PROGRAM = salsa
OBJS = main.o

CC = gcc
CFLAGS = -Wall -O2

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
	makedepend -- $(CFLAGS) -- $(OBJS)
