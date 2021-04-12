#include <dbg.h>
#include <inttypes.h>
#include <sys/stat.h>
#define KX_DLL
#include <kinx.h>
#include <kutil.h>
#include <kxthread.h>
#include <kxutf8.h>
#include <stdarg.h>

KX_DECL_MEM_ALLOCATORS();

/**
 * Debugger Core Logic
 */

typedef enum {
    CK_WHITESPACE, CK_NUMBER, CK_ALPHABET, CK_SYMBOL
} kx_charkind_t;

#define KXDS 5
#define KXNM 10
#define prompt_start() _fprintf_w32(stdout, "\n\033[96m")
#define prompt_end() _fprintf_w32(stdout, "\033[0m\033[37m")
#define prompt_cursor(pos) _fprintf_w32(stdout, "\033[%dD", pos)
#define prompt_show(fmt, ...) _fprintf_w32(stdout, fmt, __VA_ARGS__)
#define output_source_l(l, line) _fprintf_w32(stdout, "\033[90m %4d:\033[0m %s", l, line)
#define output_bsource_l(l, line) _fprintf_w32(stdout, "\033[31m*%4d:\033[0m %s", l, line)
#define output_xsource_l(l, line) _fprintf_w32(stdout, "\033[1m %4d:\033[0m \033[93m%s\033[0m", l, line)
#define output_bxsource_l(l, line) _fprintf_w32(stdout, "\033[91m*%4d:\033[0m \033[93m%s\033[0m", l, line)
#define output1(str) _fprintf_w32(stdout, "%s", str)
#define output(fmt, ...) _fprintf_w32(stdout, fmt, __VA_ARGS__)
#define message1(str) _fprintf_w32(stdout, "\033[32m>>> %s\033[0m", str)
#define message(fmt, ...) _fprintf_w32(stdout, "\033[32m>>> " fmt "\033[0m", __VA_ARGS__)
#define error1(str) _fprintf_w32(stdout, "\033[33m>>> Error: %s\033[0m", str)
#define error(fmt, ...) _fprintf_w32(stdout, "\033[33m>>> Error: " fmt "\033[0m", __VA_ARGS__)

#define BUFFER_MAX (2048)
#define BUFFER_LMT (2000)
#define HISTORY_MAX (128)
#define HISTORY_PREV(i) ((i + HISTORY_MAX - 1) % HISTORY_MAX)
#define HISTORY_NEXT(i) ((i + 1) % HISTORY_MAX)

static int sg_history_pos = 0;
static kstr_t *sg_history[HISTORY_MAX] = {0};
static kstr_t *sg_empty_str;

void kx_debugger_init(void)
{
    sg_empty_str = ks_new();
}

void kx_debugger_fin(void)
{
    for (int i = 0; i < HISTORY_MAX; ++i) {
        if (sg_history[i]) {
            ks_free(sg_history[i]);
        }
    }
    ks_free(sg_empty_str);
}

static void add_history(const char *line)
{
    if (!sg_history[sg_history_pos]) {
        sg_history[sg_history_pos] = ks_new();
    } else {
        ks_clear(sg_history[sg_history_pos]);
    }
    ks_append(sg_history[sg_history_pos], line);
    sg_history_pos = HISTORY_NEXT(sg_history_pos);
}

static kstr_t *get_history_prev(unsigned int *hpos)
{
    *hpos = HISTORY_PREV(*hpos);
    if (!sg_history[*hpos]) {
        int e = *hpos;
        *hpos = HISTORY_PREV(*hpos);
        while (*hpos != e) {
            if (sg_history[*hpos]) {
                return sg_history[*hpos];
            }
            *hpos = HISTORY_PREV(*hpos);
        }
        return sg_empty_str;
    }
    return sg_history[*hpos];
}

static kstr_t *get_history_next(unsigned int *hpos)
{
    *hpos = HISTORY_NEXT(*hpos);
    if (!sg_history[*hpos]) {
        int e = *hpos;
        *hpos = HISTORY_NEXT(*hpos);
        while (*hpos != e) {
            if (sg_history[*hpos]) {
                return sg_history[*hpos];
            }
            *hpos = HISTORY_NEXT(*hpos);
        }
        return sg_empty_str;
    }
    return sg_history[*hpos];
}

static int get_width(const char *p)
{
    int width = 0;
    int len = strlen(p);
    for (int i = 0; i < len; ) {
        int ul = utf8_length(*(p+i));
        const char *r = east_asian_width(p + i, ul, NULL, NULL);
        width += (*r == 'F' || *r == 'W' || *r == 'A') ? 2 : 1;
        i += ul;
    }
    return width;
}

static int get_pos_width(const char *p, int pos)
{
    int width = 0;
    for (int i = 0; i < pos; ) {
        int ul = utf8_length(*(p+i));
        const char *r = east_asian_width(p + i, ul, NULL, NULL);
        width += (*r == 'F' || *r == 'W' || *r == 'A') ? 2 : 1;
        i += ul;
    }
    return width;
}

static int get_left_pos(const char *buffer, int pos)
{
    int last = 0;
    int l = strlen(buffer);
    for (int i = 0; i < pos; ) {
        last = utf8_length(*(buffer + i));
        i += last;
    }
    return pos - last;
}

static int get_right_pos(const char *buffer, int pos)
{
    int l = strlen(buffer);
    if (l <= pos) {
        return pos;
    }
    int u8len = utf8_length(*(buffer + pos));
    return pos + u8len;
}

