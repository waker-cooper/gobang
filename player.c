#include"player.h"
char input_key;
int quit;
int cur_player=0; 

static void cal_weight(int a,int d,coordinate *final_coor);
void drop(){
	while(1){
		input_key=fgetc(stdin);
		if(input_key==DIRECTION_KEY){
			process_direction();
		}else if(P1_FINAL_KEY == input_key && PLAYER1 == cur_player){
			if(get_chessboard_tag(cur_coor.x,cur_coor.y) == 0){
				set_chessboard_tag(cur_coor.x,cur_coor.y);
				printf("x\b");
				break;
			}
		}else if(P2_FINAL_KEY == input_key && PLAYER2 == cur_player){
			if(get_chessboard_tag(cur_coor.x,cur_coor.y) == 0){
				set_chessboard_tag(cur_coor.x,cur_coor.y);
				printf("o\b");
				break;
			}
			
		}else if(input_key == QUIT_KEY ){
			quit=1;
			break;
		}
	}
}
coordinate random_play(){
	coordinate ai_coor;
	//do{
	ai_coor.x=1+rand()%20,ai_coor.y=1+rand()%20;
	//}while(get_chessboard_tag(ai_coor.x,ai_coor.y)!=0);
	//set_chessboard_tag(ai_coor.x,ai_coor.y);

	return ai_coor;

}


typedef struct Restriant{
	int p;
	int p_n;
}Restriant;
typedef struct  Strategy{
	int id;
	int state;
	int weight;
	coordinate c;
	int restriant_num;
	Restriant* rlist;
	int clisti;
	coordinate *clist;
	//int nature_empty;
} Strategy;
//typedef struct fesible_coor{
//	int num;
//	coordinate c1;
//	coordinate c2;
//}feasible_coor;


//------------------------------
static Strategy ai_strategy;
//static feasible_coor fc;

struct HCW{
	int hit;
	coordinate coor;
	int weight;
};
typedef struct HCW hcw;
int test_final_coor(coordinate c){


}
coordinate h_get_final_coor(coordinate s,coordinate e){
	coordinate c1={s.x-1,s.y},c2={e.x+1,e.y},c_not_find={-1,-1};
	if(!is_coor_illegal(c1)&&get_chessboard_tag(c1.x,c1.y)==0){
		return c1;
	}else if(!is_coor_illegal(c2)&&get_chessboard_tag(c2.x,c2.y)==0){
		return c2;
	}

}
void write_final_coor(coordinate c){
	if(ai_strategy.state == 0){
		ai_strategy.c=c;//
		ai_strategy.state=1;//write protect
	}

}
#define SRCH_LEFT 0
#define SRCH_RIGHT 1
struct Feasible_coor{
	int i;
	coordinate ac[100];
}feasible_set;


void clear_feasible_coor(){
	memset(feasible_set.ac,0,sizeof(coordinate)*100);
	feasible_set.i=0;
}
int chk_empty(coordinate *c){
	printf("chk empty\n");
	for(int i=0;i<ai_strategy.clisti;i++){
		printf("(%d,%d)\n",ai_strategy.clist[i].x,ai_strategy.clist[i].y);
		if(get_chessboard_tag(ai_strategy.clist[i].x,ai_strategy.clist[i].y) == 0){
			c->x=ai_strategy.clist[i].x;
			c->y=ai_strategy.clist[i].y;
			return 1;
		}
	}
	return 0;
}
void print_feasible_coor();
void find_feasible_coor(coordinate s,coordinate e){
//	clear_feasible_coor();
	//if there is empty space in restriant , so we push the coor in feasible coor set
	coordinate c;
	if(chk_empty(&c)){
		feasible_set.ac[feasible_set.i++]=c;
		return;
	}
	//else find board empty space
	if(get_chessboard_tag(s.x-1,s.y) == 0){
		c.x=s.x-1,c.y=s.y;
		//c={s.x-1,s.y};
		feasible_set.ac[feasible_set.i++]=c;
//		push_feasible_coor(x,y);
	}
	if(get_chessboard_tag(e.x+1,e.y)==0){
		coordinate c={e.x-1,e.y};
		c.x=e.x+1,c.y=e.y;
		feasible_set.ac[feasible_set.i++]=c;
	}
	//print_feasible_coor();
}
void clear_record(){
	ai_strategy.clisti=0;
	memset(ai_strategy.clist,0,sizeof(coordinate)*10);

}

