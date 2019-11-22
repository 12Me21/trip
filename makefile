CC=gcc
CFLAGS=-Wextra -Wall -pedantic -O3
OBJS=trip.o main.o search.o

trip: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lssl -lcrypto