static int remove_bs(char *buffer, int pos)
{
    if (pos == 0) {
        return pos;
    }
    int len = strlen(buffer);
    int size = len - pos;
    int prev = get_left_pos(buffer, pos);
    if (size == 0) {
        buffer[prev] = 0;
    } else {
        memmove(buffer + prev, buffer + pos, size);
        buffer[len - (pos - prev)] = 0;
    }
    return prev;
}

static int remove_pos(char *buffer, int pos)
{
    int len = strlen(buffer);
    if (pos >= len) {
        return pos;
    }
    int u8len = utf8_length(*(buffer + pos));
    int size = len - pos - u8len;
    if (size == 0) {
        buffer[pos] = 0;
    } else {
        memmove(buffer + pos, buffer + pos + u8len, size);
        buffer[len - u8len] = 0;
    }
    return pos;
}

static int insert_ch(kx_context_t *ctx, char *buffer, int pos, int ch)
{
    int sep = pos;
    char buf[BUFFER_MAX] = {0};
    strncpy(buf, buffer, pos);
    buf[pos++] = ch;
    if (BUFFER_LMT < pos) {
        return pos;
    }
    int u8len = utf8_length(ch);
    if (u8len > 1) {
        while (--u8len) {
            buf[pos++] = kx_scan_keycode(ctx);
        }
    }
    strcpy(buf + pos, buffer + sep);
    strcpy(buffer, buf);
    return pos;
}

static kstr_t *prompt(kx_context_t *ctx)
{
    int hpos = sg_history_pos;
    int width = 0;
    int pos = 0;
    char buffer[BUFFER_MAX] = {0};
    while (1) {
        ctx->signal.signal_received = 0;
        ctx->signal.sigint_count = 0;
        char *buf = conv_utf82acp_alloc(buffer);
        prompt_show("\r%*s\r> %s", -width-2, " ", buf);
        conv_free(buf);
        width = get_width(buffer);  // to remove a previous text.
        int poswidth = get_pos_width(buffer, pos);
        prompt_cursor(width - poswidth);
        int ch = kx_scan_keycode(ctx);
        if (ch == 0) {
            continue;
        }
        if (ch == 3) {
            ctx->signal.signal_received = 0;
            ctx->signal.sigint_count = 0;
            buffer[0] = 0;
            break;
        }
        if (ch < 0) {
            buffer[0] = 'q';
            buffer[1] = 0;
            break;
        }
        switch (ch) {
        case KX_KEY_ENTER:
            if (buffer[0] != '!') {
                add_history(buffer);
            }
            goto END_OF_INPUT;
        case KX_KEY_UP:
            strcpy(buffer, ks_string(get_history_prev(&hpos)));
            pos = strlen(buffer);
            continue;
        case KX_KEY_DOWN:
            strcpy(buffer, ks_string(get_history_next(&hpos)));
            pos = strlen(buffer);
            continue;
        case KX_KEY_BS:
            pos = remove_bs(buffer, pos);
            continue;
        case KX_KEY_DEL:
            pos = remove_pos(buffer, pos);
            continue;
        case KX_KEY_LEFT:
            pos = get_left_pos(buffer, pos);
            continue;
        case KX_KEY_RIGHT: {
            pos = get_right_pos(buffer, pos);
            continue;
        }
        default:
            break;
        }
        pos = insert_ch(ctx, buffer, pos, ch);
    }

END_OF_INPUT:;
    kstr_t *s = allocate_str(ctx);
    ks_append(s, buffer);
    printf("\n");

    return s;
}

static int is_char(kstr_t *s, char ch)
{
    return ks_length(s) == 1 && ks_string(s)[0] == ch;
}

static int is_number(kstr_t *s)
{
    const char *p = ks_string(s);
    if (!p || !*p) {
        return 0;
    }
    if (*p == '-') {
        ++p;
    }
    while (*p) {
        if (*p < '0' || '9' < *p) {
            return 0;
        }
        ++p;
    }
    return 1;
}

static int is_double(kstr_t *s)
{
    const char *p = ks_string(s);
    if (!p || !*p) {
        return 0;
    }
    if (*p == '-') {
        ++p;
    }
    int dot = 0;
    while (*p) {
        if (*p == '.') {
            if (++dot > 1) {
                break;
            }
            ++p;
            continue;
        }
        if (*p < '0' || '9' < *p) {
            return 0;
        }
        ++p;
    }
    return 1;
}

static void do_command_show_history(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    int idx = 0;
    int hpos = sg_history_pos;
    for (int i = 0; i < HISTORY_MAX; ++i) {
        kstr_t *s = sg_history[hpos];
        if (s && ks_length(s) > 0) {
            char *buf = conv_utf82acp_alloc(ks_string(s));
            output(" [%4d] %s\n", idx++, buf);
            conv_free(buf);
        }
        hpos = HISTORY_NEXT(hpos);
    }
}

static kstr_t *do_command_get_command(int sidx)
{
    if (sidx < 0) {
        kstr_t *s = NULL;
        int hpos = sg_history_pos;
        do {
            s = get_history_prev(&hpos);
        } while (++sidx < 0);
        return s;
    }

    int idx = 0;
    int hpos = sg_history_pos;
    for (int i = 0; i < HISTORY_MAX; ++i) {
        kstr_t *s = sg_history[hpos];
        if (s && ks_length(s) > 0) {
            if (idx == sidx) {
                return s;
            }
            ++idx;
        }
        hpos = HISTORY_NEXT(hpos);
    }
    return NULL;
}

