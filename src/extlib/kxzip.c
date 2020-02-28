#include <dbg.h>
#include <string.h>
#if defined(_WIN32) || defined(_WIN64)
#define STRICMP(s1, s2) stricmp(s1, s2)
#else
#include <string.h>
#define STRICMP(s1, s2) strcasecmp(s1, s2)
#endif
#include <kinx.h>

#include "zip/include/mz.h"
#include "zip/include/mz_os.h"
#include "zip/include/mz_strm.h"
#include "zip/include/mz_strm_buf.h"
#include "zip/include/mz_strm_split.h"
#include "zip/include/mz_zip.h"
#include "zip/include/mz_zip_rw.h"

#define KXFILE_MODE_READ   (0x10)
#define KXFILE_MODE_WRITE  (0x20)
#define KXFILE_MODE_APPEND (0x40)

KX_DECL_MEM_ALLOCATORS();

#define KX_ZIP_GET_ZIPOBJ(r, obj) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_host:hidden"); \
    if (!val || val->type != KX_OBJ_T) { \
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Invalid Zip entry object"); \
    } \
    r = val->value.ov; \
} \
/**/

#define KX_ZIP_GET_FILENAME(r, obj) \
const char *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "filename"); \
    if (!val || val->type != KX_STR_T) { \
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Invalid Zip object"); \
    } \
    r = ks_string(val->value.sv); \
} \
/**/

#define KX_ZIP_GET_TOTALFILES(r, obj) \
int r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "totalFiles"); \
    if (!val || val->type != KX_INT_T) { \
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Invalid Zip object"); \
    } \
    r = (int)(val->value.iv); \
} \
/**/

#define KX_ZIP_GET_STR_OPTION(r, obj, propname) \
const char *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, propname); \
    if (val) { \
        if (val->type == KX_STR_T) { \
            r = ks_string(val->value.sv); \
        } else if (val->type == KX_CSTR_T) { \
            r = val->value.pv; \
        } \
    } \
} \
/**/
#define KX_ZIP_GET_INT_OPTION(r, obj, propname, def) \
int64_t r = def; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, propname); \
    if (val) { \
        if (val->type == KX_INT_T) { \
            r = val->value.iv; \
        } else if (val->type == KX_DBL_T) { \
            r = (int64_t)val->value.dv; \
        } \
    } \
} \
/**/

