
all:
	mkdir -p build
	cd build; cmake ..; make clean; make
	cp build/lib/libclipboard.a ../../../build/libclipboard.a
	cp build/include/*.h include/