static kx_charkind_t get_char_kind(const char *p, int in_alphabet)
{
    if (*p == ' ') {
        return CK_WHITESPACE;
    } else if (('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z') || *p == '!' || *p == '.' || *p == '[' || *p == ']' || *p == '_') {
        return CK_ALPHABET;
    } else if (*p == '-' || ('0' <= *p && *p <= '9')) {
        return in_alphabet ? CK_ALPHABET : CK_NUMBER;
    }
    return CK_SYMBOL;
}

static void setup_command(kstr_t *a[KXDS], kstr_t *args)
{
    ks_trim(args);
    int i = 0, l = ks_length(args), idx = 0, start = 0;
    while (i < l) {
        const char *p = ks_string(args) + i;
        const char *n = p;
        kx_charkind_t kind = get_char_kind(p, 0);
        int in_alphabet = 0;
        for ( ; i < l; ++i) {
            n = ks_string(args) + i;
            if (*n == '[')      in_alphabet = 1;
            else if (*n == ']') in_alphabet = 0;
            kx_charkind_t next = get_char_kind(n, in_alphabet);
            if (*n == ' ' || *n == 0 || kind != next) {
                break;
            }
        }
        ks_append_n(a[idx], ks_string(args) + start, i - start);
        if (idx++ >= KXDS) {
            break;
        }
        while (*n == ' ') {
            ++i;
            ++n;
        }
        start = i;
    }
}

static int get_positive_array_index(kstr_t *s, int max)
{
    int val = 0;
    int minus = 0;
    const char *p = ks_string(s);
    if (!p || !*p) {
        return -1;
    }
    if (*p != '[') {
        return -1;
    }
    ++p;
    if (*p == '-') {
        minus = 1;
        ++p;
    }
    while (*p) {
        if (*p == ']' && *(p + 1) == 0) {
            if (minus) {
                val = -val;
                do {
                    val = val + max;
                } while (val < 0);
            }
            return val;
        }
        if (*p < '0' || '9' < *p) {
            return -1;
        }
        val = val * 10 + (*p - '0');
        ++p;
    }
    return -1;
}

static kx_frm_t *get_stack_frame(kx_context_t *ctx, int n)
{
    kx_frm_t *fr = NULL;
    int ssp = kv_size((ctx)->stack);
    for (int sp = 1; sp < ssp; ++sp) {
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        if (v->type == KX_FRM_T) {
            if (v->value.fr->id == n) {
                fr = v->value.fr;
                break;
            }
        }
    }
    return fr;
}

static kx_frm_t *get_lexical_frame(kx_frm_t *frmv, int n)
{
    if (n < 0) {
        return NULL;
    }
    kx_frm_t *f = frmv->lex;
    while (f) {
        if (f->id == n) {
            return f;
        }
        f = f->lex;
    }
    return NULL;
}

static int has_breakpoint(const char *file, int line, kx_location_list_t *breakpoints)
{
    while (breakpoints) {
        if (breakpoints->location.line == line && !strcmp(breakpoints->location.file, file)) {
            return 1;
        }
        breakpoints = breakpoints->next;
    }
    return 0;
}

static void do_command_show_breakpoints(kx_context_t *ctx)
{
    kx_location_list_t *breakpoints = ctx->breakpoints;
    if (!breakpoints) {
        message1("No breakpoints.\n");
    } else {
        output1("Breakpoints:\n");
        while (breakpoints) {
            output("  - <%s:%d>\n", breakpoints->location.file, breakpoints->location.line);
            breakpoints = breakpoints->next;
        }
    }
}

static void add_breakpoint(const char *file, int line, kx_context_t *ctx)
{
    kx_location_list_t *loc = kx_calloc(1, sizeof(kx_location_list_t));
    loc->location.file = kx_const_str(ctx, file);
    loc->location.line = line;
    loc->next = ctx->breakpoints;
    ctx->breakpoints = loc;
    message("Added the breakpoint of <%s:%d>.\n", file, line);
    do_command_show_breakpoints(ctx);
}

static void remove_breakpoint(const char *file, int line, kx_context_t *ctx)
{
    kx_location_list_t *prev = NULL;
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        if (breakpoints->location.line == line && !strcmp(breakpoints->location.file, file)) {
            if (prev) {
                prev->next = breakpoints->next;
            } else {
                ctx->breakpoints = breakpoints->next;
            }
            kx_free(breakpoints);
            break;
        }
        prev = breakpoints;
        breakpoints = breakpoints->next;
    }
    message("Removed the breakpoint of <%s:%d>.\n", file, line);
    do_command_show_breakpoints(ctx);
}

static void remove_breakpoint_all(kx_context_t *ctx)
{
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        kx_location_list_t *next = breakpoints->next;
        kx_free(breakpoints);
        breakpoints = next;
    }
    ctx->breakpoints = NULL;
    message1("Removed all breakpoints.\n");
}

static int split_name(kstr_t *a[KXNM], kstr_t *name)
{
    int i = 0, l = ks_length(name), idx = 0, start = 0;
    for ( ; i < l; ++i) {
        const char *p = ks_string(name) + i;
        if (*p == '[') {
            ks_append_n(a[idx], ks_string(name) + start, i - start);
            if (++idx >= KXNM) {
                return idx;
            }
            while (*p == '[') {
                start = i;
                for ( ; i < l; ++i) {
                    const char *n = ks_string(name) + i;
                    if (*n == 0) {
                        return 0;   // invalid.
                    }
                    if (*n == ']') {
                        ++i;
                        break;
                    }
                }
                ks_append_n(a[idx], ks_string(name) + start, i - start);
                if (++idx >= KXNM) {
                    return idx;
                }
                p = ks_string(name) + i;
            }
            if (*p != '.' && *p != 0) {
                return 0;   // invalid.
            }
            start = i + 1;
        } else if (*p == '.') {
            ks_append_n(a[idx], ks_string(name) + start, i - start);
            if (++idx >= KXNM) {
                return idx;
            }
            start = i + 1;
        }
    }
    if (i > start) {
        ks_append_n(a[idx++], ks_string(name) + start, i - start);
    }

    return idx;
}

