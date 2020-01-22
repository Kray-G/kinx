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
    bign.o \
    bigz.o \
    getopt.o \
    global.o \
    ir_dump.o \
    ir_exec.o \
    ir_fix.o \
    ir_util.o \
    kstr.o \
    lexer.o \
    loadlib.o \
    main.o \
    parser.o \
    string.o
SOFILES = \
    kxsystem.so \
    kxstring.so \
    kxarray.so \
    kxregex.so
PICOBJS1 = \
    bignpic.o \
    bigzpic.o
PICOBJS2 = \
    bignpic.o \
    bigzpic.o \
    allocutilpic.o
PICOBJS3 = \
    bignpic.o \
    bigzpic.o \
    allocutilpic.o \
    kstrpic.o
PICOBJALL = \
    $(PICOBJS3)
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
	rm -f $(OBJS) $(SOFILES) $(PICOBJALL) timex kinx myacc test

kinx: src/parser.c include/parser.tab.h libonig.so $(OBJS)
	./timex $(CC) -o $@ $(OBJS) -ldl -lm
	rm kx.output

kxsystem.so: src/extlib/kxsystem.c $(PICOBJS2)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS2)

kxstring.so: src/extlib/kxstring.c $(PICOBJS1)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS1)

kxarray.so: src/extlib/kxarray.c $(PICOBJS1)
	./timex $(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS1)

kxregex.so: src/extlib/kxregex.c $(PICOBJS3) libonig.so
	$(CC) $(CFLAGS) -fPIC -o $@ -shared $< $(PICOBJS3) -Wl,-rpath,'$$ORIGIN' -L. -lonig

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

kstrpic.o: src/kstr.c
	./timex $(CC) -fPIC -c $(CFLAGS) -o $@ $<

%.o: src/%.c
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

