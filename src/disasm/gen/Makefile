CC = gcc
EXE = gen
SOURCES = $(wildcard *.c)
OBJS = $(SOURCES:.c=.o)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	CXXFLAGS = -ggdb3 -std=c99 -Wall -Wextra -pedantic
	CFLAGS = $(CXXFLAGS)
endif

.c.o:
	$(CC) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CXXFLAGS) $(LIBS)

run: gen
	./gen *.sym

clean:
	rm $(EXE) $(OBJS)
