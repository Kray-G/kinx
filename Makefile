.POSIX:
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib
SRCDIR = $(CURDIR)$(.CURDIR)
DEPFILE	= Makefile.dep

CC = gcc
#CFLAGS = -DKX_PROFILE -DKX_DIRECT_THREAD -DYYMALLOC=kx_malloc -DYYFREE=kx_free -Iinclude -O2 \
	 -fno-crossjumping -Wno-unused-result -Wno-missing-braces -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
CFLAGS = -DKX_DIRECT_THREAD -DYYMALLOC=kx_malloc -DYYFREE=kx_free -Iinclude -O2 \
	 -fno-crossjumping -Wno-trigraphs -Wno-unused-result -Wno-missing-braces \
	 -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
OBJS = \
    allocator.o \
    alloccore.o \
    allocutil.o \
    ast_analyzer.o \
    ast_display.o \
    ast_gencode.o \
    ast_object.o \
    ast_native.o \
    bign.o \
    bigz.o \
    getopt.o \
    global.o \
    ir_dump.o \
    ir_dot.o \
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
SRCS = $(patsubst %.o,src/%.c,$(OBJS))
SLJIT_DEP = \
    src/jit/sljitConfig.h \
    src/jit/sljitConfigInternal.h \
    src/jit/sljitExecAllocator.c \
    src/jit/sljitLir.c \
    src/jit/sljitLir.h \
    src/jit/sljitNativeARM_32.c \
    src/jit/sljitNativeARM_64.c \
    src/jit/sljitNativeARM_T2_32.c \
    src/jit/sljitNativeMIPS_32.c \
    src/jit/sljitNativeMIPS_64.c \
    src/jit/sljitNativeMIPS_common.c \
    src/jit/sljitNativePPC_32.c \
    src/jit/sljitNativePPC_64.c \
    src/jit/sljitNativePPC_common.c \
    src/jit/sljitNativeSPARC_32.c \
    src/jit/sljitNativeSPARC_common.c \
    src/jit/sljitNativeTILEGX-encoder.c \
    src/jit/sljitNativeTILEGX_64.c \
    src/jit/sljitNativeX86_32.c \
    src/jit/sljitNativeX86_64.c \
    src/jit/sljitNativeX86_common.c \
    src/jit/sljitProtExecAllocator.c \
    src/jit/sljitUtils.c
IR_EXEC_DEP = \
    src/exec/code/_except.inc \
    src/exec/code/_inlines.inc \
    src/exec/code/add.inc \
    src/exec/code/and.inc \
    src/exec/code/append.inc \
    src/exec/code/apply.inc \
    src/exec/code/call.inc \
    src/exec/code/catch.inc \
    src/exec/code/dec.inc \
    src/exec/code/div.inc \
    src/exec/code/enter.inc \
    src/exec/code/eqeq.inc \
    src/exec/code/ge.inc \
    src/exec/code/gt.inc \
    src/exec/code/haltnop.inc \
    src/exec/code/inc.inc \
    src/exec/code/jmp.inc \
    src/exec/code/le.inc \
    src/exec/code/lge.inc \
    src/exec/code/lt.inc \
    src/exec/code/mkary.inc \
    src/exec/code/mod.inc \
    src/exec/code/mul.inc \
    src/exec/code/neg.inc \
    src/exec/code/neq.inc \
    src/exec/code/not.inc \
    src/exec/code/or.inc \
    src/exec/code/pop.inc \
    src/exec/code/push.inc \
    src/exec/code/ret.inc \
    src/exec/code/shl.inc \
    src/exec/code/shr.inc \
    src/exec/code/store.inc \
    src/exec/code/sub.inc \
    src/exec/code/throw.inc \
    src/exec/code/xor.inc
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
    kxmath.so \
    kxregex.so \
    kxsqlite.so \
    kxnet.so \
    kxxml.so \
    kxssh.so \
    kxjit.so \
    kxprocess.so
PICOBJS = \
    bign.o \
    bigz.o \
    allocutil.o \
    fileutil.o \
    format.o \
    kstr.o