static kstr_t *get_script_name(kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    char *buf = conv_acp2utf8_alloc(getenv("KINX_RUN_SCRIPT"));
    ks_append(sv, buf);
    conv_free(buf);
    return sv;
}

static const char *get_funcname(const char *func)
{
    if (!func || !strcmp(func, "_main1")) {
        return "<main-block>";
    }
    return func;
}

static kx_location_t get_frame_location(kx_context_t *ctx, kx_frm_t *frmv, kx_location_t *location)
{
    kx_location_t loc = *location;

    kx_frm_t *prv = NULL;
    int ssp = kv_size((ctx)->stack);
    for (int sp = ssp - 1; sp > 0; --sp) {
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        if (v->type == KX_FRM_T) {
            kx_frm_t *fr = v->value.fr;
            if (fr->caller) {
                if (frmv == fr) {
                    loc.file = fr->caller->file;
                    loc.line = fr->caller->line;
                    loc.func = fr->caller->func;
                    break;
                }
                prv = fr;
            }
        }
    }

    return loc;
}

static void do_command_toggle_breakpoint(kx_context_t *ctx, kx_location_t *location, kstr_t *arg[KXDS])
{
    if (is_number(arg[1])) {
        const char *scriptname = location->file;
        int line = (int)strtol(ks_string(arg[1]), NULL, 0);
        if (has_breakpoint(scriptname, line, ctx->breakpoints)) {
            remove_breakpoint(scriptname, line, ctx);
        } else {
            add_breakpoint(scriptname, line, ctx);
        }
    }
}

static void do_command_breakpoint(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_char(arg[1], '-')) {
        remove_breakpoint_all(ctx);
    } else if (is_number(arg[1])) {
        do_command_toggle_breakpoint(ctx, location, arg);
    } else {
        do_command_show_breakpoints(ctx);
    }
}

static kstr_t *sanitize_ws(kx_context_t *ctx, const char *p)
{
    kstr_t *ns = allocate_str(ctx);
    if (!p) {
        return ns;
    }
    for ( ; *p; ++p) {
        if (*p == '\r') {
            continue;
        }
        if (*p == '\n') {
            ks_append(ns, "\\");
            ks_append(ns, "n");
            continue;
        }
        if (*p == '\\') {
            ks_append(ns, "\\");
            ks_append(ns, "\\");
            continue;
        }
        if (*p == '"') {
            ks_append(ns, "\\");
            ks_append(ns, "\"");
            continue;
        }
        if (*p == '\t') {
            ks_append(ns, "\\");
            ks_append(ns, "t");
            continue;
        }
        char buf[2] = { *p, 0 };
        ks_append(ns, buf);
    }
    return ns;
}

static void do_command_frm_list(kx_context_t *ctx, kx_frm_t *frmv)
{
    if (!frmv) {
        return;
    }

    char *buf;
    int size = kv_size(frmv->varname);
    for (int i = 0; i < size; ++i) {
        const char *v = kv_A(frmv->varname, i).name;
        kx_val_t *v1 = &kv_A(frmv->v, i);
        output("  [%2d] %s", i, v);
        switch (v1->type) {
        case KX_INT_T:
            output(" = int, %"PRId64"", v1->value.iv);
            break;
        case KX_DBL_T:
            output(" = dbl, %g", v1->value.dv);
            break;
        case KX_BIG_T:
            buf = BzToString(v1->value.bz, 10, 0);
            output(" = big, %s", buf);
            BzFreeString(buf);
            break;
        case KX_CSTR_T:
            buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, v1->value.pv)));
            output(" = cstr, \"%s\"", buf);
            conv_free(buf);
            break;
        case KX_STR_T:
            buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, ks_string(v1->value.sv))));
            output(" = str, \"%s\"", buf);
            conv_free(buf);
            break;
        case KX_BIN_T:
            output1(" = bin");
            break;
        case KX_OBJ_T:
            output1(" = obj");
            break;
        case KX_FNC_T:
        case KX_BFNC_T:
            output1(" = fnc");
            break;
        default:
            break;
        }
        output1("\n");
    }
}

static void do_command_frm(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_char(arg[1], '.')) {
        do_command_frm_list(ctx, *cfrm);
        return;
    }

    output(" %s [%4d] %s (%s:%d)\n", (*cfrm) == frmv ? "[*]" : " - ", frmv->id, get_funcname(location->func), location->file, location->line);
    int ssp = kv_size((ctx)->stack);
    for (int sp = ssp - 1; sp > 0; --sp) {
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        if (v->type == KX_FRM_T) {
            kx_frm_t *fr = v->value.fr;
            if (fr->caller && (!fr->prv || !fr->prv->is_internal)) {
                output(" %s [%4d] %s (%s:%d)\n", (*cfrm) == fr->prv ? "[*]" : " - ", fr->prv ? fr->prv->id : 0, get_funcname(fr->caller->func), fr->caller->file, fr->caller->line);
            }
        }
    }
}

static void do_command_frm_var(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_number(arg[1])) {
        int frm = (int)strtol(ks_string(arg[1]), NULL, 0);
        if (frm < 0) {
            return;
        }

        kx_frm_t *fr = get_stack_frame(ctx, frm);
        if (fr) {
            do_command_frm_list(ctx, fr);
        }
    }
}

