PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib
SRCDIR = ../src
INCDIR = ../include
KXLIBD = ../lib
DOCDIR = ../docs
DEPFILE	= Makefile.dep
CDIR = $(PWD)

VER_HASH := $(shell git rev-parse HEAD)
CC = gcc
GCCV8 := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 8)
#CFLAGS = -DKX_PROFILE -DKX_DIRECT_THREAD -DYYMALLOC=kx_malloc -DYYFREE=kx_free -I$(INCDIR) -O2 \
	 -fno-crossjumping -Wno-unused-result -Wno-missing-braces -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
CFLAGS = -DNDEBUG -DKX_DIRECT_THREAD -DYYMALLOC=kx_malloc -DYYFREE=kx_free -DVER_HASH=$(VER_HASH) -I$(INCDIR) \
	 -O2 -fno-crossjumping -Wno-trigraphs -Wno-unused-result -Wno-missing-braces \
	 -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
ifeq "$(GCCV8)" "1"
        CFLAGS += -mshstk
endif
OBJS = \
    allocator.o \
    alloccore.o \
    allocutil.o \
    ast_analyzer.o \
    ast_display.o \
    ast_defdisp.o \
    ast_gencode.o \
    ast_object.o \
    ast_native.o \
    bign.o \
    bigz.o \
    getopt.o \
    global.o \
    ir_dump.o \
    ir_dot.o \
    ir_execdbg.o \
    ir_exec.o \
    ir_fix.o \
    ir_util.o \
    ir_aotcore.o \
    ir_aotdump.o \
    ir_natutil.o \
    jit_util.o \
    nir_compile.o \
    nir_dump.o \
    nir_dot.o \
    kstr.o \
    lexer.o \
    fileutil.o \
    loadlib.o \
    mainlib.o \
    parser.o \
    format.o \
    string.o \
    optimizer.o \
    opt_cfold.o \
    opt_jumpx.o
SRCS = $(patsubst %.o,$(SRCDIR)/%.c,$(OBJS))
SLJIT_DEP = \
    $(SRCDIR)/jit/sljitConfig.h \
    $(SRCDIR)/jit/sljitConfigInternal.h \
    $(SRCDIR)/jit/sljitExecAllocator.c \
    $(SRCDIR)/jit/sljitLir.c \
    $(SRCDIR)/jit/sljitLir.h \
    $(SRCDIR)/jit/sljitNativeARM_32.c \
    $(SRCDIR)/jit/sljitNativeARM_64.c \
    $(SRCDIR)/jit/sljitNativeARM_T2_32.c \
    $(SRCDIR)/jit/sljitNativeMIPS_32.c \
    $(SRCDIR)/jit/sljitNativeMIPS_64.c \
    $(SRCDIR)/jit/sljitNativeMIPS_common.c \
    $(SRCDIR)/jit/sljitNativePPC_32.c \
    $(SRCDIR)/jit/sljitNativePPC_64.c \
    $(SRCDIR)/jit/sljitNativePPC_common.c \
    $(SRCDIR)/jit/sljitNativeSPARC_32.c \
    $(SRCDIR)/jit/sljitNativeSPARC_common.c \
    $(SRCDIR)/jit/sljitNativeTILEGX-encoder.c \
    $(SRCDIR)/jit/sljitNativeTILEGX_64.c \
    $(SRCDIR)/jit/sljitNativeX86_32.c \
    $(SRCDIR)/jit/sljitNativeX86_64.c \
    $(SRCDIR)/jit/sljitNativeX86_common.c \
    $(SRCDIR)/jit/sljitProtExecAllocator.c \
    $(SRCDIR)/jit/sljitUtils.c
