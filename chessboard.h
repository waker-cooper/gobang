#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include"declare.h"

extern char input_key;
extern int cur_player;

int get_chessboard_tag();
void set_chessboard_tag();
void init();
void finish();
void process_direction();

#endif
