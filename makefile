CFLAGS = -pedantic -Wall -std=c99 -D_XOPEN_SOURCE

all: libsocketTCP.a

libsocketTCP.a: socketTCP.o socketTCP_utils.o
	ar rcs $@ $^

socketTCP.o: socketTCP.c socketTCP.h socketTCP_utils.h

install:
	cp *.a /usr/lib/ && cp *.h /usr/include/

clean:
	$(RM) *.{a,o}