int Zip_extract_entry(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int Zip_extract_entry_to(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);

static int get_info(void *reader, const char *password, const char *zipfile, const char *filename, mz_zip_file **file_info)
{
    int err = MZ_OK;
    if (password) {
        mz_zip_reader_set_password(reader, password);
    }

    err = mz_zip_reader_open_file(reader, zipfile);
    if (err != MZ_OK) {
        return err;
    }

    err = mz_zip_reader_locate_entry(reader, filename, 1);
    if (err != MZ_OK) {
        return err;
    }

    err = mz_zip_reader_entry_get_info(reader, file_info);
    if (err != MZ_OK) {
        return err;
    }

    return MZ_OK;
}

static kx_obj_t *setup_entry(kx_context_t *ctx, kx_obj_t *obj, void *reader, mz_zip_file *file_info)
{
    struct tm tmu_date;
    int is_dir = mz_zip_reader_entry_is_dir(reader) == MZ_OK;
    int crypt = file_info->flag & MZ_ZIP_FLAG_ENCRYPTED;
    mz_zip_time_t_to_tm(file_info->modified_date, &tmu_date);

    kx_obj_t *entry = allocate_obj(ctx);
    KEX_SET_PROP_OBJ(entry, "_host:hidden", obj);
    KEX_SET_METHOD("read", entry, Zip_extract_entry);
    KEX_SET_METHOD("extract", entry, Zip_extract_entry);
    KEX_SET_METHOD("extractTo", entry, Zip_extract_entry_to);
    KEX_SET_PROP_INT(entry, "isDirectory", is_dir);
    KEX_SET_PROP_INT(entry, "isEncrypted", crypt);
    KEX_SET_PROP_INT(entry, "size", file_info->uncompressed_size);
    KEX_SET_PROP_INT(entry, "compsize", file_info->compressed_size);
    KEX_SET_PROP_INT(entry, "crc32", file_info->crc);
    KEX_SET_PROP_CSTR(entry, "filename", file_info->filename);
    switch (file_info->compression_method) {
    case MZ_COMPRESS_METHOD_DEFLATE:
        KEX_SET_PROP_CSTR(entry, "method", "deflate");
        break;
    case MZ_COMPRESS_METHOD_STORE:
        KEX_SET_PROP_CSTR(entry, "method", "store");
        break;
    case MZ_COMPRESS_METHOD_BZIP2:
        KEX_SET_PROP_CSTR(entry, "method", "bzip2");
        break;
    case MZ_COMPRESS_METHOD_LZMA:
        KEX_SET_PROP_CSTR(entry, "method", "lzma");
        break;
    case MZ_COMPRESS_METHOD_AES:
        KEX_SET_PROP_CSTR(entry, "method", "aes");
        break;
    default:
        KEX_SET_PROP_CSTR(entry, "method", "unknown");
        break;
    }

    kx_obj_t *time = allocate_obj(ctx);
    KEX_SET_PROP_INT(time, "year", tmu_date.tm_year);
    KEX_SET_PROP_INT(time, "month", tmu_date.tm_mon + 1);
    KEX_SET_PROP_INT(time, "day", tmu_date.tm_mday);
    KEX_SET_PROP_INT(time, "hour", tmu_date.tm_hour);
    KEX_SET_PROP_INT(time, "minute", tmu_date.tm_min);
    KEX_SET_PROP_INT(time, "second", tmu_date.tm_sec);
    KEX_SET_PROP_OBJ(entry, "time", time);
    return entry;
}

static kx_obj_t *find_file(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile, const char *filename)
{
    mz_zip_file *file_info = NULL;
    int16_t level = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    int crypt = 0;
    void *reader = NULL;

    mz_zip_reader_create(&reader);
    err = get_info(reader, NULL, zipfile, filename, &file_info);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        return NULL;
    }

    kx_obj_t *entry = setup_entry(ctx, obj, reader, file_info);
    mz_zip_reader_delete(&reader);
    return entry;
}

static int read_files(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile)
{
    int total_files = 0;
    kv_shrinkto(obj->ary, 0);

    mz_zip_file *file_info = NULL;
    int16_t level = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    int crypt = 0;
    void *reader = NULL;

    mz_zip_reader_create(&reader);
    err = mz_zip_reader_open_file(reader, zipfile);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        return err;
    }

    err = mz_zip_reader_goto_first_entry(reader);
    if (err != MZ_OK && err != MZ_END_OF_LIST) {
        mz_zip_reader_delete(&reader);
        return err;
    }

    do {
        ++total_files;
        err = mz_zip_reader_entry_get_info(reader, &file_info);
        if (err != MZ_OK) {
            break;
        }

        kx_obj_t *entry = setup_entry(ctx, obj, reader, file_info);
        KEX_PUSH_ARRAY_OBJ(obj, entry);

        err = mz_zip_reader_goto_next_entry(reader);
        if (err != MZ_OK && err != MZ_END_OF_LIST) {
            break;
        }
    }
    while (err == MZ_OK);
    mz_zip_reader_delete(&reader);
    KEX_SET_PROP_INT(obj, "totalFiles", total_files);

    if (err == MZ_END_OF_LIST)
        return MZ_OK;
    return err;
}