int seacher(coordinate c,Restriant r,coordinate* s,coordinate* e,int direction){
		int check_range=r.p_n-1;
		coordinate j;
//		for(int m=0;m<=check_range;m++){

//          exit(-1);
			// ---> SRCH_RIGHT
			if(direction == SRCH_RIGHT){
				s->x=c.x , s->y=c.y;
				e->x=s->x+check_range , e->y=s->y;
			}else if (direction == SRCH_LEFT){
				s->x=c.x-check_range , s->y=c.y;
				e->x=c.x , e->y=s->y;
			}


				if(is_coor_illegal(*s)||is_coor_illegal(*e))
					return 0;
				for(j=*s;j.x<=e->x;j.x++){
				//printf("(%d,%d,tag %d)\n",j.x,j.y,get_chessboard_tag(j.x,j.y));
				if(get_chessboard_tag(j.x,j.y)!=r.p){
					clear_record();
					break;
				}
				}

				if(j.x>e->x){
					for(j=*s;j.x<=e->x;j.x++){
						ai_strategy.clist[ai_strategy.clisti++]=j;
					}
				#ifdef _DEBUG
//			printf("check range : %d\n",check_range);
//			printf("s(%d,%d,tag %d)\n",s->x,s->y,get_chessboard_tag(s->x,s->y));
//			printf("e(%d,%d,tag %d)\n",e->x,e->y,get_chessboard_tag(e->x,e->y));
//					printf("wtf  j.x %d e->x %d\n",j.x,e->x);
				#endif
					return 1;
				}


//		}
		return 0;
}
// rlist implem
int set_intersection(Restriant r,int i,coordinate c,int direction){
		coordinate s,e,s2;
		if(get_chessboard_tag(c.x,c.y)!=r.p ||
		             seacher(c,r,&s,&e,direction)==0)
			return 0;


if( i+1 == ai_strategy.restriant_num){
// then find enable coor
	find_feasible_coor(s,e);
	//return fs.num;
#ifdef _DEBUG
	printf("success strategy id : %d\n",ai_strategy.id);
	//printf("final (%d,%d,tag %d)\n",c.x,c.y,get_chessboard_tag(c.x,c.y));
	sleep(1);
#endif
	return 1;
}
	//write_final_coor(c);
	//return 1;


	//	if(direction == SRCH_LEFT){ 
	//		s2.x=s.x-1;s2.y=s.y;
	//	}else if(direction == SRCH_RIGHT){
			s2.x=e.x+1;s2.y=e.y;
	//	}
		
//		printf("pass (%d,%d,tag %d)\n",s2.x,s2.y,get_chessboard_tag(s2.x,s2.y));
//			sleep(1);
	
		if(set_intersection(ai_strategy.rlist[i+1],i+1,s2,direction)){
			//set_intersection(ai_strategy.rlist[i+1],i+1,e2)){
			return 1;//res chain
		}else
			return 0;

}
//int set_intersection(Restriant r,int i,coordinate c,int direction){
//		coordinate s,e,s2;
//		if(get_chessboard_tag(c.x,c.y)!=r.p ||
//		             seacher(c,r,&s,&e,direction)==0)
//			return 0;
//
//
//if( i+1 == ai_strategy.restriant_num){
//// then find enable coor
//	find_feasible_coor();
//	//return fs.num;
//	return 1;
//#ifdef _DEBUG
//	printf("success strategy id : %d\n",ai_strategy.id);
//	printf("final (%d,%d,tag %d)\n",c.x,c.y,get_chessboard_tag(c.x,c.y));
//	sleep(1);
//#endif
//}
//	//write_final_coor(c);
//	//return 1;
//
//
//		if(direction == SRCH_LEFT){ 
//			s2.x=s.x-1;s2.y=s.y;
//		}else if(direction == SRCH_RIGHT){
//			s2.x=e.x+1;s2.y=e.y;
//		}
//		
////		printf("pass (%d,%d,tag %d)\n",s2.x,s2.y,get_chessboard_tag(s2.x,s2.y));
////			sleep(1);
//	
//		if(set_intersection(ai_strategy.rlist[i+1],i+1,s2,direction)){
//			//set_intersection(ai_strategy.rlist[i+1],i+1,e2)){
//			return 1;//res chain
//		}else
//			return 0;
//
//}
void octopus_find(){
	coordinate c;
	
	// global search
	for(int x=X_MIN;x<=X_MAX;x++){
			for(int y=Y_MIN;y<=Y_MAX;y++){
				c.x=x,c.y=y;	
			//	printf("check coor (%d,%d)\n",c.x,c.y);
				if(set_intersection(ai_strategy.rlist[0],0,c,SRCH_RIGHT)==1){
					
					break;
					//return ai_strategy.weight;
				}
				//if(set_intersection(ai_strategy.rlist[0],0,c,SRCH_LEFT)==1){
				//	//find return the restriant weight
				//	break;
				//	//return ai_strategy.weight;
				//}				
			}
	}
// zero means not find
//	return 0;
//	int k=0;
//	for(k=0;k<gb.list_size;k++){
//		c=gb.plist[k].coor;
//		if(set_intersection(ai_strategy.rlist[0],0,c)==1) break;
//	}
//	if(k==gb.list_size){ 
//		printf("strategy is  %d defeat\n",ai_strategy.id);
//		printf("ai_strategy.c : (%d,%d)\n",ai_strategy.c.x,ai_strategy.c.y);
//		usleep(100000);
//	}

}
void init_strategy(Strategy s){
		ai_strategy=s;
}

