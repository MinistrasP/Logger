.PHONY: all clean src lib install uninstall

all: lib src

lib:
	$(MAKE) -C ./lib

src:
	$(MAKE) -C ./src

install:
	$(MAKE) -C ./src install
	$(MAKE) -C ./lib install

uninstall:
	$(MAKE) -C ./src uninstall
	$(MAKE) -C ./lib uninstall

clean:
	$(MAKE) -C ./src clean
	$(MAKE) -C ./lib clean
