CC:=gcc
CFLAGS:=-std=c99 -Wall
LDFLAGS:=-fPIC -shared

PREFIX:=/usr
LIB:=libLogeris.so
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)

all:clean $(LIB)

libLogeris: $(LIB)

$(LIB): logeris.o
	cc -fpic -shared $(SRC) -o $(LIB) -lsqlite3

install:
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 0555 $(LIB) $(PREFIX)/lib
	install -m 0555 logeris.h $(PREFIX)/include

uninstall:
	$(RM) $(PREFIX)/lib/$(LIB)
	$(RM) $(PREFIX)/include/bible_testine.h

clean:
	$(RM) $(BIN) $(OBJS) $(LIB)