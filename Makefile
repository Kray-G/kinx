# Hook for build directory.

all:
	(cd build; make)

clean:
	(cd build; make clean)

rebuild:
	(cd build; make clean all)
