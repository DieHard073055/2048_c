#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

/*#define DEBUG   Uncomment this for debugging*/
/*
	VARIABLE DEFINITIONS
*/
#define DATA_FILE 	"2048.data"

#define SIZE 		4
#define UP		5	
#define DOWN		6
#define RIGHT		7
#define LEFT		8
#define WRONG		9
#define CHANGED 	10
#define NOT_CHANGED 	11
#define LOAD		12
#define QUIT		13

#define WIN		2048

typedef struct{
	int g; /*The number shown in the game*/
	int m;/*Hidden number*/
	int p;/*Previous Number*/
}GAME;

typedef struct{
	GAME b[SIZE][SIZE];
	int score;
	char player[100];
}GAME_PACKAGE;

GAME_PACKAGE * setup();
void init(GAME_PACKAGE * gp);
void magic_number(GAME_PACKAGE * gp);
void re_init(GAME_PACKAGE * gp);
void print_array(GAME_PACKAGE * gp);
int get_user_input();

void merge(GAME_PACKAGE * gp, int input);
void merge_up(GAME_PACKAGE * gp);
void merge_down(GAME_PACKAGE * gp);
void merge_left(GAME_PACKAGE * gp);
void merge_right(GAME_PACKAGE * gp);

void shift(GAME_PACKAGE * gp, int input);
void shift_up(GAME_PACKAGE * gp);
void shift_down(GAME_PACKAGE * gp);
void shift_left(GAME_PACKAGE * gp);
void shift_right(GAME_PACKAGE * gp);

void insert_magic_number(GAME_PACKAGE * gp);

void welcome(GAME_PACKAGE * gp);
bool check_game_state(GAME_PACKAGE * gp);
void won(GAME_PACKAGE * gp);
void lost(GAME_PACKAGE * gp);

void save_current_state(GAME_PACKAGE * gp);
void load_previous_state(GAME_PACKAGE * gp);

void save_player_data(GAME_PACKAGE * gp);
void read_player_data();

