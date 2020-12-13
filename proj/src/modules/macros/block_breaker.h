#ifndef _LCOM_BLOCK_BREAKER_H_
#define _LCOM_BLOCK_BREAKER_H_

#include <lcom/lcf.h>

// NOTE - add brief descriptions of each variable
#define SOLO_SCENARIO_CORNER_X 240
#define SOLO_SCENARIO_CORNER_Y 60
#define SCENARIO_WIDTH 320
#define SCENARIO_HEIGHT 480
#define TIMER_BACK_HEIGHT 40
#define BORDER_WIDTH 5

#define PLATAFORM_TO_LEFT_X 116
#define PLATAFORM_TO_TOP_Y_INIT 428
#define PLATAFORM_HEIGHT 10

#define BLOCKS_TO_LEFT_X 20
#define BLOCKS_TO_TOP_Y 90
#define BLOCKS_WIDTH 40
#define BLOCKS_HEIGHT 20
#define NUMBER_BLOCKS_X 7
#define NUMBER_BLOCKS_Y 4
#define NUMBER_BLOCKS_COLORS 7

#define FIRST_NUMBER_TO_LEFT_X 135
#define FIRST_NUMBER_TO_TOP_Y 15
#define NUMBERS_WIDTH 12
#define NUMBERS_HEIGHT 18
#define SPACE_BETWEEN_NUMBERS 2

#define FIRST_HEART_TO_RIGHT_X 15
#define FIRST_HEART_TO_TOP_Y 13
#define HEART_WIDTH 23
#define HEART_HEIGHT 20
#define SPACE_BETWEEN_HEARTS 2

#define BALL_TO_LEFT_X 153
#define BALL_TO_TOP_Y 410
#define BALL_WIDTH 14
#define BALL_HEIGHT 14
#define BALL_LIMIT_TOP (SOLO_SCENARIO_CORNER_Y + BLOCKS_TO_TOP_Y + (NUMBER_BLOCKS_Y * BLOCKS_HEIGHT))
#define BALL_DOWN_LIMIT PLATAFORM_TO_TOP_Y_INT
#define BALL_LEFT_LIMIT SOLO_SCENARIO_CORNER_X + BORDER_WIDTH
#define BALL_RIGHT_LIMIT SOLO_SCENARIO_CORNER_X + BORDER_WIDTH + SCENARIO_WIDTH
#define BALL_SPEED 10

#define SCENARIO_BACKGROUND_COLOR 0x212b72
#define SCENARIO_BORDER_COLOR 0x888787
#define TIMER_BACKGROUND_COLOR 0x343131
#define NUMBERS_COLOR 0xffffff

#define PLATAFORM_DISPLACEMENT 20

#endif /* _LCOM_BLOCK_BREAKER_H_ */