static int add_buffer(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile, int aes, uint16_t method, int level, int64_t disk_size, uint8_t append, const char *password, const char *filename, const char *content)
{
    int32_t err = MZ_OK;
    void *writer = NULL;
    KX_ZIP_GET_INT_OPTION(added, obj, "added", 0);
    if (added > 0) {
        append = 1;
    }

    mz_zip_writer_create(&writer);
    mz_zip_writer_set_compress_level(writer, method == MZ_COMPRESS_METHOD_STORE ? 0 : level);
    if (password) {
        mz_zip_writer_set_password(writer, password);
    }

    err = mz_zip_writer_open_file(writer, zipfile, disk_size, append);
    if (err != MZ_OK) {
        mz_zip_writer_delete(&writer);
        return err;
    }

    mz_zip_file file_info = {0};
    file_info.filename = filename;
    file_info.modified_date = time(NULL);
    file_info.version_madeby = MZ_VERSION_MADEBY;
    file_info.compression_method = method;
    file_info.flag = MZ_ZIP_FLAG_UTF8;

    mz_zip_writer_set_aes(writer, aes);
    err = mz_zip_writer_add_buffer(writer, (void*)content, strlen(content), &file_info);
    mz_zip_writer_delete(&writer);
    if (err != MZ_OK) {
        return err;
    }

    KEX_SET_PROP_INT(obj, "added", added + 1);
    err = read_files(ctx, obj, zipfile);
    return err;
}

static int add_file(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile, int aes, uint16_t method, int level, int64_t disk_size, uint8_t append, const char *password, const char *filename)
{
    int32_t err = MZ_OK;
    void *writer = NULL;
    KX_ZIP_GET_INT_OPTION(added, obj, "added", 0);
    if (added > 0) {
        append = 1;
    }

    mz_zip_writer_create(&writer);

    mz_zip_writer_set_compress_method(writer, method);
    mz_zip_writer_set_compress_level(writer, method == MZ_COMPRESS_METHOD_STORE ? 0 : level);
    if (password) {
        mz_zip_writer_set_password(writer, password);
    }

    err = mz_zip_writer_open_file(writer, zipfile, disk_size, append);
    if (err != MZ_OK) {
        mz_zip_writer_delete(&writer);
        return err;
    }

    mz_zip_writer_set_aes(writer, aes);
    err = mz_zip_writer_add_path(writer, filename, NULL, 0, 1);
    mz_zip_writer_delete(&writer);
    if (err != MZ_OK) {
        return err;
    }

    KEX_SET_PROP_INT(obj, "added", added + 1);
    err = read_files(ctx, obj, zipfile);
    return err;
}

typedef struct overwrite_status_ {
    int overwrite;
    int skipped;
} overwrite_status_t;

static int32_t extract_file_overwrite_cb(void *handle, void *userdata, mz_zip_file *file_info, const char *path)
{
    overwrite_status_t *status = (overwrite_status_t *)userdata;
    if (status->overwrite == 0) {
        status->skipped = MZ_EXIST_ERROR;
        return MZ_EXIST_ERROR;
    }
    status->skipped = 0;
    return MZ_OK;
}

static int extract_file(int args, kx_context_t *ctx, const char *zipfile, const char *password, int overwrite, int skip, const char *filename, const char *outfile)
{
    mz_zip_file *file_info = NULL;
    int16_t level = 0;
    int32_t err = MZ_OK;
    int crypt = 0;
    void *reader = NULL;
    overwrite_status_t status = { .overwrite = overwrite };

    mz_zip_reader_create(&reader);
    mz_zip_reader_set_overwrite_cb(reader, (void*)&status, extract_file_overwrite_cb);

    err = get_info(reader, password, zipfile, filename, &file_info);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, 1);
        return err;
    }

    if (mz_zip_reader_entry_is_dir(reader) == MZ_OK) {
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    if (outfile) {
        err = mz_zip_reader_entry_save_file(reader, outfile);
        if (!skip && status.skipped) {
            err = status.skipped;
        }
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, err != MZ_OK);
        return err;
    }

    int32_t buf_size = (int32_t)mz_zip_reader_entry_save_buffer_length(reader);
    char *buf = (char *)kx_calloc(buf_size + 1, sizeof(char));
    err = mz_zip_reader_entry_save_buffer(reader, buf, buf_size);
    if (!skip && status.skipped) {
        err = status.skipped;
    }
    if (err != MZ_OK) {
        kx_free(buf);
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, 1);
        return err;
    }
    if (file_info->uncompressed_size < buf_size) {
        buf[file_info->uncompressed_size] = 0;
    }

    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, buf);

    kx_free(buf);
    mz_zip_reader_delete(&reader);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return MZ_OK;
}

