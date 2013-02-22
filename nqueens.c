#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void rotateboard();
int checkiso();

int *board;
int n, count;

struct node {
	int *board;
	struct node *next;
};

int check(int row, int column)
{
	int i;
	for (i = 0; i < row; i++) {
		if ((row - i) == (abs(column - board[i])) || column == board[i])
			return 0;
	}

	return 1;
}

int comparevec(int *v1, int *v2)
{
	int i;
	for (i = 0; i < n; i++) {
		if (v1[i] < v2[i])
			return 0;
		else if (v1[i] > v2[i])
			return 1;
	}
	return -1;
}

void solveboard(int row)
{
	int column, i;

	if (row == n) {
		if (checkiso() != 0) {
			/*for (i = 0; i < n; i++)
				printf("%d ", board[i]);
			printf("\n");*/
			count++;
		}
	}

	for (column = 0; column < n; column++) {
		if (check(row, column) == 1) {
			board[row] = column;
			solveboard(row+1);
		}
	}
}
void mirror(int *vec)
{
	int i;
	for (i = 0; i < n; i++)
		vec[i] = (n-1) - vec[i];
}
void rotateboard(int *b)
{
	int *temp = (int *) calloc(n, sizeof(int));
	int i;

	for (i = 0; i < n; i++)
		temp[b[i]] = i;
	for (i = 0; i < n; i++)
		b[i] = temp[(n-1) - i];
	free(temp);
}

int checkiso()
{
	int i, iso;
	int *transform = (int *) calloc(n, sizeof(int));

	for (i = 0; i < n; i++)
		transform[i] = board[i];

	for (i = 0; i < 7; i++) {
		if (i != 3)
			rotateboard(transform);
		else
			mirror(transform);
		iso = comparevec(board, transform);
		if (!iso) return 0;
	}
	return 1;
}
int main(int argc, char *argv[])
{
	if (argv[1] == NULL)
		exit(EXIT_FAILURE);
	n = atoi(argv[1]);
	if (n < 1)
		exit(EXIT_FAILURE);

	board = (int *) calloc(n, sizeof(int));

	solveboard(0);
	printf("# of boards: %d\n", count);
	return 0;
}	
