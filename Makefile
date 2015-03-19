PROGRAM = salsa

SRC = main.c $(wildcard src/*.c) lib/parson/parson.c
OBJS = $(patsubst %.c, %.o, $(SRC) )

CC = gcc
CFLAGS = -Wall -O0 -g
LINK = -lwiringPi

BINPATH = /usr/local/bin

.SUFFIXES: .c .o

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(depend)
	$(CC) $(LINK) -o $(PROGRAM) $^

.c.o:
	$(CC) $(CFLAGS) $(LINK) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS) *.o

.PHONY: depend
depend:
	makedepend -- $(CFLAGS) -- $(OBJS)

.PHONY: install
install:
	mv $(PROGRAM) $(BINPATH)
# DO NOT DELETE
