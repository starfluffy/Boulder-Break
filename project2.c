/* ENGGEN131 C Project 2022 - Boulder Break */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAVE_SIZE 10

// Task One: InitialiseStory
void InitialiseStory(char* paragraph)
{
	char temp[2000] = "You have been transported"; //come back to later
	strcpy(paragraph, temp);
}

// Task Two: PrintCave
void PrintCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int i;
	int j;

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 1) {
				printf("#");
			}
			else if (cave[i][j] == 0 || cave[i][j] == 8) { //8 means exit
				printf(" ");
			}
			else if (cave[i][j] == 2) { //2 means player
				printf("X");
			}
			else if (cave[i][j] == 3) { //3 means boulder
				printf("O");
			}
			else if (cave[i][j] == 4) { //4 means hole
				printf("*");
			}
			else if (cave[i][j] == 5) {// 5 means treasure
				printf("+");
			}
		}
		printf("\n");
	}
}

// Task Three: InitialiseCave
void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char *layout)
{
	int i;
	int j;
	int k = 0;

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (layout[k] == '1') {
				cave[i][j] = 1;
			}
			else if (layout[k] == '0') {
				cave[i][j] = 0;
			}
			else if (layout[k] == 'E') {
				cave[i][j] = 8; // 8 means exit
			}
			k++;
		}
	}
}

// As you work on the other tasks, remove the comments below
int IsBorderComplete(int cave[CAVE_SIZE][CAVE_SIZE]) 
{
// check top and bottom row, then left and right side

	int i;

	//rows
	for (i = 0; i < CAVE_SIZE; i++) {
		if (cave[0][i] == 0) {
			return 0;
		}
	}

	for (i = 0; i < CAVE_SIZE; i++) {
		if (cave[CAVE_SIZE - 1][i] == 0) {
			return 0;
		}
	}

	//columns
	for (i = 1; i < (CAVE_SIZE - 1); i++) {
		if (cave[i][0] == 0) {
			return 0;
		}
	}

	for (i = 1; i < (CAVE_SIZE - 1); i++) {
		if (cave[i][CAVE_SIZE - 1] == 0) {
			return 0;
		}
	}
	return 1;

}

int IsExitUnique(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int i;
	int j;
	int exits = 0;

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 8) {
				exits++;
				if (exits > 1) {
					return 0;
				}
			}
		}
	}
	if (exits == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int IsExitAccessible(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int i;

	//rows
	for (i = 1; i < (CAVE_SIZE - 1); i++) {
		if (cave[0][i] == 8) {
			return 1;
		}
	}

	for (i = 1; i < (CAVE_SIZE - 1); i++) {
		if (cave[CAVE_SIZE - 1][i] == 8) {
			return 1;
		}
	}

	//columns
	for (i = 1; i < (CAVE_SIZE - 1); i++) {
		if (cave[i][0] == 8) {
			return 1;
		}
	}

	for (i = 1; i < (CAVE_SIZE - 1); i++) {
		if (cave[i][CAVE_SIZE - 1] == 8) {
			return 1;
		}
	}
	return 0;
}

void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char *element)
{
	if ((row < CAVE_SIZE && col < CAVE_SIZE) && cave[row][col] == 0) {

		if (strcmp(element, "player") == 0) { // 2 means player
			//check numbers of players
			int players = 0;
			int i;
			int j;
			for (i = 0; i < CAVE_SIZE; i++) {
				for (j = 0; j < CAVE_SIZE; j++) {
					if (cave[i][j] == 2) {
						players++;
						if (players >= 1) {
							return;
						}
					}
				}
			}
			cave[row][col] = 2;
		}
		else if (strcmp(element, "boulder") == 0) { // 3 means boulder
			cave[row][col] = 3;
		}
		else if (strcmp(element, "hole") == 0) { // 4 means hole
			cave[row][col] = 4;
		}
		else if (strcmp(element, "treasure") == 0) {// 5 means treasure
			cave[row][col] = 5;
		}
	}
	else {
		return;
	}
}

void RotateCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int temp[CAVE_SIZE][CAVE_SIZE];
	
	int i;
	int j;

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			temp[j][(CAVE_SIZE-1) - i] = cave[i][j];
		}
	}

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			cave[i][j] = temp[i][j];
		}
	}


}

