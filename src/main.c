#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void clearBoard(int *currentGen,int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			*((currentGen + i * cols) + j) = 0;
		}
	}
}

void createSeed (int *currentGen,int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			*((currentGen + i * cols) + j) = rand() % 2; 
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

int countLiveNeighbours (int *currentPosition,int offset, int rows, int cols)
{
	int liveNeighbours = 0;

	if ( (offset % cols != 0) && (*(currentPosition - 1) == 1)) {
		liveNeighbours++;
	}
	if ( (offset % cols != (cols - 1)) && *(currentPosition + 1) == 1) {
		liveNeighbours++;
	}
	if (offset > cols && *(currentPosition - cols) == 1) {
		liveNeighbours++;
	}
	if (( (offset > cols) || (offset % cols != 0) ) && *(currentPosition - cols - 1) == 1) {
		liveNeighbours++;
	}
	if ( ((offset > cols) || (offset % cols != (cols - 1)) ) && *(currentPosition - cols + 1) == 1) {
		liveNeighbours++;
	}
	if ( (offset < (rows*(cols-1))) && *(currentPosition + cols) == 1) {
		liveNeighbours++;
	}
	if ( ((offset < (rows*(cols-1))) || (offset % cols != 0)) &&  *(currentPosition + cols - 1) == 1) {
		liveNeighbours++;
	}
	if ( ((offset < (rows*(cols-1))) || (offset % cols != (cols - 1)) ) &&  *(currentPosition + cols + 1) == 1) {
		liveNeighbours++;
	}

	return liveNeighbours;
}

void nextGeneration(int *prevGen, int *nextGen, int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int offset = (i * cols) + j;
			if( *(prevGen + offset) == 1 ) {
				int liveNeighbours = countLiveNeighbours(prevGen + offset,offset,rows,cols);
				if( liveNeighbours == 2 || liveNeighbours == 3) {
					*(nextGen + offset) = 1;
				}
			}
		else if( *(prevGen + offset) == 0 ) {
				int liveNeighbours = countLiveNeighbours(prevGen + offset,offset,rows,cols);
				if( liveNeighbours == 3) {
					*(nextGen + offset) = 1;
				}
			}
		}
	}
}

int sameGeneration (int *prevGen, int *nextGen, int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if ( *((prevGen + i * cols) + j) != *((nextGen+ i * cols) + j) ) {
				return 0;
			}
		}
	}
	return 1;
}

int main (int argc, char *argv[])
{
	int rows,cols;
	scanf("%d",&rows);
	scanf("%d",&cols);

	int *prevGen = malloc(rows * cols * sizeof(int));
	int *nextGen = malloc(rows * cols * sizeof(int));

	createSeed(prevGen,rows,cols);

	puts("---------------------");
	printBoard(prevGen,rows,cols);
	puts("---------------------");

	int gen = 1;
	do {

		clearBoard(nextGen,rows,cols);
		nextGeneration(prevGen,nextGen,rows,cols);

		system("clear");
		puts("---------------------");
		printf("Generation: %d\n",gen);
		printBoard(nextGen,rows,cols);
		puts("---------------------");

		int *tmp = prevGen;
		prevGen = nextGen;
		nextGen = tmp;

		gen++;

		sleep(1);

	} while(!sameGeneration(prevGen,nextGen,rows,cols));

	free(prevGen);
	free(nextGen);

	return 0;
}
