CC = gcc
CFLAGS = -g -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lglib-2.0 
markov : markov.o
	$(CC) $^ -o $@ $(CFLAGS)

markov.o : markov.c
	$(CC) $^ -c $(CFLAGS)