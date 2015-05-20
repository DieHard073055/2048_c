#include <stdio.h>
#include <stdlib.h>

int ** getBoard(const int size);
void initializeBoard(int **board, int size);
void printBoard(int **board, int size);

/*
	Main Function
	-Creates a 2D array pointer board
	-Calls the function getBoard to assign some space from the RAM
	-Calls initializeBoard to fill the array with 2's and 0's
	-Prints the board to screen
	

*/
int main(){
	int **board;
	
	board = getBoard( 5);
	initializeBoard(board, 5);
	printBoard(board, 5);
	
	return 0;
	
}
/*
	Get Board
	@param size : Pass the size of the board 
	the function will allocate the specified size of the board from the RAM 
*/
int ** getBoard(const int size){
	int i=0;
	int **newboard = (int**) malloc(size * sizeof(int*));
	for(i=0; i<size; i++)
		newboard[i] = (int*) malloc(size * sizeof(int*));
		
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
	
	srand(time(NULL));
	while(quota != 0){
		for(i=0; i<size; i++){
			for(j=0;j<size;j++){
				if(board[i][j] != 2){
					if((rand() % 50) == 25 && quota > 0){ board[i][j] = 2; quota--; } 
					else{ board[i][j] = 0;	}
				}
			}
		}
		if(!quota) printf("quota : %d\n\n", quota);
	}
}
/*
	Print Board
	@param board : The Game array Board
	@param size : The size of the game board
	
	This Function will print out the 2D Game Board board.
*/
void printBoard(int **board, int size){
	int i=0, j=0;
	for(i=0; i<size; i++){
		for(j=0;j<size;j++){
			printf("%i ", board[i][j]);
		}printf("\n");
	}
}

