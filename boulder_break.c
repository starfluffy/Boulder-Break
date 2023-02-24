/* ENGGEN131 C Project 2022 - Boulder Break */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAVE_SIZE 5

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

// Your function definitions should go here...
void InitialiseStory(char* paragraph)
{
	char temp[2000] = "It was a warm summer\'s night and a full moon shone\nbrightly in the cloudless sky. You decide to take a walk by\nthe river. While walking, you suddenly fall into the water\nand blackout but instead of finding yourself in front of\nheaven\'s gates, you open your eyes and discover you\'re in a\nbizarre cave! A screen appears with the words:\n\n*\"Greetings, brave traveller. Welcome to the miraculous\ncave of reincarnation where special individuals are gifted\nwith the opportunity to win their soul back from the\nunderworld just by simply finding their way out of the\ncave! Pick up treasures and use boulders to plug up holes.\n\t\t   Do you accept?\"*\n\nYou are hesitant but accept and begin your adventure. . .";
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
void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char* layout)
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

void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char* element)
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
			temp[j][(CAVE_SIZE - 1) - i] = cave[i][j];
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

	// move up
	if (move == 'w') {
		//find player (2)
		int i = 0;
		int j = 0;
		int row = 0;
		int col = 0;

		for (i = 0; i < CAVE_SIZE; i++) {
			for (j = 0; j < CAVE_SIZE; j++) {
				if (cave[i][j] == 2) {
					row = i;
					col = j;
				}
			}
		}

		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] == 0) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				boulder--;
			}
			if (cave[boulder-1][col] == 4) {
				cave[boulder - 1][col] = 0;
				cave[boulder][col] = 0;
				return 0;
			}
			return 0;
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
	else if (move == 'a') {
		RotateCave(cave);
		//find player (2)
		int i = 0;
		int j = 0;
		int row = 0;
		int col = 0;

		for (i = 0; i < CAVE_SIZE; i++) {
			for (j = 0; j < CAVE_SIZE; j++) {
				if (cave[i][j] == 2) {
					row = i;
					col = j;
				}
			}
		}

		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			RotateCave(cave);
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] == 0) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				boulder--;
			}
			if (cave[boulder-1][col] == 4) {
				cave[boulder - 1][col] = 0;
				cave[boulder][col] = 0;
				RotateCave(cave);
				RotateCave(cave);
				RotateCave(cave);
				return 0;
			}
			RotateCave(cave);
			RotateCave(cave);
			RotateCave(cave); 
			return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			RotateCave(cave);
			RotateCave(cave);
			RotateCave(cave);
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			RotateCave(cave);
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			RotateCave(cave);
			RotateCave(cave);
			return 2;
		}
		RotateCave(cave);
		RotateCave(cave);
		RotateCave(cave);
		return 0;
	}
	else if (move == 's') {
		RotateCave(cave);
		RotateCave(cave);
		//find player (2)
		int i = 0;
		int j = 0;
		int row = 0;
		int col = 0;

		for (i = 0; i < CAVE_SIZE; i++) {
			for (j = 0; j < CAVE_SIZE; j++) {
				if (cave[i][j] == 2) {
					row = i;
					col = j;
				}
			}
		}

		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] == 0) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				boulder--;
			}
			if (cave[boulder-1][col] == 4) {
				cave[boulder - 1][col] = 0; 
				cave[boulder][col] = 0;
				RotateCave(cave);
				RotateCave(cave);
				return 0;
			}
			RotateCave(cave);
			RotateCave(cave); 
			return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			RotateCave(cave);
			RotateCave(cave);
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			RotateCave(cave);
			return 2;
		}
		RotateCave(cave);
		RotateCave(cave);
		return 0;
	}
	else if (move == 'd') {
		RotateCave(cave);
		RotateCave(cave);
		RotateCave(cave);
		//find player (2)
		int i = 0;
		int j = 0;
		int row = 0;
		int col = 0;

		for (i = 0; i < CAVE_SIZE; i++) {
			for (j = 0; j < CAVE_SIZE; j++) {
				if (cave[i][j] == 2) {
					row = i;
					col = j;
				}
			}
		}

		if (cave[row - 1][col] == 0) { // nothing in front so moves up
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 3) { //moving boulder
			i = 0;
			int boulder = row - 1;
			while (cave[boulder - 1][col] == 0) {
				cave[boulder - 1][col] = 3;
				cave[boulder][col] = 0;
				boulder--;
			}
			if (cave[boulder-1][col] == 4) {
				cave[boulder - 1][col] = 0;
				cave[boulder][col] = 0;
				RotateCave(cave);
				return 0;
			}
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 4) { // failling into hole
			cave[row][col] = 0;
			RotateCave(cave);
			return 1;
		}
		else if (cave[row - 1][col] == 5) { // picking up treasure
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			return 0;
		}
		else if (cave[row - 1][col] == 8) { //finding exit
			cave[row][col] = 0;
			cave[row - 1][col] = 2;
			RotateCave(cave);
			return 2;
		}
		RotateCave(cave);
		return 0;
	}
	return 0;
}


/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
		scanf("%c", &move);
	}
	return move;
}

/* The Boulder Break simulation */
int main(void)
{
	char story[2000];
	//char layout[200] = "1111111111111000001111000000111000000001100000000E10010000011100000011111000001111111001111111111111";
	char layout[200] = "11111100011000E1000111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = {0};
	int gameOver = 0;

	InitialiseStory(story);
	InitialiseCave(cave, layout);
	/*
	AddItem(cave, 2, 4, "boulder");
	AddItem(cave, 5, 6, "boulder");
	AddItem(cave, 4, 8, "hole");
	AddItem(cave, 1, 4, "treasure");
	AddItem(cave, 4, 5, "player");
	*/
	AddItem(cave, 2, 3, "boulder");
	AddItem(cave, 3, 1, "treasure");
	AddItem(cave, 1, 2, "player");

	printf("ENGGEN131 - C Project 2022\n");
	printf("                          ... presents ...\n");
	printf("______   _____  _     _        ______  _______  ______\n");
	printf("|_____] |     | |     | |      |     \\ |______ |_____/\n");
	printf("|_____] |_____| |_____| |_____ |_____/ |______ |    \\_\n");
	printf("______   ______ _______ _______ _     _\n");
	printf("|_____] |_____/ |______ |_____| |____/ \n");
	printf("|_____] |    \\_ |______ |     | |    \\_\n");
	printf("\n");
	printf("%s\n", story);
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	PrintCave(cave);
	while (!gameOver) {
		gameOver = MakeMove(cave, GetMove());
		PrintCave(cave);
		if (gameOver == 1) {
			printf("\n\nGAME OVER!! \nYou died!\n\n");
		} else if (gameOver == 2) {
			printf("\n\nCONGRATULATIONS!! \nYou escaped!\n\n");
		}
	}

	return 0;
}