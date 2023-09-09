CC=gcc
DEBUG=-D_DEBUG
CFLAGS= -O0 $(DEBUG) -std=c99
main.o : main.c 
	$(CC) $(CFLAGS)  main.c -c
chessboard.o : chessboard.c
	$(CC) $(CFLAGS) chessboard.c   -c
player.o : player.c
	$(CC) $(CFLAGS) player.c -c
referee.o : referee.c
	$(CC) $(CFLAGS) referee.c -c
clean:
	rm  -f *.o 
	rm  -f gobang
gobang : main.o chessboard.o player.o referee.o
		$(CC) $(CFLAGS) $^ -o $@
all:gobang
