# Hook for build directory.

all:
	(cd build; make)
	cp -f build/kinx ./
	cp -f build/kxrepl ./
	cp -f build/kxtest ./
	cp -f build/*.so* ./

clean:
	(cd build; make clean)
	rm -f kinx
	rm -f kxrepl
	rm -f kxtest
	rm -f *.so*

rebuild:
	(cd build; make clean all)
	cp -f build/kinx ./
	cp -f build/kxrepl ./
	cp -f build/kxtest ./
	cp -f build/*.so* ./
