#ifndef DECLEAR_H
#define DECLEAR_H
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<termios.h>
#include<time.h>
#define gotoxy(x,y) printf("\033[%d;%dH\b", (1+BOARD_OFFSET_Y+(y)), (2+2*((x)+BOARD_OFFSET_X)))
#define UP printf("\033[1A");
#define DOWN printf("\033[1B");
#define LEFT printf("\033[2D");
#define RIGHT printf("\033[2C");
#define CLEAN printf("\033[2J\b");
#define ROW (20+1)
#define LEN (20+1)
#define Y_MAX ROW-1
#define Y_MIN 1
#define X_MAX LEN-1
#define X_MIN 1
#define DIRECTION_KEY '\033'
#define BOARD_OFFSET_X 1
#define BOARD_OFFSET_Y 0
#define CHECKED 1
#define PIECE_LIST_MAX_SIZE 500
typedef struct Coordinate{
	int x;
	int y;
} coordinate;
typedef struct Piece_list{
	coordinate coor;
	int state;
}piece_list;
typedef struct Gobang{
	int chessboard_tag[ROW][LEN];
	int list_size;
	piece_list plist[PIECE_LIST_MAX_SIZE];
}gobang;
#endif
