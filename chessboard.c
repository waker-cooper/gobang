#include"chessboard.h"

coordinate cur_coor;
gobang gobang_board;
//int chessboard_tag [ROW][LEN];

void print_index(){
	for(int i=1;i<=LEN;i++){
		gotoxy(i,0);
		if (i%2) printf("%d",i);      
	}
	for(int i=1;i<=ROW;i++){
		gotoxy(0,i);
		if(i%2)	printf("%d",i);
	}
}
void draw_chessboard(){
	print_index();
}
void init_gobang_board(){
	gobang_board.list_size=0;
	memset(gobang_board.plist,0,PIECE_LIST_MAX_SIZE*sizeof(piece_list));
	for(int i =0 ;i<ROW;i++)
		for(int j=0;j<LEN;j++)
			gobang_board.chessboard_tag[i][j]=0;
}
static   struct  termios oldt;
void  restore_terminal_settings(void)
{
     // Apply saved settings
    tcsetattr( 0 , TCSANOW,  & oldt); 
}

void  disable_terminal_return( void )
{
     struct  termios newt;
    tcgetattr( 0 ,  & oldt); 
    newt  =  oldt;  
    newt.c_lflag  &=   ~ (ICANON  |  ECHO);
    tcsetattr( 0 , TCSANOW,  & newt);
    atexit(restore_terminal_settings);
}


int is_coor_illegal(coordinate c){
	if(X_MIN<=c.x&&c.x<=X_MAX&&
	   Y_MIN<=c.y&&c.y<=Y_MAX)
		return 0;
	else
		return 1;

}
void init_coor(){
	cur_coor.x=10,cur_coor.y=10;
	gotoxy(cur_coor.x,cur_coor.y);
}
void init(){
	disable_terminal_return();
	CLEAN;
	draw_chessboard();
	init_gobang_board();
	//clear_chessboard_tag();
	init_coor();
}
void finish(){

}
void process_direction(){
		input_key=fgetc(stdin);
		if(input_key=='['){
			input_key=fgetc(stdin);
			switch(input_key){
				case 'A': 
					if(cur_coor.y > Y_MIN){
						cur_coor.y--;
						UP;
					}
					break;

				case 'B':
					if(cur_coor.y < Y_MAX){
						cur_coor.y++;
						DOWN;
					}
					break;
				case 'D':
					if(cur_coor.x > X_MIN){
						cur_coor.x--;
						LEFT;
					}
					break;
				case 'C':
					if(cur_coor.x < X_MAX){
						cur_coor.x++;
						RIGHT;
					}
					break;
				default : 
					printf("error input \n");exit(1);
			}
		}
}
int get_chessboard_tag(int x,int y){
    coordinate c={x,y};
	if(!is_coor_illegal(c)){
		return gobang_board.chessboard_tag[y][x];
	}else
		return 0;
}
void set_chessboard_tag(int x,int y){
    coordinate c={x,y};
	if(!is_coor_illegal(c)){
		gobang_board.chessboard_tag[y][x]=cur_player;
		gobang_board.plist[gobang_board.list_size++].coor=c;
	}
}


