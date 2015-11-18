.PHONY: all clean

CFILES=$(wildcard *.c)
OFILES=$(patsubst %.c,%.o,$(CFILES))

CFLAGS=-std=gnu11 -g -O1 -Wall -Wextra
LDFLAGS=-std=gnu11 -g -O1 -lcurses

all: fw

fw: ${OFILES}
	gcc ${LDFLAGS} -o $@ ${OFILES}
