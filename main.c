#include<unistd.h>
#include"chessboard.h"
#include"referee.h"
#include"player.h"
extern char input_key;
int ctler(int player){
	set_cur_player(player);
	drop();
	win_test();
	return !over_test(); 
}
int ctler2(int player){
	set_cur_player(player);
	ai_drop();
	win_test();
	//usleep(1000000);
	return !over_test(); 
}
int ctler3(int player){
	set_cur_player(player);
	usleep(10000);
	char shift_key=fgetc(stdin);
	if(shift_key == 's'){
		ai_drop();
	}else{
		drop();
	}
	win_test();
	return !over_test(); 
}
int main(){
	init();
	//while(ctler(PLAYER1)&&ctler(PLAYER2));
	//while(ctler(PLAYER1)&&ctler2(PLAYER2));
	while(ctler(PLAYER1)&&ctler3(PLAYER2));
	finish();
	return 0;	
}
