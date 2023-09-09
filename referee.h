#ifndef REFEREE_H
#define REFEREE_H
#include"declare.h"
extern int cur_player;
extern int quit;
extern coordinate cur_coor;

int is_coor_illegal(coordinate c);
void win_test();
int over_test();

//extern function -----
extern int get_chessboard_tag();
#endif