static void do_command_lex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    kx_location_t loc = get_frame_location(ctx, *cfrm, location);
    output(" [*] [%4d] %s (%s:%d)\n", (*cfrm)->id, get_funcname(loc.func), loc.file, loc.line);
    for (kx_frm_t *f = (*cfrm)->lex; f; f = f->lex) {
        output(" %s [%4d] lexical frame\n", (*cfrm) == f ? "[*]" : " - ", f->id);
    }
}

static void do_command_lex_var(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_number(arg[1])) {
        int lex = (int)strtol(ks_string(arg[1]), NULL, 0);
        kx_frm_t *f = get_lexical_frame(frmv, lex);
        if (f) {
            do_command_frm_list(ctx, f);
        }
    }
}

static void do_command_stack_list(kx_context_t *ctx, int max)
{
    int i = 0;
    int ssp = kv_size((ctx)->stack);
    for (int sp = ssp - 1; sp > 0; --sp) {
        if (max > 0 && ++i > max) {
            output1("    ... more\n");
            break;
        }
        char *buf;
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        switch (v->type) {
        case KX_UND_T:
            output("  [%5d] null\n", sp);
            break;
        case KX_INT_T:
            output("  [%5d] int, %"PRId64"\n", sp, v->value.iv);
            break;
        case KX_BIG_T:
            buf = BzToString(v->value.bz, 10, 0);
            output("  [%5d] big, %s\n", sp, buf);
            BzFreeString(buf);
            break;
        case KX_DBL_T:
            output("  [%5d] dbl, %g\n", sp, v->value.dv);
            break;
        case KX_CSTR_T:
            buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, v->value.pv)));
            output("  [%5d] cstr, %s\n", sp, buf);
            conv_free(buf);
            break;
        case KX_STR_T:
            buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, ks_string(v->value.sv))));
            output("  [%5d] str, %s\n", sp, buf);
            conv_free(buf);
            break;
        case KX_BIN_T:
            output("  [%5d] bin, <...>\n", sp);
            break;
        case KX_OBJ_T:
            output("  [%5d] object/array\n", sp);
            break;
        case KX_FNC_T:
            output("  [%5d] function, %s\n", sp, v->value.fn->jp->func);
            break;
        case KX_FRM_T:
            output("  [%5d] frm, var:%d\n", sp, (int)kv_size(v->value.fr->v));
            break;
        case KX_BFNC_T:
            output("  [%5d] built-in function\n", sp);
            break;
        case KX_NFNC_T:
            output("  [%5d] native, %s\n", sp, v->value.fn->native.name);
            break;
        case KX_ADDR_T:
            if (v->value.jp) {
                output("  [%5d] address, ret -> %s\n", sp, v->value.jp->func);
            } else {
                output("  [%5d] address, ret -> <end>\n", sp);
            }
            break;
        case KX_ANY_T:
            output("  [%5d] any object\n", sp);
            break;
        default:
            ;
        }
    }
}

static void do_command_stack(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (ks_length(arg[1]) == 0) {
        do_command_stack_list(ctx, 10);
    } else if (!strcmp(ks_string(arg[1]), "all")) {
        do_command_stack_list(ctx, -1);
    }
}

static void do_command_move_frame(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    int n = -1;
    if (is_number(arg[1])) {
        n = (int)strtol(ks_string(arg[1]), NULL, 0);
    }
    if (is_char(arg[1], '-')) {
        n = frmv->id;
    }
    if (n >= 0) {
        kx_frm_t *fr = NULL;
        if (!strcmp(ks_string(arg[0]), "mf")) {
            fr = get_stack_frame(ctx, n);
        } else if (!strcmp(ks_string(arg[0]), "ml")) {
            fr = get_lexical_frame(frmv, n);
        }
        if (fr) {
            *cfrm = fr;
        }
    }
}

static kx_val_t *get_variable_by_name(kx_frm_t *frmv, kstr_t *nm[KXDS])
{
    const char *base = ks_string(nm[0]);
    int size = kv_size(frmv->varname);
    for (int i = 0; i < size; ++i) {
        const char *v = kv_A(frmv->varname, i).name;
        if (!strcmp(v, base)) {
            return &kv_A(frmv->v, i);
        }
    }
    return NULL;
}

static void show_variable_info(kx_context_t *ctx, kx_val_t *v, int recursive)
{
    char *buf;
    switch (v->type) {
    case KX_UND_T:
        output1("  --> null\n");
        break;
    case KX_INT_T:
        output("  --> int, %"PRId64"\n", v->value.iv);
        break;
    case KX_BIG_T:
        buf = BzToString(v->value.bz, 10, 0);
        output("  --> big, %s\n", buf);
        BzFreeString(buf);
        break;
    case KX_DBL_T:
        output("  --> dbl, %g\n", v->value.dv);
        break;
    case KX_CSTR_T:
        buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, v->value.pv)));
        output("  --> cstr, %s\n", buf);
        conv_free(buf);
        break;
    case KX_STR_T:
        buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, ks_string(v->value.sv))));
        output("  --> str, %s\n", buf);
        conv_free(buf);
        break;
    case KX_BIN_T:
        output1("  --> bin, <...>\n");
        break;
    case KX_OBJ_T: {
        kx_obj_t *obj = v->value.ov;
        output1("  --> object/array\n");
        if (recursive) {
            int sz = kv_size(obj->ary);
            for (int i = 0; i < sz; ++i) {
                kx_val_t *vp = &kv_A(obj->ary, i);
                output("    [%d]", i);
                show_variable_info(ctx, vp, 0);
            }
            for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
                if (kh_exist(obj->prop, k)) {
                    kx_val_t *vp = &kh_value(obj->prop, k);
                    const char *key = kh_key(obj->prop, k);
                    output("    .%s", key);
                    show_variable_info(ctx, vp, 0);
                }
            }
        }
        break;
    }
    case KX_FNC_T:
        output("  --> function, %s\n", v->value.fn->jp->func);
        break;
    case KX_BFNC_T:
        output1("  --> built-in function\n");
        break;
    case KX_NFNC_T:
        output("  --> native, %s\n", v->value.fn->native.name);
        break;
    case KX_ANY_T:
        output1("  --> <any object>\n");
        break;
    default:
        ;
    }
}

