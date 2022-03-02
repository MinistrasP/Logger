CC:=gcc
CFLAGS:=-std=c99 -Wall
LDFLAGS:=-fPIC -shared

BIN:=mainas
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)

all:clean $(BIN)
$(BIN): main.c
	$(CC) -o $@ $^ -L`pwd` -lLogeris

install:
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 0555 $(LIB) $(PREFIX)/lib
	install -m 0555 bible_testine.h $(PREFIX)/include

uninstall:
	$(RM) $(PREFIX)/lib/$(LIB)
	$(RM) $(PREFIX)/include/bible_testine.h

clean:
	$(RM) $(BIN) $(OBJS) $(LIB)