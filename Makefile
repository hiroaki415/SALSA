PROGRAM = salsa

OBJS = main.o

CC = gcc
CFLAGS = -Wall -O2

BINPATH = /usr/local/bin

.SUFFIXES: .c .o

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS)

.PHONY: depend
depend:
	makedepend -- $(CFLAGS) -- $(OBJS)

.PHONY: install
install:
	mv $(PROGRAM) $(BINPATH)