static kx_val_t *get_object_property(kx_val_t *val, kstr_t *nm[KXNM], int nms)
{
    for (int i = 1; i < nms; ++i) {
        if (val->type != KX_OBJ_T) {
            return NULL; // invalid.
        }
        kx_val_t *nextv = NULL;
        int max = kv_size(val->value.ov->ary);
        int index = get_positive_array_index(nm[i], max);
        if (index >= 0) {
            nextv = &kv_A(val->value.ov->ary, index);
        } else {
            KEX_GET_PROP(nextv, val->value.ov, ks_string(nm[i]));
        }
        if (!nextv) {
            return NULL; // not found.
        }
        val = nextv;
    }
    return val;
}

static void set_value_to_variable(kx_context_t *ctx, const char *name, kx_val_t *val, kstr_t *value, const char *type)
{
    if (!type || !type[0]) {
        if (is_number(value)) {
            type = "i";
        } else if (is_double(value)) {
            type = "d";
        } else {
            type = "s";
        }
    }
    if (type[0] == 'i') {
        int64_t v = strtoll(ks_string(value), NULL, 0);
        val->type = KX_INT_T;
        val->value.iv = v;
        message("Set %"PRId64", to the variable(%s)\n", v, name);
        show_variable_info(ctx, val, 0);
    } else if (type[0] == 'd') {
        double v = strtod(ks_string(value), NULL);
        val->type = KX_DBL_T;
        val->value.dv = v;
        message("Set %g, to the variable(%s)\n", v, name);
        show_variable_info(ctx, val, 0);
    } else if (type[0] == 's') {
        val->type = KX_STR_T;
        val->value.sv = value;
        char *buf = conv_utf82acp_alloc(ks_string(value));
        message("Set \"%s\", to the variable(%s)\n", buf, name);
        conv_free(buf);
        show_variable_info(ctx, val, 0);
    }
}

static void do_command_variable_set(kx_context_t *ctx, kx_frm_t *frmv, kstr_t *name, kstr_t *value, kstr_t *type)
{
    kstr_t *nm[KXNM];
    for (int i = 0; i < KXNM; ++i) {
        nm[i] = allocate_str(ctx);
    }
    int nms = split_name(nm, name);
    kx_val_t *val = get_variable_by_name(frmv, nm);
    if (!val) {
        error("Variable(%s) not found\n", ks_string(name));
        return;
    }
    if (nms > 1) {
        val = get_object_property(val, nm, nms);
        if (!val) {
            error("Variable(%s) do not have a specified property.\n", ks_string(nm[0]));
            return; // not found.
        }
    }
    set_value_to_variable(ctx, ks_string(name), val, value, ks_string(type));
}

static void do_command_variable_show(kx_context_t *ctx, kx_frm_t *frmv, kstr_t *name)
{
    kstr_t *nm[KXNM];
    for (int i = 0; i < KXNM; ++i) {
        nm[i] = allocate_str(ctx);
    }
    int nms = split_name(nm, name);
    if (nms <= 0) {
        return;
    }
    kx_val_t *val = get_variable_by_name(frmv, nm);
    if (!val) {
        error("Variable(%s) not found\n", ks_string(name));
        return;
    }

    if (nms > 1) {
        val = get_object_property(val, nm, nms);
        if (!val) {
            error("Variable(%s) do not have a specified property.\n", ks_string(nm[0]));
            return; // not found.
        }
    }
    show_variable_info(ctx, val, 1);
}

static void do_command_variable(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (ks_length(arg[1]) == 0) {
        do_command_frm_list(ctx, *cfrm);  /* Show the variables in the current frame. */
    } else if (ks_length(arg[2]) > 0) {
        // Set the value to the variable.
        do_command_variable_set(ctx, *cfrm, arg[1], arg[2], arg[3]);
    } else {
        // Show details of the variable.
        do_command_variable_show(ctx, *cfrm, arg[1]);
    }
}

static kx_function_t *get_function_info(kx_context_t *ctx, kx_location_t *location, int list)
{
    const char *cfunc = location->func;
    if (!cfunc || !strcmp(cfunc, "_main1")) {
        return NULL;
    }
    const char *cfile = location->file;
    int cline = location->line;
    int cfunclines = -1;
    kx_function_t *candidate = NULL;
    int mlen = kv_size(ctx->module);
    for (int mi = 0; mi < mlen; ++mi) {
        kx_module_t *module = &kv_A(ctx->module, mi);
        int flen = kv_size(*(module->funclist));
        for (int fi = 0; fi < flen; ++fi) {
            kx_function_t *func = &kv_A(*(module->funclist), fi);
            if (list) {
                if (func->start <= func->end) {
                    printf(" - %s - %s(%d - %d)\n", func->name, func->file, func->start, func->end);
                }
            }
            if (func->name && cfunc && !strcmp(func->name, cfunc) && !strcmp(func->file, cfile)) {
                int funclines = func->end - func->start;
                if (funclines < cfunclines || cfunclines < 0) {
                    candidate = func;
                }
            }
        }
    }
    return candidate;
}

