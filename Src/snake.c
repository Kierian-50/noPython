/**
  ******************************************************************************
  * @file           : snake.c
  * @brief          : This file regroup all functions allowing to play a move and display snake matrix
  ******************************************************************************
  */

#include "snake.h"

const struct Case myCase = {0, 1, 2};
const struct State state = {0, 1, 2};
const struct Direction direction = {0, 1, 2, 3};
const unsigned short M_HEIGHT = 8;
const unsigned short M_WIDTH = 8;
const unsigned short MAX_SNAKE_LENGTH = M_HEIGHT * M_WIDTH + 1;
unsigned short score = 0;

/**
 * This methods allows to move the snake by duplicating coordinates of first element of the snake, remove
 * last element of the snake and change coordinates of one of the duplicated values in function of the new direction
 * @param matrix - matrix where snake will be put
 * @param snake - coordinates of the current snake
 * @param newDirection - new direction to move on
 * @param apple - coordinates of the apple
 * @return game status (WIN, LOSE or RUNNING)
 */
unsigned short move(unsigned short matrix[M_HEIGHT][M_WIDTH], unsigned short snake[MAX_SNAKE_LENGTH][2], unsigned short newDirection, unsigned short apple[2]) {

	// init move variable
	unsigned short gameState = state.RUNNING;
	unsigned short increment = 1;

	// shift snake array values by one case, so first two element have the same coordinate
	for (short i = score; i >= 0; i--) {
		snake[i + 1][0] = snake[i][0];
		snake[i + 1][1] = snake[i][1];
	}

	// set last value of shifted array to 0, we don't need him anymore.
	snake[score + 1][0] = 0;
	snake[score + 1][1] = 0;

	// Check for direction, then check if snake is on the border of the game board or if the next square is
	// already taken by the snake. If it's the case, set lose, else change coordinate of the first element
	// of the snake array to move it
	if (newDirection == direction.DOWN) {
		if (snake[0][0] == M_HEIGHT - 1 || matrix[snake[0][0] + increment][snake[0][1]] == myCase.SNAKE) {
			gameState = state.LOSE;
		} else {
			snake[0][0] = snake[0][0] + increment;
		}
	} else if (newDirection == direction.UP) {
		if (snake[0][0] == 0 || matrix[snake[0][0] - increment][snake[0][1]] == myCase.SNAKE) {
			gameState = state.LOSE;
		} else {
			snake[0][0] = snake[0][0] - increment;
		}
	} else if (newDirection == direction.LEFT) {
		if (snake[0][1] == 0 || matrix[snake[0][0]][snake[0][1] - increment] == myCase.SNAKE) {
			gameState = state.LOSE;
		} else {
			snake[0][1] = snake[0][1] - increment;
		}
	} else if (newDirection == direction.RIGHT) {
		if (snake[0][1] == M_WIDTH - 1 || matrix[snake[0][0]][snake[0][1] + increment] == myCase.SNAKE) {
			gameState = state.LOSE;
		} else {
			snake[0][1] = snake[0][1] + increment;
		}
	}

	// if head of snake touch an apple, increment snake length and change apple coordinates randomly
	if (snake[0][0] == apple[0] && snake[0][1] == apple[1]) {
		apple[0] = rand() % M_WIDTH;
		apple[1] = rand() % M_HEIGHT;
		snake[score+1][0] = snake[score][0];
		snake[score+1][1] = snake[score][1];
		score++;
	}

	// clear matrix
	for (unsigned short i = 0; i < M_HEIGHT; i++) {
		for (unsigned short j = 0; j < M_WIDTH; j++) {
			matrix[i][j] = myCase.EMPTY;
		}
	}

	// set new apple and snake positions on matrix
	matrix[apple[0]][apple[1]] = myCase.APPLE;
	for (unsigned short i = 0; i < score + 1; i++) {
		matrix[snake[i][0]][snake[i][1]] = myCase.SNAKE;
	}

	// draw matrix
	displayArray(matrix);

	// if length of snake is equal or greater than 80% of his max length, set win
	if (score >= (unsigned short)(MAX_SNAKE_LENGTH - 1 - (20*(MAX_SNAKE_LENGTH - 1))/100)) gameState = state.WIN;

	return gameState;
}

/**
 * This method allows to display a game board matrix on a terminal.
 * @param matrix - matrix to display
 */
void displayArray(unsigned short matrix[M_HEIGHT][M_WIDTH]) {
	// flush output
	printf("\e[1;1H\e[2J");
	// display the new matrix
	printf("---------------------------------\r\n");
	for (unsigned short i = 0; i < M_HEIGHT; i++) {
		printf("|");
		for (unsigned short j = 0; j < M_WIDTH; j++) {
			if (matrix[i][j] == myCase.SNAKE) {
				printf(" * |");
			} else if (matrix[i][j] == myCase.APPLE) {
				printf(" o |");
			} else {
				printf("   |");
			}
		}
		printf("\r\n---------------------------------\r\n");
	}
}


