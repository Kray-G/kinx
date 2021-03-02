
all:
	mkdir -p build
	cd build; cmake ..; make clean; make
	cp build/lib/libclipboard.a ../../../build/libclipboard.a
	cp build/include/*.h include/
	gcc -o kxsel -DVERSION="\"1.2.0\"" xsel.c -lX11
	cp ./kxsel ../../../build/