static void do_command_sourcecode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (!strcmp(ks_string(arg[1]), "list")) {
        (void)get_function_info(ctx, location, 1);
        return;
    }

    const char *file = location->file;
    FILE *fp = fopen(file, "r");
    if (!fp) {
        error("Can't open the file(%s).\n", file);
        return;
    }
    int start = 0, end = 0;
    if (strcmp(ks_string(arg[1]), "all") != 0) {
        kx_function_t *func = get_function_info(ctx, location, 0);
        if (func) {
            start = func->start;
            end = func->end;
        }
    }

    int l = 0, line = location->line;
    char buf[2048] = {0};
    while (fgets(buf, 2040, fp)) {
        ++l;
        if (l < start) {
            continue;
        }
        if (end < l && 0 < end) {
            break;
        }
        int b = has_breakpoint(file, l, ctx->breakpoints);
        if (l == line) {
            if (b) output_bxsource_l(l, buf);
            else   output_xsource_l(l, buf);
        } else {
            if (b) output_bsource_l(l, buf);
            else   output_source_l(l, buf);
        }
    }
    fclose(fp);
}

static void do_command_dumpecode_block(kx_context_t *ctx, kx_function_t *func, kx_block_t *block, kx_location_t *location, int is_main)
{
    if (block) {
        int len = kv_size(block->code);
        if (len == 0) {
            return;
        }
        const char *file = location->file;
        kx_code_t *code0 = &kv_A(block->code, 0);
        if (is_main && code0 && code0->file && strcmp(code0->file, file) != 0) {
            return;
        }
        output(".L%d\n", block->index);
        for (int i = 0; i < len; ++i) {
            kx_code_t *code = &kv_A(block->code, i);
            if (is_main) {
                if (code && code->op != KX_VARNAME && (code->op == KX_ENTER || (!code->file || !strcmp(code->file, file)))) {
                    ctx->ir_dumpcode(code->i, code, location);
                }
            } else {
                if (code && code->op != KX_VARNAME) {
                    ctx->ir_dumpcode(code->i, code, location);
                }
            }
        }
    }
}

static void output_funcname(kx_function_t *func)
{
    if (func->end > 0) {
        output("%s: %s(%d - %d)\n", func->name, func->file, func->start, func->end);
    } else {
        output("%s:\n", func->name);
    }
}

static void do_command_dumpecode_func(kx_context_t *ctx, kx_module_t *module, kx_function_t *func, kx_location_t *location)
{
    output_funcname(func);
    int is_main = !strcmp(func->name, "_main1");
    int len = kv_size(func->block);
    for (int i = 0; i < len; ++i) {
        int block = kv_A(func->block, i);
        do_command_dumpecode_block(ctx, func, &kv_A(module->blocks, block), location, is_main);
    }
}

static void do_command_dumpcode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    const char *cfunc = location->func;
    const char *cfile = location->file;
    int cline = location->line;
    kx_function_t *func = NULL;
    kx_module_t *module = NULL;
    int mlen = kv_size(ctx->module);

    if (strcmp(ks_string(arg[1]), "all") != 0) {
        int cfunclines = -1;
        for (int mi = 0; mi < mlen; ++mi) {
            kx_module_t *m = &kv_A(ctx->module, mi);
            int flen = kv_size(*(m->funclist));
            for (int fi = 0; fi < flen; ++fi) {
                kx_function_t *f = &kv_A(*(m->funclist), fi);
                if (f->name && cfunc && !strcmp(f->name, cfunc) && !strcmp(f->file, cfile)) {
                    int funclines = f->end - f->start;
                    if (funclines < cfunclines || cfunclines < 0) {
                        func = f;
                        module = m;
                    }
                }
            }
        }
    }

    if (func && module) {
        do_command_dumpecode_func(ctx, module, func, location);
    } else {
        int output = 0;
        for (int mi = 0; mi < mlen; ++mi) {
            module = &kv_A(ctx->module, mi);
            if (!module || !module->funclist) {
                continue;
            }
            int flen = kv_size(*(module->funclist));
            for (int fi = 0; fi < flen; ++fi) {
                func = &kv_A(*(module->funclist), fi);
                if (!func || func->is_internal || !strcmp(func->name, "_startup")) {
                    continue;
                }
                if (output++ > 0) output1("\n");
                do_command_dumpecode_func(ctx, module, func, location);
            }
        }
    }
}