TESTCORE = \
    apply \
    append \
    add \
    sub \
    mul \
    div \
    mod \
    shl \
    shr \
    inc \
    dec \
    lt \
    le \
    lge \
    gt \
    ge \
    eqeq \
    neq \
    and \
    or \
    xor \
    neg \
    not \
    push \
    store \
    call \
    mkary \
    ret \
    haltnop \
    trycatch \
    fib \

all: timex kinx $(SOFILES) main_kxcmd

install:
	if [ ! -d /usr/bin/kinxlib ]; then mkdir -p /usr/bin/kinxlib; fi;
	cp -f ./kinx /usr/bin/kinx
	cp -f ./kxrepl /usr/bin/kxrepl
	cp -f ./kxtest /usr/bin/kxtest
	cp -rf lib/* /usr/bin/kinxlib/
	mkdir -p /usr/bin/kinxlib/include
	cp -f include/libkinx.h /usr/bin/kinxlib/include/libkinx.h
	cp -f include/fileutil.h /usr/bin/kinxlib/include/fileutil.h
	cp -f libkx.a /usr/bin/kinxlib/
	cp -f libkinx.so /usr/bin/kinxlib/
	cp -f kxarray.so /usr/bin/kinxlib/
	cp -f kxbinary.so /usr/bin/kinxlib/
	cp -f kxdouble.so /usr/bin/kinxlib/
	cp -f kxfile.so /usr/bin/kinxlib/
	cp -f kxinteger.so /usr/bin/kinxlib/
	cp -f kxmath.so /usr/bin/kinxlib/
	cp -f kxnet.so /usr/bin/kinxlib/
	cp -f kxregex.so /usr/bin/kinxlib/
	cp -f kxsqlite.so /usr/bin/kinxlib/
	cp -f kxstring.so /usr/bin/kinxlib/
	cp -f kxsystem.so /usr/bin/kinxlib/
	cp -f kxxml.so /usr/bin/kinxlib/
	cp -f kxssh.so /usr/bin/kinxlib/
	cp -f kxjit.so /usr/bin/kinxlib/
	cp -f kxprocess.so /usr/bin/kinxlib/
	cp -f libcrypto.so.3 /usr/bin/kinxlib/
	cp -f libonig.so.5.0.0 /usr/bin/kinxlib/
	ln -sf /usr/bin/kinxlib/libonig.so.5.0.0 /usr/bin/kinxlib/libonig.so.5
	ln -sf /usr/bin/kinxlib/libonig.so.5 /usr/bin/kinxlib/libonig.so
	cp -f libssl.so.3 /usr/bin/kinxlib/
	cp -f libz.so.1.2.11 /usr/bin/kinxlib/
	ln -sf /usr/bin/kinxlib/libz.so.1 /usr/bin/kinxlib/libz.so
	ln -sf /usr/bin/kinxlib/libz.so.1.2.11 /usr/bin/kinxlib/libz.so.1

timex:
	$(CC) $(CFLAGS) -o timex timex.c

clean:
	rm -f $(OBJS) $(DISASM) $(SOFILES) $(PICOBJS) timex kinx myacc test main_kxcmd
	rm -f src/optimizer.c src/opt_*.c

kinx: src/main.c libkinx.so
	./timex $(CC) $(CFLAGS) -o $@ src/main.c fileutil.o -ldl

main_kxcmd: src/main_kxcmd.c libkinx.so
	./timex $(CC) $(CFLAGS) -o $@ src/main_kxcmd.c fileutil.o -ldl
	cp -f main_kxcmd kxrepl
	cp -f main_kxcmd kxtest

libkinx.so: src/optimizer.c src/parser.c include/parser.tab.h libonig.so $(OBJS) $(DISASM)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $(OBJS) $(DISASM) -ldl -lm
	ar rcs libkx.a fileutil.o

kxsystem.so: src/extlib/kxsystem.c src/extlib/kc-json/kc-json.h kc-json.o $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) kc-json.o

kxstring.so: src/extlib/kxstring.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxbinary.so: src/extlib/kxbinary.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxinteger.so: src/extlib/kxinteger.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxdouble.so: src/extlib/kxdouble.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxarray.so: src/extlib/kxarray.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxfile.so: src/extlib/kxfile.c $(PICOBJS) libz.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) src/extlib/zip/x64/gcc/libminizip.a -Wl,-rpath,'$$ORIGIN' -L. -lz

kxmath.so: src/extlib/kxmath.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -lm

kxregex.so: src/extlib/kxregex.c $(PICOBJS) libonig.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -Wl,-rpath,'$$ORIGIN' -L. -lonig

kxsqlite.so: src/extlib/kxsqlite.c $(PICOBJS) sqlite3.o
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) sqlite3.o -pthread

kxnet.so: src/extlib/kxnet.c $(PICOBJS) libssl.so.3 libcrypto.so.3
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) src/extlib/libcurl/x64/gcc/libcurl.a src/extlib/zip/x64/gcc/libminizip.a -pthread -ldl -Wl,-rpath,'$$ORIGIN' -L. -lz -lcrypto -lssl

kxxml.so: src/extlib/kxxml.c $(PICOBJS) src/extlib/libxml2/x64/gcc/libxml2.a libz.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -I src/extlib/libxml2/include/libxml2 src/extlib/libxml2/x64/gcc/libxml2.a -Wl,-rpath,'$$ORIGIN' -L. -lz

kxssh.so: src/extlib/kxssh.c $(PICOBJS) libssl.so.3 libcrypto.so.3
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) src/extlib/libssh2/x64/gcc/libssh2.a -Wl,-rpath,'$$ORIGIN' -L. -lonig -pthread -lcrypto

kxprocess.so: src/extlib/kxprocess.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxjit.so: src/extlib/kxjit.c $(PICOBJS)
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) $(DISASM) ir_aotcore.o

libz.so: libz.so.1
	ln -s libz.so.1 libz.so

libz.so.1: libz.so.1.2.11
	ln -s libz.so.1.2.11 libz.so.1

libz.so.1.2.11: src/extlib/zip/x64/gcc/libz.so.1.2.11
	cp -f src/extlib/zip/x64/gcc/libz.so.1.2.11 ./libz.so.1.2.11
	chmod +x libz.so.1.2.11

libssl.so.3:
	cp -f src/extlib/openssl/x64/gcc/libssl.so.3 ./libssl.so.3

libcrypto.so.3:
	cp -f src/extlib/openssl/x64/gcc/libcrypto.so.3 ./libcrypto.so.3

src/optimizer.c: src/optimizer/optimizer.c
	cp -f src/optimizer/optimizer.c src/
	cp -f src/optimizer/opt_*.c src/
	cp -f src/optimizer/opt_*.c src/

src/parser.c: kx.tab.c
	mv -f kx.tab.c src/parser.c

include/parser.tab.h: kx.tab.h
	mv -f kx.tab.h include/parser.tab.h

kx.tab.c: utility/kmyacc
	utility/kmyacc -v -d -m utility/kmyacc.c.parser -b kx -p kx_yy src/kinx.y;

kx.tab.h: utility/kmyacc
	utility/kmyacc -v -d -m utility/kmyacc.c.parser -b kx -p kx_yy src/kinx.y;

libonig.so:
	cd src/extlib/onig; \
	autoreconf -vfi; \
	./configure --with-pic; \
	make; \
	cp -f src/.libs/libonig.so.5.0.0 ../../../;
	ln -s libonig.so.5.0.0 libonig.so.5; \
	ln -s libonig.so.5 libonig.so;

kc-json.o: src/extlib/kc-json/kc-json.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

sqlite3.o: src/extlib/sqlite/sqlite3.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/optimizer/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/optimizer/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/optimizer/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/disasm-x64/libudis86/%.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

test-core: $(OBJS)
	for file in $(TESTCORE) ; do \
		$(CC) -Iinclude -o test src/exec/test/$$file.c \
			ir_exec.o ir_util.o ir_dump.o \
			allocator.o allocutil.o alloccore.o \
			kstr.o bign.o bigz.o string.o global.o loadlib.o \
			-lm -ldl; \
		echo Test $$file...\
		./test; \
		ret=$$?; \
		if [ $$ret = 0 ]; then \
			echo $$file Successful;\
		else \
			echo -------- $$file Failed;\
		fi; \
	done;

src/ir_aotcore.o: src/ir_aotcore.c $(SLJIT_DEP)
	./timex $(CC) -c $(CFLAGS) -o $@ src/ir_aotcore.c

src/ir_exec.c: include/ir.h include/kinx.h $(IR_EXEC_DEP)

depend: $(DEPFILE)

$(DEPFILE): $(SRCS)
	$(CC) $(CFLAGS) -MM $(SRCS) > $(DEPFILE)

allocator.o: src/allocator.c include/dbg.h include/kinx.h include/kvec.h \
 include/ir.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
alloccore.o: src/alloccore.c
allocutil.o: src/allocutil.c include/dbg.h include/ir.h include/kvec.h \
 include/khash.h include/klist.h include/kstr.h include/bigz.h \
 include/bign.h include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
ast_analyzer.o: src/ast_analyzer.c include/dbg.h include/parser.h \
 include/kinx.h include/kvec.h include/ir.h include/khash.h \
 include/klist.h include/kstr.h include/bigz.h include/bign.h \
 include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/parser.tab.h
ast_display.o: src/ast_display.c include/dbg.h include/parser.h \
 include/kinx.h include/kvec.h include/ir.h include/khash.h \
 include/klist.h include/kstr.h include/bigz.h include/bign.h \
 include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/parser.tab.h
ast_gencode.o: src/ast_gencode.c include/dbg.h include/kvec.h \
 include/kinx.h include/ir.h include/khash.h include/klist.h \
 include/kstr.h include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
ast_object.o: src/ast_object.c include/dbg.h include/kinx.h \
 include/kvec.h include/ir.h include/khash.h include/klist.h \
 include/kstr.h include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
ast_native.o: src/ast_native.c include/dbg.h include/kinx.h \
 include/kvec.h include/ir.h include/khash.h include/klist.h \
 include/kstr.h include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxnative.h
bign.o: src/bign.c include/dbg.h include/bign.h
bigz.o: src/bigz.c include/dbg.h include/bigz.h include/bign.h
getopt.o: src/getopt.c include/dbg.h include/getopt.h
global.o: src/global.c include/dbg.h include/kinx.h include/kvec.h \
 include/ir.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxthread.h
ir_dump.o: src/ir_dump.c include/dbg.h include/kvec.h include/kinx.h \
 include/ir.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
ir_exec.o: src/ir_exec.c include/dbg.h include/kvec.h include/kstr.h \
 include/kinx.h include/ir.h include/khash.h include/klist.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxexec.h \
 src/exec/code/_except.inc src/exec/code/_inlines.inc \
 src/exec/code/haltnop.inc src/exec/code/enter.inc src/exec/code/call.inc \
 src/exec/code/ret.inc src/exec/code/throw.inc src/exec/code/catch.inc \
 src/exec/code/jmp.inc src/exec/code/push.inc src/exec/code/pop.inc \
 src/exec/code/store.inc src/exec/code/bnot.inc src/exec/code/not.inc \
 src/exec/code/neg.inc src/exec/code/inc.inc src/exec/code/dec.inc \
 src/exec/code/mkary.inc src/exec/code/append.inc src/exec/code/apply.inc \
 src/exec/code/add.inc src/exec/code/sub.inc src/exec/code/pow.inc \
 src/exec/code/mul.inc src/exec/code/div.inc src/exec/code/mod.inc \
 src/exec/code/and.inc src/exec/code/or.inc src/exec/code/xor.inc \
 src/exec/code/shl.inc src/exec/code/shr.inc src/exec/code/eqeq.inc \
 src/exec/code/neq.inc src/exec/code/le.inc src/exec/code/lt.inc \
 src/exec/code/ge.inc src/exec/code/gt.inc src/exec/code/lge.inc \
 src/exec/code/regeq.inc
ir_fix.o: src/ir_fix.c include/dbg.h include/kvec.h include/ir.h \
 include/khash.h include/klist.h include/kstr.h include/bigz.h \
 include/bign.h include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
ir_util.o: src/ir_util.c include/dbg.h include/kvec.h include/kstr.h \
 include/kinx.h include/ir.h include/khash.h include/klist.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxexec.h \
 include/kxthread.h src/exec/code/_inlines.inc
ir_aotcore.o: src/ir_aotcore.c include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h src/jit/sljitLir.c \
 src/jit/sljitLir.h src/jit/sljitUtils.c src/jit/sljitExecAllocator.c \
 src/jit/sljitNativeX86_common.c src/jit/sljitNativeX86_64.c
ir_aotdump.o: src/ir_aotdump.c include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h src/disasm/disas.h \
 src/disasm/arch/x86/x86load.h src/disasm/arch/x86/../../common/file.h \
 src/disasm/arch/x86/../../common/trie.h \
 src/disasm/arch/x86/../../common/table.h src/disasm/arch/x86/x86.h \
 src/disasm/arch/x86/../../dis.h \
 src/disasm/arch/x86/../../common/common.h \
 src/disasm/arch/x86/../../common/common.h \
 src/disasm/arch/x86/x86strings.h src/disasm/arch/x86/x86load.h \
 src/disasm/arch/x86/x86asm.h src/disasm/arch/x86/x86.h \
 src/disasm/arch/mips/mload.h src/disasm/arch/mips/../../common/file.h \
 src/disasm/arch/mips/../../common/trie.h \
 src/disasm/arch/mips/../../common/table.h src/disasm/arch/mips/mips.h \
 src/disasm/arch/mips/../../common/common.h \
 src/disasm/arch/mips/../../dis.h src/disasm/arch/mips/mload.h \
 src/disasm/arch/mips/mstrings.h src/disasm/arch/arm/aload.h \
 src/disasm/arch/arm/../../common/file.h \
 src/disasm/arch/arm/../../common/trie.h \
 src/disasm/arch/arm/../../common/table.h src/disasm/arch/arm/arm.h \
 src/disasm/arch/arm/aload.h src/disasm/arch/arm/astrings.h \
 src/disasm/arch/arm/../../common/common.h \
 src/disasm/arch/arm/../../dis.h src/disasm/dis.h src/disasm/dss.h \
 src/disasm/common/table.h src/disasm/lex.h src/disasm/sym.h \
 src/disasm/common/trie.h
ir_natutil.o: src/ir_natutil.c include/kinx.h include/kvec.h include/ir.h \
 include/dbg.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
nir_compile.o: src/nir_compile.c include/dbg.h include/kinx.h \
 include/kvec.h include/ir.h include/khash.h include/klist.h \
 include/kstr.h include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxnative.h
nir_dump.o: src/nir_dump.c include/dbg.h include/kinx.h include/kvec.h \
 include/ir.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxnative.h
kstr.o: src/kstr.c include/dbg.h include/kstr.h
lexer.o: src/lexer.c include/dbg.h include/parser.h include/kinx.h \
 include/kvec.h include/ir.h include/khash.h include/klist.h \
 include/kstr.h include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/parser.tab.h
fileutil.o: src/fileutil.c include/dbg.h include/fileutil.h
loadlib.o: src/loadlib.c include/dbg.h include/fileutil.h \
 include/kxthread.h
mainlib.o: src/mainlib.c include/dbg.h include/kinx.h include/kvec.h \
 include/ir.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h include/kxthread.h \
 include/getopt.h
parser.o: src/parser.c include/kvec.h include/kinx.h include/ir.h \
 include/dbg.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
format.o: src/format.c include/kinx.h include/kvec.h include/ir.h \
 include/dbg.h include/khash.h include/klist.h include/kstr.h \
 include/bigz.h include/bign.h include/jit.h \
 include/../src/jit/sljitLir.h include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
string.o: src/string.c include/dbg.h include/khash.h include/ir.h \
 include/kvec.h include/klist.h include/kstr.h include/bigz.h \
 include/bign.h include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
optimizer.o: src/optimizer/optimizer.c include/kxoptimizer.h include/kinx.h \
 include/kvec.h include/ir.h include/dbg.h include/khash.h \
 include/klist.h include/kstr.h include/bigz.h include/bign.h \
 include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
opt_cfold.o: src/optimizer/opt_cfold.c include/kxoptimizer.h include/kinx.h \
 include/kvec.h include/ir.h include/dbg.h include/khash.h \
 include/klist.h include/kstr.h include/bigz.h include/bign.h \
 include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
opt_jumpx.o: src/optimizer/opt_jumpx.c include/kxoptimizer.h include/kinx.h \
 include/kvec.h include/ir.h include/dbg.h include/khash.h \
 include/klist.h include/kstr.h include/bigz.h include/bign.h \
 include/jit.h include/../src/jit/sljitLir.h \
 include/../src/jit/sljitConfig.h \
 include/../src/jit/sljitConfigInternal.h
 
