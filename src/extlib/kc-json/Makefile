.POSIX:
.SUFFIXES:

NAME = kc-json
CC = gcc
CFLAGS = -O2 -Wno-missing-braces -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -std=gnu99

all: dist/$(NAME).c dist/sample.exe

dist/$(NAME).c: dist/myacc
	./dist/myacc -y __json_yy -Y JSON_YY src/$(NAME).y
	cp -f y.tab.c dist/$(NAME).c
	cat src/string.c >> dist/$(NAME).c
	cat src/vector.c >> dist/$(NAME).c
	rm -f y.tab.c
	cp -f src/$(NAME).h dist/$(NAME).h

dist/myacc:
	mkdir -p dist
	$(CC) $(CFLAGS) -o dist/myacc util/myacc.c

dist/sample.exe:
	cp -f sample/* dist/
	cd dist; \
	$(CC) $(CFLAGS) -o sample sample.c kc-json.c -lm; \
	cd ..

sample: dist/sample
	cp -f sample/* dist/
	cd dist; \
	./sample sample.json; \
	./sample sample_ext1.json; \
	cd ..

clean:
	rm -rf dist > /dev/null

