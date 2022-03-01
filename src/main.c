#include <stdio.h>
#include <stdlib.h>

void clearBoard(int *currentGen,int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			*((currentGen + i * cols) + j) = 0;
		}
	}
}

void readBoard (int *currentGen,int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d",((currentGen + i * cols) + j));
		}
	}
}

void printBoard(int *currentGen,int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ",*((currentGen + i * cols) + j));
		}
		puts("\n");
	}
	puts("\n");
}

//TODO: 
// Missing edge cases
int countLiveNeighbours (int *currentPosition, int rows, int cols)
{
	int liveNeighbours = 0;

	if ( *(currentPosition - 1) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition + 1) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition - cols) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition - cols - 1) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition - cols + 1) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition + cols) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition + cols - 1) == 1) {
		liveNeighbours++;
	}
	if ( *(currentPosition + cols + 1) == 1) {
		liveNeighbours++;
	}

	return liveNeighbours;
}

void nextGeneration(int *prevGen, int *nextGen, int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if( *((prevGen + i * cols) + j) == 1 ) {
				int liveNeighbours = countLiveNeighbours((prevGen + i * cols) + j,rows,cols);
				if( liveNeighbours == 2 || liveNeighbours == 3) {
					*((nextGen + i * cols) + j) = 1;
				}
			}
			else if( *((prevGen + i * cols) + j) == 0 ) {
				int liveNeighbours = countLiveNeighbours((prevGen + i * cols) + j,rows,cols);
				if( liveNeighbours == 3) {
					*((nextGen + i * cols) + j) = 1;
				}
			}
		}
	}
}

int main (int argc, char *argv[])
{
	int rows,cols;
	scanf("%d",&rows);
	scanf("%d",&cols);

	int *prevGen = malloc(rows * cols * sizeof(int));
	int *nextGen = malloc(rows * cols * sizeof(int));

	readBoard(prevGen,rows,cols);

	int k = 0;
	while (k<2) {
		clearBoard(nextGen,rows,cols);
		nextGeneration(prevGen,nextGen,rows,cols);
		puts("---------------------");
		printBoard(prevGen,rows,cols);
		printBoard(nextGen,rows,cols);
		puts("---------------------");

		int *tmp = prevGen;
		prevGen = nextGen;
		nextGen = tmp;

		k++;
	}

	free(prevGen);
	free(nextGen);

	return 0;
}