int MakeMove(int cave[CAVE_SIZE][CAVE_SIZE], char move)
{
	//find player (2)
	int i = 0;
	int j = 0;
	int row;
	int col;

	for (i = 0; i < CAVE_SIZE; i++) {
		for (j = 0; j < CAVE_SIZE; j++) {
			if (cave[i][j] == 2) {
				row = i;
				col = j;
			}
		}
	}

	// move up
	if (move == 'w') {
		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] != 1) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				if (cave[boulder][col] == 4) {
					cave[boulder - 1][col] = 0;
					cave[boulder][col] = 0;
					return 0;
				}
				boulder++;
			} return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 2;
		}
		return 0;
	}
	else if (move == 'd') {
		RotateCave(cave);
		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] != 1) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				if (cave[boulder][col] == 4) {
					cave[boulder - 1][col] = 0;
					cave[boulder][col] = 0;
					return 0;
				}
				boulder++;
			} return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 2;
		}
		return 0;
		RotateCave(cave);
		RotateCave(cave);
		RotateCave(cave);
	}
	else if (move == 's') {
		RotateCave(cave);
		RotateCave(cave);
		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] != 1) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				if (cave[boulder][col] == 4) {
					cave[boulder - 1][col] = 0;
					cave[boulder][col] = 0;
					return 0;
				}
				boulder++;
			} return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 2;
		}
		return 0;
		RotateCave(cave);
		RotateCave(cave);
	}
	else if (move == 'a') {
		RotateCave(cave);
		RotateCave(cave);
		RotateCave(cave);
		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] != 1) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				if (cave[boulder][col] == 4) {
					cave[boulder - 1][col] = 0;
					cave[boulder][col] = 0;
					return 0;
				}
				boulder++;
			} return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 2;
		}
		return 0;
		RotateCave(cave);
	}
	return 0;
}


/***********************************************************/
/***********************************************************/
/******* A SIMPLE MAIN FUNCTION TO TEST YOUR PROGRESS ******/
/***********************************************************/
/***********************************************************/

/* You should add your own tests in here */
int main(void)
{
	char story[2000];
	//char layout[200] = "1111111111111000001111000000111000000001100000000E10010000011100000011111000001111111001111111111111";
	//char layout[200] = "1111111111000000000110000000011000000001100000000110000000011000000001100000000110000000011111111111"; // complete
	//char layout[200] = "11111111111000000001100000000110000000011EEEEEEEE110000000011000000001100000000110000000011111111111"; // unique
	//char layout[200] = "111111111110000000011000000001100000000110000000011000000001100000000110000000011000000001111111111E"; // accesible
	//int cave[CAVE_SIZE][CAVE_SIZE] = {0};
	/*
	InitialiseStory(story);
	printf("%s\n", story);
	InitialiseCave(cave, layout);
	PrintCave(cave);
	//printf("Complete? %d\n", IsBorderComplete(cave));
	//printf("Unique? %d\n", IsExitUnique(cave));
	//printf("Accessible? %d\n", IsExitAccessible(cave));
	
	/*
	char layout[200] = "1111111111100000000110000000011000000001100000000E10000000011000000001100000000110000000011111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = { 0 };
	InitialiseCave(cave, layout);
	AddItem(cave, 7, 3, "player");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 2, 3, "boulder");
	AddItem(cave, 4, 6, "boulder");
	AddItem(cave, 5, 7, "boulder");
	AddItem(cave, 6, 8, "boulder");
	AddItem(cave, 7, 1, "hole");
	AddItem(cave, 8, 3, "hole");
	AddItem(cave, 6, 4, "treasure");
	AddItem(cave, 3, 5, "treasure");
	AddItem(cave, 1, 1, "treasure");
	PrintCave(cave);
	*/
	
	char layout[200] = "1111111111100000000110000000011000000001100000000E10000000011000000001100000000110000000011111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = { 0 };
	InitialiseCave(cave, layout);
	AddItem(cave, 0, 0, "player");
	AddItem(cave, 5, 5, "player");
	AddItem(cave, 6, 6, "player");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 2, 2, "boulder");
	AddItem(cave, 1000, 1000, "boulder");
	PrintCave(cave);
	
	/*
	char layout[200] = "1111111111100000000110000000011000000001100000000E10000000011000000001100000000110000000011111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = { 0 };
	InitialiseCave(cave, layout);
	AddItem(cave, 5, 5, "boulder");
	AddItem(cave, 5, 6, "boulder");
	AddItem(cave, 5, 7, "boulder");
	AddItem(cave, 2, 2, "player");
	printf("Original position:\n");
	PrintCave(cave);
	printf("First rotation:\n");
	RotateCave(cave);
	PrintCave(cave);
	printf("Second rotation:\n");
	RotateCave(cave);
	PrintCave(cave);
	printf("Third rotation:\n");
	RotateCave(cave);
	PrintCave(cave);
	printf("Fourth rotation:\n");
	RotateCave(cave);
	PrintCave(cave);
	*/
	return 0;
}