IR_EXEC_DEP = \
    $(SRCDIR)/exec/code/_except.inc \
    $(SRCDIR)/exec/code/_inlines.inc \
    $(SRCDIR)/exec/code/add.inc \
    $(SRCDIR)/exec/code/and.inc \
    $(SRCDIR)/exec/code/append.inc \
    $(SRCDIR)/exec/code/apply.inc \
    $(SRCDIR)/exec/code/call.inc \
    $(SRCDIR)/exec/code/catch.inc \
    $(SRCDIR)/exec/code/dec.inc \
    $(SRCDIR)/exec/code/div.inc \
    $(SRCDIR)/exec/code/enter.inc \
    $(SRCDIR)/exec/code/eqeq.inc \
    $(SRCDIR)/exec/code/ge.inc \
    $(SRCDIR)/exec/code/gt.inc \
    $(SRCDIR)/exec/code/haltnop.inc \
    $(SRCDIR)/exec/code/inc.inc \
    $(SRCDIR)/exec/code/jmp.inc \
    $(SRCDIR)/exec/code/le.inc \
    $(SRCDIR)/exec/code/lge.inc \
    $(SRCDIR)/exec/code/lt.inc \
    $(SRCDIR)/exec/code/mkary.inc \
    $(SRCDIR)/exec/code/mod.inc \
    $(SRCDIR)/exec/code/mul.inc \
    $(SRCDIR)/exec/code/neg.inc \
    $(SRCDIR)/exec/code/neq.inc \
    $(SRCDIR)/exec/code/not.inc \
    $(SRCDIR)/exec/code/or.inc \
    $(SRCDIR)/exec/code/pop.inc \
    $(SRCDIR)/exec/code/push.inc \
    $(SRCDIR)/exec/code/ret.inc \
    $(SRCDIR)/exec/code/shl.inc \
    $(SRCDIR)/exec/code/shr.inc \
    $(SRCDIR)/exec/code/store.inc \
    $(SRCDIR)/exec/code/sub.inc \
    $(SRCDIR)/exec/code/throw.inc \
    $(SRCDIR)/exec/code/xor.inc
DISASM = \
    decode.o \
    itab.o \
    syn-att.o \
    syn-intel.o \
    syn.o \
    udis86.o
SOFILES = \
    kxsystem.so \
    kxstring.so \
    kxbinary.so \
    kxinteger.so \
    kxdouble.so \
    kxarray.so \
    kxfile.so \
    kxdebugger.so \
    kxmath.so \
    kxregex.so \
    kxsqlite.so \
    kxnet.so \
    kxxml.so \
    kxpdf.so \
    kxssh.so \
    kxjit.so \
    kxprocess.so \
    libz.so \
    libssl.so \
    libcrypto.so
PICOBJS = \
    bign.o \
    bigz.o \
    allocutil.o \
    fileutil.o \
    format.o \
    kstr.o

all: timex kinx $(SOFILES) main_kxcmd