int Zip_add_buffer(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    KX_ZIP_GET_INT_OPTION(mode, obj, "mode", KXFILE_MODE_READ);
    if (((mode & KXFILE_MODE_WRITE) != KXFILE_MODE_WRITE) && ((mode & KXFILE_MODE_APPEND) != KXFILE_MODE_APPEND)) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Needs to open file with File.WRITE or File.APPEND");
    }

    const char *filename = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(content, opts, "content");
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_STR_OPTION(method_string, opts, "method");
    KX_ZIP_GET_INT_OPTION(aes, opts, "aes", 0);
    KX_ZIP_GET_INT_OPTION(disk_size, opts, "diskSize", 0);
    KX_ZIP_GET_INT_OPTION(level, opts, "level", 6);
    if (!filename) {
        KX_ZIP_GET_STR_OPTION(fn, opts, "filename");
        if (!fn) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename to zip");
        }
        filename = fn;
    }
    if (!content) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No file content to zip");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    uint16_t method = MZ_COMPRESS_METHOD_DEFLATE;
    if (method_string) {
        if (!STRICMP(method_string, "store")) {
            method = MZ_COMPRESS_METHOD_STORE;
        } else if (!STRICMP(method_string, "bzip2")) {
            method = MZ_COMPRESS_METHOD_BZIP2;
        } else if (!STRICMP(method_string, "lzma")) {
            method = MZ_COMPRESS_METHOD_LZMA;
        }
    }
    int append = (mode & KXFILE_MODE_APPEND) == KXFILE_MODE_APPEND;
    int err = add_buffer(ctx, obj, zipfile, aes, method, level, disk_size, append, password, filename, content);
    if (err != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to add the string in zip file(%s)", zipfile));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Zip_add_file(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    KX_ZIP_GET_INT_OPTION(mode, obj, "mode", KXFILE_MODE_READ);
    if (((mode & KXFILE_MODE_WRITE) != KXFILE_MODE_WRITE) && ((mode & KXFILE_MODE_APPEND) != KXFILE_MODE_APPEND)) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Needs to open file with File.WRITE or File.APPEND");
    }

    const char *filename = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_STR_OPTION(method_string, opts, "method");
    KX_ZIP_GET_INT_OPTION(aes, opts, "aes", 0);
    KX_ZIP_GET_INT_OPTION(disk_size, opts, "diskSize", 0);
    KX_ZIP_GET_INT_OPTION(level, opts, "level", 6);
    if (!filename) {
        KX_ZIP_GET_STR_OPTION(fn, opts, "filename");
        if (!fn) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename to zip");
        }
        filename = fn;
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    uint16_t method = MZ_COMPRESS_METHOD_DEFLATE;
    if (method_string) {
        if (!STRICMP(method_string, "store")) {
            method = MZ_COMPRESS_METHOD_STORE;
        } else if (!STRICMP(method_string, "bzip2")) {
            method = MZ_COMPRESS_METHOD_BZIP2;
        } else if (!STRICMP(method_string, "lzma")) {
            method = MZ_COMPRESS_METHOD_LZMA;
        }
    }
    int append = (mode & KXFILE_MODE_APPEND) == KXFILE_MODE_APPEND;
    int err = add_file(ctx, obj, zipfile, aes, method, level, disk_size, append, password, filename);
    if (err != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to add the file(%s) in zip file(%s)", filename, zipfile));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int extract_impl(int args, const char *filename, const char *password, int overwrite, int skip, kx_obj_t *obj, kx_context_t *ctx, const char *outfile)
{
    KX_ZIP_GET_FILENAME(zipfile, obj);
    KX_ZIP_GET_INT_OPTION(mode, obj, "mode", KXFILE_MODE_READ);
    if ((mode & KXFILE_MODE_READ) != KXFILE_MODE_READ) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Needs to open file with File.READ");
    }

    int32_t err = extract_file(args, ctx, zipfile, password, overwrite, skip, filename, outfile);
    if (err != MZ_OK) {
        if (err == MZ_EXIST_ERROR) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to extract the file(%s) because the file(%s) already exists", filename, outfile));
        } else {
            KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to extract the file(%s) in zip file(%s)", filename, zipfile));
        }
    }

    return 0;
}