static void usage(void)
{
    output1("Kinx Debugger version 0.1.0\n");
    output1("\n");
    output1("[Common]\n");
    output1("  h, help               Display this help.\n");
    output1("  !, history            Display a command history.\n");
    output1("  !!                    Do the previous command in history.\n");
    output1("  ! [N]                 Do the [N]th command in history.\n");
    output1("\n");
    output1("[Flow]\n");
    output1("  n                     Run until the next line by step-in.\n");
    output1("  nn                    Run until the next line by step-out.\n");
    output1("  r                     Run until the next breakpoint.\n");
    output1("  b                     Show breakpoints.\n");
    output1("  b [L]                 Toggle the breakpoint to the line [L].\n");
    output1("  b -                   Remove all breakpoints.\n");
    output1("\n");
    output1("[Frames]\n");
    output1("  f                     Show a frame list on the stack.\n");
    output1("  l                     Show a lexical frame list of a current frame.\n");
    output1("  mf [N]                Move a current frame to the specified stack frame.\n");
    output1("  ml [N]                Move a current frame to the specified lexical frame.\n");
    output1("\n");
    output1("[Stack]\n");
    output1("  s                     Show the stack with the first 10 entries.\n");
    output1("  s all                 Show the stack all.\n");
    output1("\n");
    output1("[Veriables]\n");
    output1("  v                     Show variables in a current frame.\n");
    output1("  vf [N]                Show variables of [N]th frame on the stack.\n");
    output1("  vl [N]                Show variables of [N]th lexical frame.\n");
    output1("  v [Name]              Show details of a variable in a current frame.\n");
    output1("  v [Name] [Val] [Type] Set the value to a variable in a current frame.\n");
    output1("                        Name: Variable name with index or property name.\n");
    output1("                              ex) name, name.prop[1].next\n");
    output1("                        Type: i ... int\n");
    output1("                              d ... dbl\n");
    output1("                              s ... str\n");
    output1("                              * auto detect by [Val] if not specified.\n");
    output1("\n");
    output1("[Source Code]\n");
    output1("  c                     Show a source code of a current function.\n");
    output1("  c all                 Show all of a current source code.\n");
    output1("  d                     Dump an IR code of a current function.\n");
    output1("  d all                 Dump an IR code of a current source code.\n");
}

static int do_command(int *r, int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *s)
{
    kstr_t *arg[KXDS];
    for (int i = 0; i < KXDS; ++i) {
        arg[i] = allocate_str(ctx);
    }

    int loop = 0;
SETUP_COMMAND:
    if (loop > 5) {
        error1("Detected a history loop, enter command again.\n");
        return 1;
    }
    setup_command(arg, s);
    const char *cmd = ks_string(arg[0]);
    if (*cmd == 0) {
        return 1;
    }

    if (!strcmp(cmd, "q")) {
        *r = 0;     // Terminate the Program
        return 0;   // Debugger Prompt Loop end
    }

    if ((!strcmp(cmd, "!") && is_number(arg[1])) || !strcmp(cmd, "!!")) {
        int sidx = 0;
        if (!strcmp(cmd, "!!")) {
            sidx = -1;
        } else {
            sidx = (int)strtol(ks_string(arg[1]), NULL, 0);
        }
        kstr_t *ns = do_command_get_command(sidx);
        if (!ns) {
            char *buf = conv_utf82acp_alloc(ks_string(s));
            error("Could not find a command in history: %s\n", buf);
            conv_free(buf);
            return 1;
        }
        for (int i = 0; i < KXDS; ++i) {
            ks_clear(arg[i]);
        }
        s = ns;
        char *buf = conv_utf82acp_alloc(ks_string(s));
        message("Command: %s\n", buf);
        conv_free(buf);
        ++loop;
        goto SETUP_COMMAND;
    }

    if (!strcmp(cmd, "n")) {
        ctx->options.debug_step = 1;
        *r = 1;
        return 0;   // Debugger Prompt Loop end
    } else if (!strcmp(cmd, "nn")) {
        // Step out.
        ctx->stepout_file = location->file;
        ctx->options.debug_step = 1;
        *r = 1;
        return 0;   // Debugger Prompt Loop end
    } else if (!strcmp(cmd, "h") || !strcmp(cmd, "help")) {
        usage();
    } else if (!strcmp(cmd, "!") || !strcmp(cmd, "history")) {
        do_command_show_history(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "s")) {
        do_command_stack(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "v")) {
        do_command_variable(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "b")) {
        do_command_breakpoint(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "f")) {
        do_command_frm(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "l")) {
        do_command_lex(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "vf")) {
        do_command_frm_var(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "vl")) {
        do_command_lex_var(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "mf") || !strcmp(cmd, "ml")) {
        do_command_move_frame(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "c")) {
        do_command_sourcecode(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "d")) {
        do_command_dumpcode(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "r")) {
        *r = 1;     // Restart the Program
        return 0;   // Debugger Prompt Loop end
    } else {
        char *buf = conv_utf82acp_alloc(ks_string(s));
        error("Unknown command: '%s'\n", buf);
        conv_free(buf);
    }

    return 1;   // Continue the Debugger
}

static int Debugger_prompt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location)
{
    const char *file = location->file;
    int line = location->line;
    if (line == 0) {
        /* Ignore when the line was not set.  */
        return 1;
    }
    if (line < 0) {
        line = location->line = 0;
    }

    /* Reset once. */
    ctx->options.debug_step = 0;
    ctx->stepout_file = NULL;

    int r = 1;
    if (line > 0) {
        message("Break at %s:%d\n", file, line);
    } else {
        message("Break before starting at %s\n", file);
    }
    kx_frm_t *cfrm = frmv;
    kstr_t *s;
    while (1) {
        prompt_start();
        s = prompt(ctx);
        prompt_end();
        ks_trim(s);
        if (ks_length(s) > 0) {
            if (!do_command(&r, args, frmv, lexv, ctx, location, &cfrm, s)) {
                break;
            }
        }
    }

    return r;
}

int Debugger_start(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* this method will/must be called at the startup. */
    if (!ctx->objs.debugger_prompt) {
        ctx->objs.debugger_prompt = Debugger_prompt; // setup this method at the startup.
    }

    const char *file = get_arg_str(1, args, ctx);
    int line = get_arg_int(2, args, ctx);

    int r = Debugger_prompt(args, frmv, lexv, ctx, &(kx_location_t){
        .file = file,
        .line = line,
    });

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "_startDebugger", Debugger_start },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, kx_debugger_init, kx_debugger_fin);