install:
	mkdir -p /usr/bin/kinxlib/include
	mkdir -p /usr/bin/kinxlib/docs/licenses
	mkdir -p /usr/bin/kinxlib/package
	cp -f ./kinx /usr/bin/kinx
	cp -f ./kxrepl /usr/bin/kxrepl
	cp -f ./kxtest /usr/bin/kxtest
	cp -rf $(KXLIBD)/* /usr/bin/kinxlib/
	cp -f ./kxsel /usr/bin/kinxlib/kxsel
	cp -f $(DOCDIR)/licenses/LICENSE.* /usr/bin/kinxlib/docs/licenses/
	cp -f $(INCDIR)/libkinx.h /usr/bin/kinxlib/include/libkinx.h
	cp -f $(INCDIR)/fileutil.h /usr/bin/kinxlib/include/fileutil.h
	cp -f libkx.a /usr/bin/kinxlib/
	cp -f libkinx.so /usr/bin/kinxlib/
	cp -f kxarray.so /usr/bin/kinxlib/
	cp -f kxbinary.so /usr/bin/kinxlib/
	cp -f kxdouble.so /usr/bin/kinxlib/
	cp -f kxfile.so /usr/bin/kinxlib/
	cp -f kxdebugger.so /usr/bin/kinxlib/
	cp -f kxinteger.so /usr/bin/kinxlib/
	cp -f kxmath.so /usr/bin/kinxlib/
	cp -f kxnet.so /usr/bin/kinxlib/
	cp -f kxregex.so /usr/bin/kinxlib/
	cp -f kxsqlite.so /usr/bin/kinxlib/
	cp -f kxstring.so /usr/bin/kinxlib/
	cp -f kxsystem.so /usr/bin/kinxlib/
	cp -f kxxml.so /usr/bin/kinxlib/
	cp -f kxpdf.so /usr/bin/kinxlib/
	cp -f kxssh.so /usr/bin/kinxlib/
	cp -f kxjit.so /usr/bin/kinxlib/
	cp -f kxprocess.so /usr/bin/kinxlib/
	cp -f libonig.so.5.1.0 /usr/bin/kinxlib/
	ln -sf /usr/bin/kinxlib/libonig.so.5.1.0 /usr/bin/kinxlib/libonig.so.5
	ln -sf /usr/bin/kinxlib/libonig.so.5 /usr/bin/kinxlib/libonig.so
	cp -f libz.so.1.2.11 /usr/bin/kinxlib/
	cp -f libssl.so.3 /usr/bin/kinxlib/
	cp -f libcrypto.so.3 /usr/bin/kinxlib/
	ln -sf /usr/bin/kinxlib/libz.so.1.2.11 /usr/bin/kinxlib/libz.so.1
	ln -sf /usr/bin/kinxlib/libz.so.1 /usr/bin/kinxlib/libz.so
	ln -sf /usr/bin/kinxlib/libssl.so.3 /usr/bin/kinxlib/libssl.so
	ln -sf /usr/bin/kinxlib/libcrypto.so.3 /usr/bin/kinxlib/libcrypto.so
	rm -f /usr/bin/kinxlib/exec/3rdparty/.gitignore

timex:
	$(CC) $(CFLAGS) -o timex utility/src/timex.c

clean:
	rm -f $(OBJS) $(DISASM) *.o *.so* timex kinx myacc test main_kxcmd
	rm -f $(SRCDIR)/optimizer.c $(SRCDIR)/opt_*.c

kinx: $(SRCDIR)/main.c libkinx.so
	./timex $(CC) $(CFLAGS) -o $@ $(SRCDIR)/main.c fileutil.o -ldl

main_kxcmd: $(SRCDIR)/main_kxcmd.c libkinx.so
	./timex $(CC) $(CFLAGS) -o $@ $(SRCDIR)/main_kxcmd.c fileutil.o -ldl
	cp -f main_kxcmd kxrepl
	cp -f main_kxcmd kxtest
	cp -f main_kxcmd kxkitty

libkinx.so: $(SRCDIR)/optimizer.c $(SRCDIR)/parser.c $(INCDIR)/parser.tab.h libonig.so $(OBJS) $(DISASM)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $(OBJS) $(DISASM) -ldl -lm
	ar rcs libkx.a fileutil.o

kxsystem.so: $(SRCDIR)/extlib/kxsystem.c $(SRCDIR)/extlib/kc-json/dist/kc-json.h kc-json.o duktape.o picosat.o libclipboard.a $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) kc-json.o duktape.o picosat.o libclipboard.a -lm -lxcb

kxstring.so: $(SRCDIR)/extlib/kxstring.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxbinary.so: $(SRCDIR)/extlib/kxbinary.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxinteger.so: $(SRCDIR)/extlib/kxinteger.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxdouble.so: $(SRCDIR)/extlib/kxdouble.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxarray.so: $(SRCDIR)/extlib/kxarray.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxfile.so: $(SRCDIR)/extlib/kxfile.c $(PICOBJS) libz.so libcrypto.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) $(SRCDIR)/extlib/zip/x64/gcc/libminizip.a -Wl,-rpath,'$$ORIGIN' -L. -lcrypto -lz

kxdebugger.so: $(SRCDIR)/extlib/kxdebugger.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -Wl,-rpath,'$$ORIGIN'

kxmath.so: $(SRCDIR)/extlib/kxmath.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -lm

kxregex.so: $(SRCDIR)/extlib/kxregex.c $(PICOBJS) libonig.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -Wl,-rpath,'$$ORIGIN' -L. -lonig

kxsqlite.so: $(SRCDIR)/extlib/kxsqlite.c $(PICOBJS) sqlite3.o
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) sqlite3.o -pthread

kxnet.so: $(SRCDIR)/extlib/kxnet.c $(PICOBJS) libssl.so libcrypto.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) $(SRCDIR)/extlib/libcurl/x64/gcc/libcurl.a $(SRCDIR)/extlib/zip/x64/gcc/libminizip.a -pthread -ldl -Wl,-rpath,'$$ORIGIN' -L. -lz -lcrypto -lssl

kxxml.so: $(SRCDIR)/extlib/kxxml.c $(PICOBJS) $(SRCDIR)/extlib/libxml2/x64/gcc/libxml2.a libz.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -I $(SRCDIR)/extlib/libxml2/include/libxml2 $(SRCDIR)/extlib/libxml2/x64/gcc/libxml2.a -Wl,-rpath,'$$ORIGIN' -L. -lz

kxpdf.so: $(SRCDIR)/extlib/kxpdf.c $(PICOBJS) $(SRCDIR)/extlib/libharu/x64/gcc/libhpdf.a $(SRCDIR)/extlib/libharu/x64/gcc/libpng.a libz.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -I $(SRCDIR)/extlib/libharu/include $(SRCDIR)/extlib/libharu/x64/gcc/libhpdf.a $(SRCDIR)/extlib/libharu/x64/gcc/libpng.a -Wl,-rpath,'$$ORIGIN' -lm -L. -lz

kxssh.so: $(SRCDIR)/extlib/kxssh.c $(PICOBJS) libssl.so libcrypto.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) $(SRCDIR)/extlib/libssh2/x64/gcc/libssh2.a -Wl,-rpath,'$$ORIGIN' -L. -lonig -pthread -lcrypto

kxprocess.so: $(SRCDIR)/extlib/kxprocess.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxjit.so: $(SRCDIR)/extlib/kxjit.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) $(DISASM) ir_aotcore.o

libz.so: libz.so.1
	ln -s libz.so.1 libz.so

libz.so.1: libz.so.1.2.11
	ln -s libz.so.1.2.11 libz.so.1

libz.so.1.2.11: $(SRCDIR)/extlib/zip/x64/gcc/libz.so.1.2.11
	cp -f $(SRCDIR)/extlib/zip/x64/gcc/libz.so.1.2.11 ./libz.so.1.2.11
	chmod +x libz.so.1.2.11

libssl.so:
	cp -f $(SRCDIR)/extlib/openssl/x64/gcc/libssl.so.3 ./libssl.so.3
	ln -s libssl.so.3 libssl.so

libcrypto.so:
	cp -f $(SRCDIR)/extlib/openssl/x64/gcc/libcrypto.so.3 ./libcrypto.so.3
	ln -s libcrypto.so.3 libcrypto.so

$(SRCDIR)/optimizer.c: $(SRCDIR)/optimizer/optimizer.c
	cp -f $(SRCDIR)/optimizer/optimizer.c $(SRCDIR)
	cp -f $(SRCDIR)/optimizer/opt_*.c $(SRCDIR)
	cp -f $(SRCDIR)/optimizer/opt_*.c $(SRCDIR)

$(SRCDIR)/parser.c: kx.tab.c
	mv -f kx.tab.c $(SRCDIR)/parser.c

$(INCDIR)/parser.tab.h: kx.tab.h
	mv -f kx.tab.h $(INCDIR)/parser.tab.h

kx.tab.c: $(SRCDIR)/kinx.y
	utility/kmyacc -v -d -m utility/kmyacc.c.parser -b kx -p kx_yy $(SRCDIR)/kinx.y;

kx.tab.h: $(SRCDIR)/kinx.y
	utility/kmyacc -v -d -m utility/kmyacc.c.parser -b kx -p kx_yy $(SRCDIR)/kinx.y;

libonig.so:
	cd $(SRCDIR)/extlib/onig; \
	autoreconf -vfi; \
	./configure --with-pic; \
	make; \
	cp -f src/.libs/libonig.so.5.1.0 $(CDIR);
	ln -s libonig.so.5.1.0 libonig.so.5; \
	ln -s libonig.so.5 libonig.so;

$(SRCDIR)/extlib/kc-json/dist/kc-json.h:
	cd $(SRCDIR)/extlib/kc-json; \
	make -f Makefile clean all

kc-json.o: $(SRCDIR)/extlib/kc-json/dist/kc-json.c $(SRCDIR)/extlib/kc-json/dist/kc-json.h
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

duktape.o: $(SRCDIR)/extlib/duktape/duktape.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

picosat.o: $(SRCDIR)/extlib/picosat/picosat.c
	./timex $(CC) -fPIC -c -DNGETRUSAGE $(CFLAGS) -o $@ $<

libclipboard.a: $(SRCDIR)/extlib/libclipboard/src/clipboard_x11.c
	cd $(SRCDIR)/extlib/libclipboard/; make

sqlite3.o: $(SRCDIR)/extlib/sqlite/sqlite3.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: $(SRCDIR)/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: $(SRCDIR)/optimizer/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: $(SRCDIR)/optimizer/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: $(SRCDIR)/optimizer/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: $(SRCDIR)/disasm-x64/libudis86/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

$(SRCDIR)/ir_aotcore.o: $(SRCDIR)/ir_aotcore.c $(SLJIT_DEP)
	./timex $(CC) -c $(CFLAGS) -o $@ $(SRCDIR)/ir_aotcore.c

$(SRCDIR)/ir_exec.c: $(INCDIR)/ir.h $(INCDIR)/kinx.h $(IR_EXEC_DEP)
$(SRCDIR)/ir_execdbg.c: $(INCDIR)/ir.h $(INCDIR)/kinx.h $(IR_EXEC_DEP)

depend: $(DEPFILE)

$(DEPFILE): $(SRCS)
	$(CC) $(CFLAGS) -MM $(SRCS) > $(DEPFILE)

allocator.o: $(SRCDIR)/allocator.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h $(INCDIR)/kvec.h \
 $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
alloccore.o: $(SRCDIR)/alloccore.c
allocutil.o: $(SRCDIR)/allocutil.c $(INCDIR)/dbg.h $(INCDIR)/ir.h $(INCDIR)/kvec.h \
 $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h \
 $(INCDIR)/bign.h $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
ast_analyzer.o: $(SRCDIR)/ast_analyzer.c $(INCDIR)/dbg.h $(INCDIR)/parser.h \
 $(INCDIR)/kinx.h $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h \
 $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h \
 $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/parser.tab.h
ast_display.o: $(SRCDIR)/ast_display.c $(INCDIR)/dbg.h $(INCDIR)/parser.h \
 $(INCDIR)/kinx.h $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h \
 $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h \
 $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/parser.tab.h
ast_defdisp.o: $(SRCDIR)/ast_defdisp.c $(INCDIR)/dbg.h $(INCDIR)/parser.h \
 $(INCDIR)/kinx.h $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h \
 $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h \
 $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/parser.tab.h
ast_gencode.o: $(SRCDIR)/ast_gencode.c $(INCDIR)/dbg.h $(INCDIR)/kvec.h \
 $(INCDIR)/kinx.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
ast_object.o: $(SRCDIR)/ast_object.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
ast_native.o: $(SRCDIR)/ast_native.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxnative.h
bign.o: $(SRCDIR)/bign.c $(INCDIR)/dbg.h $(INCDIR)/bign.h
bigz.o: $(SRCDIR)/bigz.c $(INCDIR)/dbg.h $(INCDIR)/bigz.h $(INCDIR)/bign.h
getopt.o: $(SRCDIR)/getopt.c $(INCDIR)/dbg.h $(INCDIR)/getopt.h
global.o: $(SRCDIR)/global.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h $(INCDIR)/kvec.h \
 $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxthread.h
ir_dump.o: $(SRCDIR)/ir_dump.c $(INCDIR)/dbg.h $(INCDIR)/kvec.h $(INCDIR)/kinx.h \
 $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
ir_exec.o: $(SRCDIR)/ir_exec.c $(INCDIR)/dbg.h $(INCDIR)/kvec.h $(INCDIR)/kstr.h \
 $(INCDIR)/kinx.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxexec.h \
 $(SRCDIR)/exec/code/_except.inc $(SRCDIR)/exec/code/_inlines.inc \
 $(SRCDIR)/exec/code/haltnop.inc $(SRCDIR)/exec/code/enter.inc $(SRCDIR)/exec/code/call.inc \
 $(SRCDIR)/exec/code/ret.inc $(SRCDIR)/exec/code/throw.inc $(SRCDIR)/exec/code/catch.inc \
 $(SRCDIR)/exec/code/jmp.inc $(SRCDIR)/exec/code/push.inc $(SRCDIR)/exec/code/pop.inc \
 $(SRCDIR)/exec/code/store.inc $(SRCDIR)/exec/code/bnot.inc $(SRCDIR)/exec/code/not.inc \
 $(SRCDIR)/exec/code/neg.inc $(SRCDIR)/exec/code/inc.inc $(SRCDIR)/exec/code/dec.inc \
 $(SRCDIR)/exec/code/mkary.inc $(SRCDIR)/exec/code/append.inc $(SRCDIR)/exec/code/apply.inc \
 $(SRCDIR)/exec/code/add.inc $(SRCDIR)/exec/code/sub.inc $(SRCDIR)/exec/code/pow.inc \
 $(SRCDIR)/exec/code/mul.inc $(SRCDIR)/exec/code/div.inc $(SRCDIR)/exec/code/mod.inc \
 $(SRCDIR)/exec/code/and.inc $(SRCDIR)/exec/code/or.inc $(SRCDIR)/exec/code/xor.inc \
 $(SRCDIR)/exec/code/shl.inc $(SRCDIR)/exec/code/shr.inc $(SRCDIR)/exec/code/eqeq.inc \
 $(SRCDIR)/exec/code/neq.inc $(SRCDIR)/exec/code/le.inc $(SRCDIR)/exec/code/lt.inc \
 $(SRCDIR)/exec/code/ge.inc $(SRCDIR)/exec/code/gt.inc $(SRCDIR)/exec/code/lge.inc \
 $(SRCDIR)/exec/code/regeq.inc
ir_execdbg.o: $(SRCDIR)/ir_execdbg.c $(INCDIR)/dbg.h $(INCDIR)/kvec.h $(INCDIR)/kstr.h \
 $(INCDIR)/kinx.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxexec.h \
 $(SRCDIR)/exec/code/_except.inc $(SRCDIR)/exec/code/_inlines.inc \
 $(SRCDIR)/exec/code/haltnop.inc $(SRCDIR)/exec/code/enter.inc $(SRCDIR)/exec/code/call.inc \
 $(SRCDIR)/exec/code/ret.inc $(SRCDIR)/exec/code/throw.inc $(SRCDIR)/exec/code/catch.inc \
 $(SRCDIR)/exec/code/jmp.inc $(SRCDIR)/exec/code/push.inc $(SRCDIR)/exec/code/pop.inc \
 $(SRCDIR)/exec/code/store.inc $(SRCDIR)/exec/code/bnot.inc $(SRCDIR)/exec/code/not.inc \
 $(SRCDIR)/exec/code/neg.inc $(SRCDIR)/exec/code/inc.inc $(SRCDIR)/exec/code/dec.inc \
 $(SRCDIR)/exec/code/mkary.inc $(SRCDIR)/exec/code/append.inc $(SRCDIR)/exec/code/apply.inc \
 $(SRCDIR)/exec/code/add.inc $(SRCDIR)/exec/code/sub.inc $(SRCDIR)/exec/code/pow.inc \
 $(SRCDIR)/exec/code/mul.inc $(SRCDIR)/exec/code/div.inc $(SRCDIR)/exec/code/mod.inc \
 $(SRCDIR)/exec/code/and.inc $(SRCDIR)/exec/code/or.inc $(SRCDIR)/exec/code/xor.inc \
 $(SRCDIR)/exec/code/shl.inc $(SRCDIR)/exec/code/shr.inc $(SRCDIR)/exec/code/eqeq.inc \
 $(SRCDIR)/exec/code/neq.inc $(SRCDIR)/exec/code/le.inc $(SRCDIR)/exec/code/lt.inc \
 $(SRCDIR)/exec/code/ge.inc $(SRCDIR)/exec/code/gt.inc $(SRCDIR)/exec/code/lge.inc \
 $(SRCDIR)/exec/code/regeq.inc
ir_fix.o: $(SRCDIR)/ir_fix.c $(INCDIR)/dbg.h $(INCDIR)/kvec.h $(INCDIR)/ir.h \
 $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h \
 $(INCDIR)/bign.h $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
ir_util.o: $(SRCDIR)/ir_util.c $(INCDIR)/dbg.h $(INCDIR)/kvec.h $(INCDIR)/kstr.h \
 $(INCDIR)/kinx.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxexec.h \
 $(INCDIR)/kxthread.h $(SRCDIR)/exec/code/_inlines.inc
ir_aotcore.o: $(SRCDIR)/ir_aotcore.c $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(SRCDIR)/jit/sljitLir.c \
 $(SRCDIR)/jit/sljitLir.h $(SRCDIR)/jit/sljitUtils.c $(SRCDIR)/jit/sljitExecAllocator.c \
 $(SRCDIR)/jit/sljitNativeX86_common.c $(SRCDIR)/jit/sljitNativeX86_64.c
ir_aotdump.o: $(SRCDIR)/ir_aotdump.c $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(SRCDIR)/disasm/disas.h \
 $(SRCDIR)/disasm/arch/x86/x86load.h $(SRCDIR)/disasm/arch/x86/../../common/file.h \
 $(SRCDIR)/disasm/arch/x86/../../common/trie.h \
 $(SRCDIR)/disasm/arch/x86/../../common/table.h $(SRCDIR)/disasm/arch/x86/x86.h \
 $(SRCDIR)/disasm/arch/x86/../../dis.h \
 $(SRCDIR)/disasm/arch/x86/../../common/common.h \
 $(SRCDIR)/disasm/arch/x86/../../common/common.h \
 $(SRCDIR)/disasm/arch/x86/x86strings.h $(SRCDIR)/disasm/arch/x86/x86load.h \
 $(SRCDIR)/disasm/arch/x86/x86asm.h $(SRCDIR)/disasm/arch/x86/x86.h \
 $(SRCDIR)/disasm/arch/mips/mload.h $(SRCDIR)/disasm/arch/mips/../../common/file.h \
 $(SRCDIR)/disasm/arch/mips/../../common/trie.h \
 $(SRCDIR)/disasm/arch/mips/../../common/table.h $(SRCDIR)/disasm/arch/mips/mips.h \
 $(SRCDIR)/disasm/arch/mips/../../common/common.h \
 $(SRCDIR)/disasm/arch/mips/../../dis.h $(SRCDIR)/disasm/arch/mips/mload.h \
 $(SRCDIR)/disasm/arch/mips/mstrings.h $(SRCDIR)/disasm/arch/arm/aload.h \
 $(SRCDIR)/disasm/arch/arm/../../common/file.h \
 $(SRCDIR)/disasm/arch/arm/../../common/trie.h \
 $(SRCDIR)/disasm/arch/arm/../../common/table.h $(SRCDIR)/disasm/arch/arm/arm.h \
 $(SRCDIR)/disasm/arch/arm/aload.h $(SRCDIR)/disasm/arch/arm/astrings.h \
 $(SRCDIR)/disasm/arch/arm/../../common/common.h \
 $(SRCDIR)/disasm/arch/arm/../../dis.h $(SRCDIR)/disasm/dis.h $(SRCDIR)/disasm/dss.h \
 $(SRCDIR)/disasm/common/table.h $(SRCDIR)/disasm/lex.h $(SRCDIR)/disasm/sym.h \
 $(SRCDIR)/disasm/common/trie.h
ir_natutil.o: $(SRCDIR)/ir_natutil.c $(INCDIR)/kinx.h $(INCDIR)/kvec.h $(INCDIR)/ir.h \
 $(INCDIR)/dbg.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
nir_compile.o: $(SRCDIR)/nir_compile.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxnative.h
nir_dump.o: $(SRCDIR)/nir_dump.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h $(INCDIR)/kvec.h \
 $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxnative.h
kstr.o: $(SRCDIR)/kstr.c $(INCDIR)/dbg.h $(INCDIR)/kstr.h
lexer.o: $(SRCDIR)/lexer.c $(INCDIR)/dbg.h $(INCDIR)/parser.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h \
 $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/parser.tab.h
fileutil.o: $(SRCDIR)/fileutil.c $(INCDIR)/dbg.h $(INCDIR)/fileutil.h
loadlib.o: $(SRCDIR)/loadlib.c $(INCDIR)/dbg.h $(INCDIR)/fileutil.h \
 $(INCDIR)/kxthread.h
mainlib.o: $(SRCDIR)/mainlib.c $(INCDIR)/dbg.h $(INCDIR)/kinx.h $(INCDIR)/kvec.h \
 $(INCDIR)/version.h \
 $(INCDIR)/ir.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h $(INCDIR)/kxthread.h \
 $(INCDIR)/getopt.h
parser.o: $(SRCDIR)/parser.c $(INCDIR)/kvec.h $(INCDIR)/kinx.h $(INCDIR)/ir.h \
 $(INCDIR)/dbg.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
format.o: $(SRCDIR)/format.c $(INCDIR)/kinx.h $(INCDIR)/kvec.h $(INCDIR)/ir.h \
 $(INCDIR)/dbg.h $(INCDIR)/khash.h $(INCDIR)/klist.h $(INCDIR)/kstr.h \
 $(INCDIR)/bigz.h $(INCDIR)/bign.h $(INCDIR)/jit.h \
 $(INCDIR)/../src/jit/sljitLir.h $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
string.o: $(SRCDIR)/string.c $(INCDIR)/dbg.h $(INCDIR)/khash.h $(INCDIR)/ir.h \
 $(INCDIR)/kvec.h $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h \
 $(INCDIR)/bign.h $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
optimizer.o: $(SRCDIR)/optimizer/optimizer.c $(INCDIR)/kxoptimizer.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/dbg.h $(INCDIR)/khash.h \
 $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h \
 $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
opt_cfold.o: $(SRCDIR)/optimizer/opt_cfold.c $(INCDIR)/kxoptimizer.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/dbg.h $(INCDIR)/khash.h \
 $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h \
 $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h
opt_jumpx.o: $(SRCDIR)/optimizer/opt_jumpx.c $(INCDIR)/kxoptimizer.h $(INCDIR)/kinx.h \
 $(INCDIR)/kvec.h $(INCDIR)/ir.h $(INCDIR)/dbg.h $(INCDIR)/khash.h \
 $(INCDIR)/klist.h $(INCDIR)/kstr.h $(INCDIR)/bigz.h $(INCDIR)/bign.h \
 $(INCDIR)/jit.h $(INCDIR)/../src/jit/sljitLir.h \
 $(INCDIR)/../src/jit/sljitConfig.h \
 $(INCDIR)/../src/jit/sljitConfigInternal.h

