#include <stdio.h>
#include <stdlib.h>

int ** getBoard(const int size);
void initializeBoard(int **board, int size);
void printBoard(int **board, int size);


int main(){
	int **board;
	
	board = getBoard( 5);
	initializeBoard(board, 5);
	printBoard(board, 5);
	
	return 0;
	
}

int ** getBoard(const int size){
	int i=0;
	int **newboard = (int**) malloc(size * sizeof(int*));
	for(i=0; i<size; i++)
		newboard[i] = (int*) malloc(size * sizeof(int*));
		
	return newboard;
}

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

void printBoard(int **board, int size){
	int i=0, j=0;
	for(i=0; i<size; i++){
		for(j=0;j<size;j++){
			printf("%i ", board[i][j]);
		}printf("\n");
	}
}

