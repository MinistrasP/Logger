CC:=gcc

BIN:=myLogger
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)
LDFLAGS:=-I../lib/ -L../lib/ -lmyLogger
PREFIX:=/usr

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(SRC)
	$(CC) -o $@ $^ $(LDFLAGS)

install:
	install -d $(PREFIX)/bin
	install -m 0555 $(BIN) $(PREFIX)/bin

uninstall:
	$(RM) $(PREFIX)/bin/$(BIN)

clean:
	$(RM) $(BIN) $(OBJS)