int main(){
	GAME_PACKAGE p;
	GAME_PACKAGE * gp = &p;
	bool GAME_STATE_RUNNING = true;
	int input=0, i;
	
	
	/*gp = setup();*/
	init(gp);
	welcome(gp);
	while(GAME_STATE_RUNNING){
	
		input = 0;
		re_init(gp);
		print_array(gp);
		input = get_user_input(gp);
		
		if(
		input == UP ||
		input == DOWN ||
		input == LEFT ||
		input == RIGHT||
		input == LOAD
		){
			if(input == LOAD) {load_previous_state(gp);}
			else{
				merge(gp, input);
				shift(gp, input);	
				insert_magic_number(gp);
				GAME_STATE_RUNNING = check_game_state(gp);
				save_current_state(gp);
			}
			
		}else if(input == QUIT){
			GAME_STATE_RUNNING = !GAME_STATE_RUNNING;
			return 0;
		}
		
		
	}
	save_player_data(gp);
	read_player_data();
	
	
	/*for(i=0;i<SIZE;i++)
	free((gp)->b[i]);
	free((gp)->b);
	free((gp)->player);
	free(gp);*/
	
	return 0;
}
GAME_PACKAGE * setup(){
/*	  GAME_PACKAGE * gp;
	GAME **b;
	int i;
	
	b = (GAME**) malloc(SIZE * sizeof(GAME**));
	for(i=0;i<SIZE;i++)
	b[i] = (GAME*)  malloc(SIZE * sizeof(GAME*));
	
	gp = (GAME_PACKAGE*) malloc(sizeof(GAME_PACKAGE*));
	
	(gp)->b = b;
	
	return gp;
	*/
	return NULL;
}
void welcome(GAME_PACKAGE * gp){
	char name[50], ch;
	int i=0;
	printf("\t########## WELCOME TO 2048 ##########");
	printf("\n\n\n\tPlease Enter Your Name : ");
	 /*while ((ch = getchar()) != '\n' && ch != EOF){
	 	fflush(stdin);
	 	name[i++] = ch;
	 } */
	 scanf("%s", name); 
	(gp)->score = 0;
	strcpy((gp)->player, name);
	printf("\n\n\n\t\t Welcome %s, Lets Begin!\n\n",name);
	
}
void won(GAME_PACKAGE * gp){
	printf("\n\n\n\n\n\n\n\t########## CONGRATULATIONS ##########\n");
	printf("\n\n\n\n\n\t\t--- %10s ---",(gp)->player);
	printf("\n\t\t--- Score :%i ---\n\n", (gp)->score);
	printf("\n\n\n\t######## YOU'VE WON THE GAME ########\n\n\n");
}
void lost(GAME_PACKAGE * gp){
	printf("\n\n\n\n\n\n\n\t########## GAME OVER! ##########\n");
	printf("\n\n\n\n\n\t\t--- %10s ---",(gp)->player);
	printf("\n\t\t--- Score :%i ---\n\n", (gp)->score);
	printf("\n\n\n\t######## YOU'VE LOST THE GAME ########\n\n\n");
}
bool check_game_state(GAME_PACKAGE * gp){
	int y, x;
	bool l = true;
	bool w = false;
	for(y=0;y<SIZE;y++){
		for(x=0;x<SIZE;x++){
			/*UP*/
			if(y > 0){
				if(((gp)->b[y][x]).g == ((gp)->b[y-1][x]).g){
					l = false;
				}
			}
			/*DOWN*/
			if(y < (SIZE-1)){
				if(((gp)->b[y][x]).g == ((gp)->b[y+1][x]).g){
					l= false;
				}
			}
			/*LEFT*/
			if(x > 0){
				if(((gp)->b[y][x]).g == ((gp)->b[y][x-1]).g){
					l= false;
				}
			}
			/*RIGHT*/
			if(x < (SIZE-1)){
				if(((gp)->b[y][x]).g == ((gp)->b[y][x+1]).g){
					l = false;
				}
			}
			if(((gp)->b[y][x]).g == 0){
				l = false;
			}
			if(((gp)->b[y][x]).g == WIN){
				w = true;
			}
		}
	}
	
	if(w){
		won(gp);
		return false;
	}else if(l){
		lost(gp);
		return false;
	}
	return true;
}
void init(GAME_PACKAGE * gp){
	int y=0, x=0;
	
	for(y=0;y<SIZE;y++){
		for(x=0;x<SIZE;x++){
			((gp)->b[y][x]).g= 0;
			((gp)->b[y][x]).m= NOT_CHANGED;	
		}
	}

	
	#ifdef DEBUG
	/*
	An array with predefined values for testing.
	*/
	((gp)->b[0][0]).g = 4; ((gp)->b[0][1]).g = 2; ((gp)->b[0][2]).g = 4; ((gp)->b[0][3]).g = 2;
	((gp)->b[1][0]).g = 2; ((gp)->b[1][1]).g = 4; ((gp)->b[1][2]).g = 2; ((gp)->b[1][3]).g = 4;
	((gp)->b[2][0]).g = 4; ((gp)->b[2][1]).g = 2; ((gp)->b[2][2]).g = 4; ((gp)->b[2][3]).g = 2;
	((gp)->b[3][0]).g = 0; ((gp)->b[3][1]).g = 4; ((gp)->b[3][2]).g = 2; ((gp)->b[3][3]).g = 4;
	#else
	
	magic_number(gp);
	magic_number(gp);
	
	#endif
}

