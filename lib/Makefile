CC:=gcc
CFLAGS:=-std=c99 -Wall
LDFLAGS:=-fPIC -shared

PREFIX:=/usr
LIB:=libMyLogger.so
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
DEP:=myLogger.h

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) -fpic -shared $(SRC) -o $(LIB) -lsqlite3

install:
	install -d $(PREFIX)/lib $(PREFIX)/include
	install -m 0555 $(LIB) $(PREFIX)/lib
	install -m 0555 $(DEP) $(PREFIX)/include

uninstall:
	$(RM) $(PREFIX)/lib/$(LIB)
	$(RM) $(PREFIX)/include/$(DEP)

clean:
	$(RM) $(OBJS) $(LIB)