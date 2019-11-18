CC=gcc
CFLAGS=-Wextra -Wall -pedantic
OBJS=trip.o main.o search.o

trip: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lssl -lcrypto
