#include"referee.h"
int winner;
coordinate winner_coor[5];

void print_winner(){
	for(int i=0;i<5;i++){
		gotoxy(winner_coor[i].x,winner_coor[i].y);
		cur_player == 1 ? printf("\033[31;5mx\b") : printf("\033[31;5mo\b");
	}
	gotoxy(1,22);
    printf("\33[0m%d is winner\n",cur_player);
}
void vertical_test(){
	int check_range=4;
	coordinate s,e,j;
	for (int i=0;i<=check_range;i++){
		s.x=cur_coor.x , s.y=cur_coor.y-i;
		e.x=s.x , e.y=s.y+check_range;
		if(is_coor_illegal(s)||is_coor_illegal(e)) continue;
		int k=0;
		for(j=s;j.y<=e.y;j.y++){
			if(get_chessboard_tag(j.x,j.y)!=cur_player){
				break;
			}else{
				winner_coor[k].x=j.x;
				winner_coor[k++].y=j.y;
			}
		}
		if(j.y>e.y){
			print_winner();
            winner = cur_player;
			break;
		}
	}
}
void horizontal_test(){
	int check_range=4;
	coordinate s,e,j;
	for (int i=0;i<=check_range;i++){
		s.x=cur_coor.x-i , s.y=cur_coor.y;
		e.x=s.x+check_range , e.y=s.y;
		if(is_coor_illegal(s)||is_coor_illegal(e)) continue;
		int k=0;
		for(j=s;j.x<=e.x;j.x++){
			if(get_chessboard_tag(j.x,j.y)!=cur_player){
				break;
			}else{
				winner_coor[k].x=j.x;
				winner_coor[k++].y=j.y;
			}
		}
		if(j.x>e.x){
			print_winner();
            winner = cur_player;
			break;
		}
	}
}
void lo_test(){
	int check_range=4;
	coordinate s,e,j;
	for (int i=0;i<=check_range;i++){
		s.x=cur_coor.x-i , s.y=cur_coor.y-i;
		e.x=s.x+check_range , e.y=s.y+check_range;
		if(is_coor_illegal(s)||is_coor_illegal(e)) continue;
		int k=0;
		for(j=s;j.x<=e.x;){
			if(get_chessboard_tag(j.x,j.y)!=cur_player){
				break;
			}else{
				
				winner_coor[k].x=j.x;
				winner_coor[k++].y=j.y;
			}
			j.x++;
			j.y++;
		}
		if(j.x>e.x){
			print_winner();
            winner = cur_player;
			break;
		}
	}
}
void ro_test(){
	int check_range=4;
	coordinate s,e,j;
	for (int i=0;i<=check_range;i++){
		s.x=cur_coor.x-i , s.y=cur_coor.y+i;
		e.x=s.x+check_range , e.y=s.y-check_range;
		if(is_coor_illegal(s)||is_coor_illegal(e)) continue;
		int k=0;
		for(j=s;j.x<=e.x;){
			if(get_chessboard_tag(j.x,j.y)!=cur_player){
				break;
			}else{
			
				winner_coor[k].x=j.x;
				winner_coor[k++].y=j.y;
			}
			j.x++;
			j.y--;
		}
		if(j.x>e.x){
			print_winner();
            winner = cur_player;
			break;
		}
	}

}

void win_test(){
	    
	enum test_direction {horizontal,vertical,left_oblique,right_oblique};
	enum test_direction td;
	for (td=horizontal;td<=right_oblique;td++){
		switch(td){
			case horizontal:horizontal_test();break;
			case vertical: vertical_test();break;
			case left_oblique:lo_test();break;
			case right_oblique:ro_test();break;
			default:printf("wtf\n");exit(2);
		}
		if(winner!=0) break;
	}
}
int over_test(){
	int over=0;
	if(winner){
		over=1;
	}else if(quit){
		over=1;
	}
	return over;
}


