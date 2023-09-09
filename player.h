#ifndef PLAYER_H
#define PLAYER_H
#include "declare.h"
#define DIRECTION_KEY '\033'
#define PLAYER1 1
#define P1_FINAL_KEY '1'
#define PLAYER2 2
#define P2_FINAL_KEY '2'
#define QUIT_KEY 'q'
extern coordinate cur_coor;
extern int cur_player;
//extern int chessboard_tag[20][20];
extern gobang gobang_board;
void drop();
void set_cur_player(int player);
void ai_drop();
//extern function
extern int get_chessboard_tag();
extern void set_chessboard_tag();
extern void process_direction();
extern int is_coor_illegal(coordinate c);
#endif
