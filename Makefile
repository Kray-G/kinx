.POSIX:
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib
SRCDIR = $(CURDIR)$(.CURDIR)

CC = gcc
CFLAGS = -DKX_DIRECT_THREAD -Iinclude -O2 \
	 -Wno-unused-result -Wno-missing-braces -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
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
    ir_exec.o \
    ir_fix.o \
    ir_util.o \
    ir_aotcore.o \
    ir_aotdump.o \
    ir_natutil.o \
    kstr.o \
    lexer.o \
    fileutil.o \
    loadlib.o \
    main.o \
    parser.o \
    string.o
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
    dis.o \
    disas.o \
    dss.o \
    lex.o \
    sym.o \
    aload.o \
    arm.o \
    astrings.o \
    mips.o \
    mload.o \
    mstrings.o \
    x86.o \
    x86asm.o \
    x86load.o \
    x86strings.o \
    file.o \
    table.o \
    trie.o
SOFILES = \
    kxsystem.so \
    kxstring.so \
    kxbinary.so \
    kxinteger.so \
    kxdouble.so \
    kxarray.so \
    kxfile.so \
    kxmath.so \
    kxregex.so
PICOBJS = \
    bignpic.o \
    bigzpic.o \
    allocutilpic.o \
    fileutilpic.o \
    kstrpic.o
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

all: timex kinx $(SOFILES)

timex:
	$(CC) $(CFLAGS) -o timex timex.c

clean:
	rm -f $(OBJS) $(DISASM) $(SOFILES) $(PICOBJS) timex kinx myacc test

kinx: src/parser.c include/parser.tab.h libonig.so $(OBJS) $(DISASM)
	./timex $(CC) -o $@ $(OBJS) $(DISASM) -ldl -lm
	rm kx.output
	cp -f src/disasm/arch/x86/x86.ins .
	cp -f src/disasm/arch/x86/x64.ins .
	cp -f src/disasm/arch/mips/mips.ins .
	cp -f src/disasm/arch/arm/arm.ins .
	cp -f src/disasm/spec/x86.spec .
	cp -f src/disasm/spec/mips.spec .

kxsystem.so: src/extlib/kxsystem.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxstring.so: src/extlib/kxstring.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxbinary.so: src/extlib/kxbinary.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxinteger.so: src/extlib/kxinteger.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxdouble.so: src/extlib/kxdouble.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxarray.so: src/extlib/kxarray.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxfile.so: src/extlib/kxfile.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS)

kxmath.so: src/extlib/kxmath.c $(PICOBJS)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -lm

kxregex.so: src/extlib/kxregex.c $(PICOBJS) libonig.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS) -Wl,-rpath,'$$ORIGIN' -L. -lonig

src/parser.c: kx.tab.c
	mv -f kx.tab.c src/parser.c; 

include/parser.tab.h: kx.tab.h
	mv -f kx.tab.h include/parser.tab.h;

kx.tab.c: myacc
	./myacc -vd -b kx -y kx_yy -Y KINX_YY src/kinx.y;

kx.tab.h: myacc
	./myacc -vd -b kx -y kx_yy -Y KINX_YY src/kinx.y;

myacc:
	cd utility; \
	$(CC) $(CFLAGS) -Wno-format-security -o myacc myacc.c; \
	mv -f myacc ../;

libonig.so:
	cd src/extlib/onig; \
	autoreconf -vfi; \
	./configure --with-pic; \
	make; \
	cp -f src/.libs/libonig.so.5.0.0 ../../../;
	ln -s libonig.so.5.0.0 libonig.so.5; \
	ln -s libonig.so.5 libonig.so;

bignpic.o: src/bign.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

bigzpic.o: src/bigz.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

allocutilpic.o: src/allocutil.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

fileutilpic.o: src/fileutil.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

kstrpic.o: src/kstr.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/%.c
	./timex $(CC) -c $(CFLAGS) -o $@ $<

%.o: src/disasm/%.c
	./timex $(CC) -c $(CFLAGS) -o $@ $<

%.o: src/disasm/common/%.c
	./timex $(CC) -c $(CFLAGS) -o $@ $<

%.o: src/disasm/arch/x86/%.c
	./timex $(CC) -c $(CFLAGS) -o $@ $<

%.o: src/disasm/arch/arm/%.c
	./timex $(CC) -c $(CFLAGS) -o $@ $<

%.o: src/disasm/arch/mips/%.c
	./timex $(CC) -c $(CFLAGS) -o $@ $<

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