int Zip_extract(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    const char *filename = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    if (!filename) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename in zip to extract");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    int r = extract_impl(args, filename, password, 1, 1, obj, ctx, NULL);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_extract_to(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    const char *filename = get_arg_str(2, args, ctx);
    const char *outfile = get_arg_str(3, args, ctx);
    kx_obj_t *opts = get_arg_obj(4, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_INT_OPTION(overwrite, opts, "overwrite", 0);
    KX_ZIP_GET_INT_OPTION(skip, opts, "skip", 0);
    if (!filename) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename in zip to extract");
    }
    if (!outfile) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No output filename to unzip");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    if (!overwrite) {
        KX_ZIP_GET_INT_OPTION(ow, obj, "overwrite", 0);
        overwrite = ow;
    }
    int r = extract_impl(args, filename, password, overwrite, skip, obj, ctx, outfile);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_extract_entry(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *entry = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_ZIPOBJ(obj, entry);
    KX_ZIP_GET_STR_OPTION(filename, entry, "filename");
    kx_obj_t *opts = get_arg_obj(2, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    int r = extract_impl(args, filename, password, 1, 1, obj, ctx, NULL);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_extract_entry_to(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *entry = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_ZIPOBJ(obj, entry);
    KX_ZIP_GET_STR_OPTION(filename, entry, "filename");
    const char *outfile = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_INT_OPTION(overwrite, opts, "overwrite", 0);
    KX_ZIP_GET_INT_OPTION(skip, opts, "skip", 0);
    if (!outfile) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No output filename to unzip");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    if (!overwrite) {
        KX_ZIP_GET_INT_OPTION(ow, obj, "overwrite", 0);
        overwrite = ow;
    }
    int r = extract_impl(args, filename, password, overwrite, skip, obj, ctx, outfile);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_find(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    const char *filename = get_arg_str(2, args, ctx);

    kx_obj_t *entry = find_file(ctx, obj, zipfile, filename);
    if (!entry) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to find the file (%s) in zip file(%s)", filename, zipfile));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, entry);
    return 0;
}

int Zip_set_password(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    const char *password = get_arg_str(2, args, ctx);

    KEX_SET_PROP_CSTR(obj, "password", password);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Zip_set_overwrite(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    int overwrite = get_arg_int(2, args, ctx);

    KEX_SET_PROP_INT(obj, "overwrite", overwrite);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Zip_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *zipfile = get_arg_str(1, args, ctx);
    if (!zipfile) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No zip file name");
    }
    int mode = get_arg_int(2, args, ctx);
    if (!mode) {
        mode = KXFILE_MODE_READ;
    }

    kx_obj_t *obj = allocate_obj(ctx);
    if (read_files(ctx, obj, zipfile) != MZ_OK) {
        if (((mode & KXFILE_MODE_WRITE) != KXFILE_MODE_WRITE) && ((mode & KXFILE_MODE_APPEND) != KXFILE_MODE_APPEND)) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to read zip file(%s)", zipfile));
        }
    }

    KEX_SET_PROP_CSTR(obj, "filename", zipfile);
    KEX_SET_PROP_INT(obj, "mode", mode);
    KEX_SET_PROP_INT(obj, "added", 0);
    KEX_SET_METHOD("read", obj, Zip_extract);
    KEX_SET_METHOD("extract", obj, Zip_extract);
    KEX_SET_METHOD("extractTo", obj, Zip_extract_to);
    KEX_SET_METHOD("find", obj, Zip_find);
    KEX_SET_METHOD("addFile", obj, Zip_add_file);
    KEX_SET_METHOD("addString", obj, Zip_add_buffer);
    KEX_SET_METHOD("setPassword", obj, Zip_set_password);
    KEX_SET_METHOD("setOverwrite", obj, Zip_set_overwrite);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create", Zip_create },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
