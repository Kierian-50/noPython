/**
  ******************************************************************************
  * @file           : snake.h
  * @brief          : Header for snake.c file.
  *                   This file contains the common defines for playing to the snake game
  ******************************************************************************
  */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
* Define direction possibilities : DOWN, UP, LEFT or RIGHT
*/
struct Direction {
	unsigned short DOWN;
	unsigned short UP;
	unsigned short LEFT;
	unsigned short RIGHT;
};

/**
* Define case possibilities : EMPTY, SNAKE or APPLE
*/
struct Case {
	unsigned short EMPTY;
	unsigned short SNAKE;
	unsigned short APPLE;
};

/**
* Define game state possibilities : RUNNING, WIN or LOSE
*/
struct State {
	unsigned short RUNNING;
	unsigned short WIN;
	unsigned short LOSE;
};

/**
* Define case status
*/
extern const struct Case myCase;
/**
* Define game status
*/
extern const struct State state;
/**
* Define current move direction status
*/
extern const struct Direction direction;
/**
* Define matrix height
*/
extern const unsigned short M_HEIGHT;
/**
* Define matrix width
*/
extern const unsigned short M_WIDTH;
/**
* Define max snake length in function of matrix size
*/
extern const unsigned short MAX_SNAKE_LENGTH;
/**
* Define player score
*/
extern unsigned short score;

unsigned short move(unsigned short matrix[M_HEIGHT][M_WIDTH], unsigned short snake[MAX_SNAKE_LENGTH][2], unsigned short newDirection, unsigned short apple[2]);
void displayArray(unsigned short matrix[M_HEIGHT][M_WIDTH]);

#endif /* INC_SNAKE_H_*/
