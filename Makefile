CC=gcc
CFLAGS=-Wall -pedantic
OBJS=utils.o quicksort.o analyzation.o maman_13.o
BIN=maman_13

release: CFLAGS+=-O3 -DNDEBUG
release: maman_13

debug: CFLAGS+=-g
debug: maman_13

maman_13: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

clean:
	rm -r $(BIN) *.o