void magic_number(GAME_PACKAGE * gp){
	int y, x, zero = 0;
	
	srand((unsigned)time(NULL));
	
	if(zero){
		while(1){
			y = rand() % SIZE;
			x = rand() % SIZE;
		
			if(((gp)->b[y][x]).g == 0){
				if((rand() % (SIZE*SIZE)) == 0){ ((gp)->b[y][x]).g = 4; }
				else 			{ ((gp)->b[y][x]).g = 2; }
				return;
			}
		}
	}
}
void insert_magic_number(GAME_PACKAGE * gp){
	int y, x, gen=0;
	srand((unsigned) time(NULL));
	for(y=0;y<SIZE;y++)
	for(x=0;x<SIZE;x++){

		if(((gp)->b[y][x]).g == 0){ gen++; }
	
	}
	if(gen > 0){
		while(gen){
			y = rand() % SIZE;
			x = rand() % SIZE;
			if(((gp)->b[y][x]).g == 0){
				gen = 0;
			}
		}
		if((rand() % SIZE) == 0){
			((gp)->b[y][x]).g =4;
		}else{  ((gp)->b[y][x]).g =2; }
	}
}
void re_init(GAME_PACKAGE * gp){
	int y, x;
	
	for(y=0;y<SIZE;y++){
		for(x=0;x<SIZE;x++){
			((gp)->b[y][x]).m=NOT_CHANGED;
		}
	}
}
void save_current_state(GAME_PACKAGE * gp){
	int y, x;
	
	for(y=0;y<SIZE;y++){
		for(x=0;x<SIZE;x++){
			((gp)->b[y][x]).p=((gp)->b[y][x]).g;
		}
	}
}
void load_previous_state(GAME_PACKAGE * gp){
	int y, x;
	
	for(y=0;y<SIZE;y++){
		for(x=0;x<SIZE;x++){
			((gp)->b[y][x]).g=((gp)->b[y][x]).p;
		}
	}
}
void save_player_data(GAME_PACKAGE * gp){
	FILE * f;
	f=fopen(DATA_FILE, "a+");
	if(f==NULL){
		printf("ERROR WRITTING TO FILE\n");
	}else{
		fprintf(f,"%s %i\n", (gp)->player , (gp)->score);
		fclose(f);
	}
	
}
void read_player_data(){
	char name[50];
	int score;
	FILE * f;
	f=fopen(DATA_FILE, "r");
	if(f==NULL){
		printf("ERROR READING FROM FILE\n");
	}else{
		printf("\n\n\n\n\n\t\t========== SCORE ==========\n\n");
		while(fscanf(f,"%s %i", name , &score) == 2){
			printf("\t\t%s\t-\t%i\n", name , score);
		}
		fclose(f);
	}
}
void print_array(GAME_PACKAGE * gp){
	int y, x;
	
	printf("\n\t\t");
	for(y=0;y<SIZE;y++){
		for(x=0;x<SIZE;x++){
			if(((gp)->b[y][x]).g == 0){
				printf("|        |\t");
			}else {	printf("|    %-4i|\t", ((gp)->b[y][x]).g); }
		}
		printf("\n\n\t\t");
	}printf("\n");
	
}
int get_user_input(GAME_PACKAGE * gp){
	
	char input;
	
	printf("\n\tENTER NEXT DIRECTION (Q|W|A|S|D|R) : ");
	
	/*input = getchar();
	getchar();*/
	input = getch();
	
	switch(input){
	
		case 'w':
		case 'W':
			return UP;
		break;
		
		case 'a':
		case 'A':
			return LEFT;
		break;
		
		case 's':
		case 'S':
			return DOWN;
		break;
		
		case 'd':
		case 'D':
			return RIGHT;
		break;
		
		case 'r':
		case 'R':
			return RIGHT;
		break;
		
		case 'q':
		case 'Q':
			return QUIT;
		break;
		
		default:
			return WRONG;
		break;
	}
	
}
void merge(GAME_PACKAGE * gp, int input){
	
	switch(input){
		case UP:
			merge_up(gp);
		break;
	
		case DOWN:
			merge_down(gp);
		break;
	
		case LEFT:
			merge_left(gp);
		break;
	
		case RIGHT:
			merge_right(gp);
		break;
	}
}
void merge_up(GAME_PACKAGE * gp){
	int y, x, back;
	for(x=0;x<SIZE;x++)
	for(y=0;y<SIZE;y++){
	
		if(((gp)->b[y][x]).g != 0){
			for(back=1;back<=y;back++){
				if(((gp)->b[(y-back)][x]).g != 0){
					if(((gp)->b[(y-back)][x]).g == ((gp)->b[y][x]).g &&
					((gp)->b[(y-back)][x]).m == NOT_CHANGED){
						((gp)->b[(y-back)][x]).g += ((gp)->b[y][x]).g;
						(gp)->score += ((gp)->b[(y-back)][x]).g;
						((gp)->b[y][x]).g = 0;
						((gp)->b[(y-back)][x]).m = CHANGED;
					
						back=y+1;
					}else{	back=y+1;	}
				}
			}
		}	
	}
	
}
void merge_down(GAME_PACKAGE * gp){
	int y, x, back;
	for(x=0;x<SIZE;x++)
	for(y=(SIZE-1);y>(SIZE-(SIZE+1));y--){
		
		if(((gp)->b[y][x]).g != 0){
			for(back=1;back<=((SIZE-1)-y);back++){
				if(((gp)->b[(y+back)][x]).g != 0){
					if(((gp)->b[(y+back)][x]).g == ((gp)->b[y][x]).g &&
					((gp)->b[(y+back)][x]).m == NOT_CHANGED){
						((gp)->b[(y+back)][x]).g += ((gp)->b[y][x]).g;
						(gp)->score += ((gp)->b[(y+back)][x]).g;
						((gp)->b[y][x]).g = 0;
						((gp)->b[(y+back)][x]).m = CHANGED;
					
						back=((SIZE-1)-y)+1;
					}else{	back=((SIZE-1)-y)+1;	}
				}
			}
		}	
	}
}
void merge_left(GAME_PACKAGE * gp){
	int y, x, back;
	for(y=0;y<SIZE;y++)
	for(x=0;x<SIZE;x++){
	
		if(((gp)->b[y][x]).g != 0){
			for(back=1;back<=x;back++){
				if(((gp)->b[y][(x-back)]).g != 0){
					if(((gp)->b[y][(x-back)]).g == ((gp)->b[y][x]).g &&
					((gp)->b[y][(x-back)]).m == NOT_CHANGED){
						((gp)->b[y][(x-back)]).g += ((gp)->b[y][x]).g;
						(gp)->score += ((gp)->b[y][(x-back)]).g;
						((gp)->b[y][x]).g = 0;
						((gp)->b[y][(x-back)]).m = CHANGED;
					
						back = x+1;
					}else{	back = x+1;	}
				}
			}
		}	
	}
}