int __a4(int a,int d){
	Restriant rlist[2]={{a,4},{0,1}};
	Strategy s={0,0,100,{0,0},2,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}

int __a_a3(int a,int d){
	Restriant rlist[4]={{a,1},{0,1},{a,3},{0,1}};
	Strategy s={1,0,95,{0,0},4,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __a2_s_a2(int a,int d){
	Restriant rlist[3]={{a,2},{0,1},{a,2}};
	Strategy s={2,0,95,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}


int __ad4(int a,int d){
	Restriant rlist[3]={{a,1},{d,4},{0,1}};
	Strategy s={3,0,95,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;

}
int __d2_s_d2(int a,int d){
	Restriant rlist[3]={{d,2},{0,1},{d,2}};
	Strategy s={4,0,95,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __d_d3(int a,int d){
	Restriant rlist[4]={{d,1},{0,1},{d,3},{0,1}};
	Strategy s={5,0,95,{0,0},4,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}

int __d3(int a,int d){
	Restriant rlist[3]={{0,1},{d,3},{0,1}};
	Strategy s={6,0,90,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
//A3-----------------------------------------------

void __a3(int a,int d){
	Restriant rlist[1]={{a,3}};
	coordinate clist[10];
	memset(clist,0,sizeof(coordinate)*10);
	Strategy s={7,0,85,{0,0},1,rlist,0,clist};
	init_strategy(s);
	octopus_find();

}
void __a2_a(int a,int d){
	coordinate clist[10];
	memset(clist,0,sizeof(coordinate)*10);
	Restriant rlist[3]={{a,2},{0,1},{a,1}};
	Strategy s2={8,0,85,{0,0},3,rlist,0,clist};
	init_strategy(s2);
	octopus_find();
}
void __a_a2(int a,int d){
	coordinate clist[10];
	memset(clist,0,sizeof(coordinate)*10);
	Restriant rlist[3]={{a,1},{0,1},{a,2}};
	Strategy s2={9,0,85,{0,0},3,rlist,0,clist};
	init_strategy(s2);
	octopus_find();
}
//void construct_strategy(int id,int state,int weight,)
int three(int a,int d){
	//Strategy s;
	__a3(a,d);
	__a2_a(a,d);
	__a_a2(a,d);
	if(feasible_set.i==0) return 0;

	coordinate final_coor;
	cal_weight(a,d,&final_coor);
	ai_strategy.c=final_coor;
	ai_strategy.state=1;
	return 1;
	//find many  feasible coors 
	//return ai_strategy.state;
	//return 0;

}
//------------------------------------------------------
void fake_set_tag(coordinate c,int player,gobang* gb){
	if(!is_coor_illegal(c)){
		gb->chessboard_tag[c.y][c.x]=player;
	}
}
struct Expression
{
	int weight;
	int rlist_num;
	Restriant*rlist;
	/* data */
};
int find_expression(struct Expression e){

	
	return 0;

}
void simulate(int a,int d,coordinate c,gobang gb,int* sum){
	Restriant rlist[3]={{0,1},{a,4},{0,1}};
	struct Expression e1={1000,3,rlist};
	if(find_expression(e1)){
		*sum+=e1.weight;
		return ;
	}
	Restriant rlist2[3]={{d,1},{a,4},{0,1}};
	struct Expression e2={20,3,rlist2};
	if(find_expression(e2)){
		*sum+=e2.weight;
	}


}

void cal_weight(int a,int d,coordinate *final_coor){
	int sum_max=0;
	coordinate best_coor;
	for(int i=0;i<feasible_set.i;i++){
		int sum=0;
		gobang gb=gobang_board;
		fake_set_tag(feasible_set.ac[i],a,&gb);
		simulate(a,d,feasible_set.ac[i],gb,&sum);
		if(sum>sum_max){
			sum_max=sum;
			best_coor=feasible_set.ac[i];
		}
	}
	final_coor->x=best_coor.x;
	final_coor->y=best_coor.y;

}
int __a3d1(int a,int d){
	Restriant rlist[3]={{a,3},{d,1},{0,1}};
	Strategy s={8,0,80,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __a2(int a,int d){
	Restriant rlist[2]={{a,2},{0,1}};
	Strategy s={9,0,75,{0,0},2,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __a2d(int a,int d){
	Restriant rlist[3]={{a,2},{d,1},{0,1}};
	Strategy s={10,0,70,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __a(int a,int d){
	Restriant rlist[2]={{a,1},{0,1}};
	Strategy s={11,0,65,{0,0},2,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __ad(int a,int d){
	Restriant rlist[3]={{a,1},{d,1},{0,1}};
	Strategy s={12,0,60,{0,0},3,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __d(int a,int d){
	Restriant rlist[2]={{d,1},{0,1}};
	Strategy s={13,0,55,{0,0},2,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}
int __n(int a,int d){
	Restriant rlist[1]={{0,1}};
	Strategy s={14,0,50,{10,10},1,rlist};
	init_strategy(s);
	octopus_find();
	return ai_strategy.state;
}



void print_feasible_coor(){
	printf("feasible coor \n");
	for(int i=0;i<feasible_set.i;i++){
		printf("(%d,%d)\n",feasible_set.ac[i].x,feasible_set.ac[i].y);
	}

}

void  through_decision_table(int a,int d){
//greed algorithm

//	int sum_weight=0;
//	if(__a4(a,d)){		
//		return ;
//	//printf("%d\n",ai_strategy.state);	
//	}
//	if(__a2_s_a2(a,d)){
//		return ;
//	}
//	if(__a_a3(a,d)){
//		return ;
//	}
//	if(__d_d3(a,d)){
//		return ;
//	}
//	if(__d2_s_d2(a,d)){
//		return ;
//	}
////	printf("excute ad4\n");
//  if(__ad4(a,d)){	
//  	return ;
//  }
//
	if(three(a,d)){
		return ;
	}
	print_feasible_coor();
	//printf("miss\n");
//	if(__d3(a,d)){
//		return ;
//	}
//	if(__a3d1(a,d)){
//		return ;
//	}
//	if(__a2(a,d)){
//		return ;
//	}
//	if(__a2d(a,d)){
//		return ;
//	}
//	if(__a(a,d)){
//		return ;
//	}
//	if(__ad(a,d)){
//		return ;
//	}
//	if(__d(a,d)){
//		return ;
//	}
//	if(__n(a,d)){
//		return ;
//	}
//		//
		//if
	//	else{ 
			//
			//if
	//	}
	
}
coordinate rookie(){
	int attacker=cur_player;
	int defender= attacker == PLAYER1 ? PLAYER2:PLAYER1;
	through_decision_table(attacker,defender);
	coordinate ai_coor=ai_strategy.c;
	return ai_coor;
}
coordinate calculate_coor(){
	coordinate ai_coor;
	//srand((unsigned int)time(0));
	do{
		ai_coor=rookie();
		//ai_coor=random_play();
		//printf("x:%d y:%d\n",ai_coor.x,ai_coor.y);
		//printf("tag %d\n",get_chessboard_tag(ai_coor.x,ai_coor.y));
	}while(get_chessboard_tag(ai_coor.x,ai_coor.y)!=0);
	set_chessboard_tag(ai_coor.x,ai_coor.y);
	return ai_coor;
}
void ai_drop(){
	coordinate ai_coor=calculate_coor();
	cur_coor=ai_coor;
	gotoxy(ai_coor.x,ai_coor.y);
	cur_player == PLAYER1 ? printf("x\b"):printf("o\b");

}

void set_cur_player(int player){
	cur_player=player; 
}
