#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG
#define VERBOSE 0
/*
VERBOSE 0 = DEBUG MESSAGES
VERBOSE 1 = ALL MESSAGES
*/
#define RUNNING 1


/*DEBUG FILE*/
FILE * DEBUG_F;
/*
	Function Prototypes
*/
int ** getBoard(const int size);
void initializeBoard(int **board, int size);
void printBoard(int **board, int size);
void openDebugFile();
void closeDebugFile();
void printd(const char * msg, int verbose);
/*
	Main Function
	-Creates a 2D array pointer board
	-Calls the function getBoard to assign some space from the RAM
	-Calls initializeBoard to fill the array with 2's and 0's
	-Prints the board to screen
	

*/
int main(){
	int **board;
	int game_state = 1;
	openDebugFile();
	
	board = getBoard(5);
	initializeBoard(board, 5);
	
	
	
/*	while(game_state == RUNNING)*/
	printBoard(board, 5);
	
	closeDebugFile();
	return 0;
	
}
/*
	Get Board
	@param size : Pass the size of the board 
	the function will allocate the specified size of the board from the RAM 
*/
int ** getBoard(const int size){
	int i=0;
	
	printd("getBoard(): -- Function Start", 0);
	
	int **newboard = (int**) malloc(size * sizeof(int*));
	for(i=0; i<size; i++)
		newboard[i] = (int*) malloc(size * sizeof(int*));
	
	printd("getBoard(): -- Function End", 0);
	
	return newboard;
}
/*
	Initialize Board
	@param board : The Game array Board
	@param size : The size of the game board
	
	The function will fill the array with 0's and randomly assign 2's
	the number of 2 it assigns has a quota which is 2.

*/
void initializeBoard(int **board, int size){
	int i=0, j=0, quota = 2;
	char msg[100];
	printd("initializeBoard(): -- Function Start", 0);
	
	srand(time(NULL));
	while(quota != 0){
		for(i=0; i<size; i++){
			for(j=0;j<size;j++){
				if(board[i][j] != 2){
					if((rand() % 50) == 25 && quota > 0){
						board[i][j] = 2; 
						sprintf(msg, "initializeBoard(): -- board[%i][%i] = 2", i, j);
						printd(msg, 1);
						quota--; 
						sprintf(msg, "initializeBoard(): -- quota = : %d", quota);
						printd(msg, 1);
					} 
					else{ 
						board[i][j] = 0;
						sprintf(msg, "initializeBoard(): -- board[%i][%i] = 0", i, j);
						printd(msg, 1);	
					}
				}
			}
		}
		if(!quota) printf("quota : %d\n\n", quota);
	}
	
	printd("initializeBoard(): -- Function End", 0);
}
/*
	Print Board
	@param board : The Game array Board
	@param size : The size of the game board
	
	This Function will print out the 2D Game Board board.
*/
void printBoard(int **board, int size){
	int i=0, j=0;

	printd("printBoard(): -- Function Start", 0);

	for(i=0; i<size; i++){
		for(j=0;j<size;j++){
			printf("%i ", board[i][j]);
		}printf("\n");
	}
	
	printd("printBoard(): -- Function End", 0);
}

void openDebugFile(){
	time_t now;
	char filename[100];
	int i, size;
	
	/*Getting Debug Filename*/
	time(&now);
	size = sprintf(filename, "error_file %21s.txt", ctime(&now));
	for(i=0;i<size;i++){ 
		if(filename[i] == ' ' || filename[i] == ':')
		{filename[i] = '_';}
	}
	/*Open File*/
	DEBUG_F=fopen(filename, "w");
}
void closeDebugFile(){
	fclose(DEBUG_F);
}
void printd(const char * msg, int verbose){
	if(verbose <= VERBOSE)
	fprintf( DEBUG_F, "%d | %s\n", verbose, msg);
}