void merge_right(GAME_PACKAGE * gp){
	int y, x, back;
	for(y=0;y<SIZE;y++)
	for(x=(SIZE-1);x>(SIZE-(SIZE+1));x--){
		if(((gp)->b[y][x]).g != 0){
			for(back=1;back<=((SIZE-1)-x);back++){
				if(((gp)->b[y][(x+back)]).g != 0){
					if(((gp)->b[y][(x+back)]).g == ((gp)->b[y][x]).g &&
					((gp)->b[y][(x+back)]).m == NOT_CHANGED){
						((gp)->b[y][(x+back)]).g += ((gp)->b[y][x]).g;
						(gp)->score += ((gp)->b[y][(x+back)]).g;
						((gp)->b[y][x]).g = 0;
						((gp)->b[y][(x+back)]).m = CHANGED;
						back=((SIZE-1)-x)+1;
					}else{	back=((SIZE-1)-x)+1; }
				}
			}
		}	
	}
}


void shift(GAME_PACKAGE * gp, int input){
	switch(input){
		case UP:
			shift_up(gp);
		break;
	
		case DOWN:
			shift_down(gp);
		break;
	
		case LEFT:
			shift_left(gp);
		break;
	
		case RIGHT:
			shift_right(gp);
		break;
	}
}
void shift_up(GAME_PACKAGE * gp){
	int y, x, back;
	for(x=0;x<SIZE;x++)
	for(y=0;y<SIZE;y++){
		if(((gp)->b[y][x]).g == 0){
			back = y+1;
			while(back<SIZE){
				if(((gp)->b[back][x]).g != 0){
					((gp)->b[y][x]).g = ((gp)->b[back][x]).g;
					((gp)->b[back][x]).g = 0;
					back=SIZE;
				}
				back++;
			}
		}	
	}
}
void shift_down(GAME_PACKAGE * gp){
	int y, x, back;
	for(x=0;x<SIZE;x++)
	for(y=(SIZE-1);y>0;y--){
		if(((gp)->b[y][x]).g == 0){
			back = y-1;
			while(back>-1){
				if(((gp)->b[back][x]).g != 0){
					((gp)->b[y][x]).g = ((gp)->b[back][x]).g;
					((gp)->b[back][x]).g = 0;
					back=-1;
				}
				back--;
			}
		}	
	}
}
void shift_left(GAME_PACKAGE * gp){
	int y, x, back;
	for(y=0;y<SIZE;y++)
	for(x=0;x<SIZE;x++){
		if(((gp)->b[y][x]).g == 0){
			back = x+1;
			while(back<SIZE){
				if(((gp)->b[y][back]).g != 0){
					((gp)->b[y][x]).g = ((gp)->b[y][back]).g;
					((gp)->b[y][back]).g = 0;
					back=SIZE;
				}
				back++;
			}
		}	
	}
}
void shift_right(GAME_PACKAGE * gp){
	int y, x, back;
	for(y=0;y<SIZE;y++)
	for(x=(SIZE-1);x>0;x--){
		if(((gp)->b[y][x]).g == 0){
			back = x-1;
			while(back>-1){
				if(((gp)->b[y][back]).g != 0){
					((gp)->b[y][x]).g = ((gp)->b[y][back]).g;
					((gp)->b[y][back]).g = 0;
					back=-1;
				}
				back--;
			}
		}	
	}
}

