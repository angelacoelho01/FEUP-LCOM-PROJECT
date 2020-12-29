#include "graphics.h"

#include <time.h>
#include <stdlib.h>

#include "../game/collision/collision.h"
#include "../../xpm/xpm.h"
#include "../../xpm/load_xpms.h"

extern vbe_mode_info_t mode_conf;
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;


uint16_t plataform_x; 

size_t plataform_to_draw = 0;
uint8_t no_lives = 3; 
uint8_t minutes = 0, seconds = 0;

void (draw_scenario)(uint16_t xi, uint16_t yi){
  // Draw the scenario background
  video_draw_rectangle(xi, yi, SCENARIO_WIDTH, SCENARIO_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  // Draw the background for the timer
  video_draw_rectangle(xi, yi, SCENARIO_WIDTH, TIMER_BACK_HEIGHT, TIMER_BACKGROUND_COLOR);

  // Draw the borders of the scenario
  // Top border
  video_draw_rectangle(xi, yi, SCENARIO_WIDTH, BORDER_WIDTH, SCENARIO_BORDER_COLOR);
  // Bottom border
  video_draw_rectangle(xi, yi + SCENARIO_HEIGHT - BORDER_WIDTH, SCENARIO_WIDTH, BORDER_WIDTH, SCENARIO_BORDER_COLOR);
  // Left border
  video_draw_rectangle(xi, yi, BORDER_WIDTH, SCENARIO_HEIGHT, SCENARIO_BORDER_COLOR);
  // Right border
  video_draw_rectangle(xi + SCENARIO_WIDTH - BORDER_WIDTH, yi, BORDER_WIDTH, SCENARIO_HEIGHT, SCENARIO_BORDER_COLOR);

  // Draw the matrix of blocks in is inicial position
  draw_blocks(xi + BLOCKS_TO_LEFT_X, yi + BLOCKS_TO_TOP_Y);

  // Draw the plataform in is inicial coordenates and format
  draw_plataform(xi + PLATAFORM_TO_LEFT_X_INIT + (6*plataform_to_draw), yi + PLATAFORM_TO_TOP_Y, xi, plataforms_xpms[plataform_to_draw]);
 

  // Draw the ball in is inicial coordenates 
  draw_ball(xi + BALL_TO_LEFT_X, yi + BALL_TO_TOP_Y);

  // Draw the 3 inicial lives of the player
  draw_hearts(0, no_lives, xi + SCENARIO_WIDTH - FIRST_HEART_TO_RIGHT_X, yi + FIRST_HEART_TO_TOP_Y);

  // Draw the inicial clock 00:00
  draw_clock(minutes, seconds, xi + FIRST_NUMBER_TO_LEFT_X, yi + FIRST_NUMBER_TO_TOP_Y);
}

void (game_over_display)(uint16_t xi, uint16_t yi){
	// o jogador nao pode interagir mais com o jogo - nao permite mover a paltaforma
	// timer para de contar - no more interrupçoes
	// blocos ficam onde estao como estao
	
	// plataforma volta à sua posicao inicial
	draw_plataform(xi + PLATAFORM_TO_LEFT_X_INIT + (6*plataform_to_draw), yi + PLATAFORM_TO_TOP_Y, xi, plataforms_xpms[plataform_to_draw]);
	
	// a bola volta à sua posicao inicial
	draw_ball(xi + BALL_TO_LEFT_X, yi + BALL_TO_TOP_Y);
	
	// label of game over
	draw_game_over_label(xi + GAME_OVER_TO_LEFT_X, yi + GAME_OVER_TO_TOP_Y);
}

void (game_win_display)(uint16_t xi, uint16_t yi, struct Player player){
	// o jogador nao pode interagir mais com o jogo - nao permite mover a paltaforma
	// timer para de contar - gerada a pontuacao do jogador
	// nao existem blocos

	// plataforma volta à sua posicao inicial
	draw_plataform(xi + PLATAFORM_TO_LEFT_X_INIT + (6*plataform_to_draw), yi + PLATAFORM_TO_TOP_Y, xi, plataforms_xpms[plataform_to_draw]);
	
	// a bola volta à sua posicao inicial
	draw_ball(xi + BALL_TO_LEFT_X, yi + BALL_TO_TOP_Y);
	
	// label of you win
	draw_game_win_label(xi + YOU_WIN_TO_LEFT_X, yi + YOU_WIN_TO_TOP_Y);
	
	// label of score
	draw_score_label(xi + SCORE_LABEL_TO_LEFT_X, yi + SCORE_LABEL_TO_TOP_Y);
	
	// draw score value
	unsigned int player_score = calculate_player_score(minutes, seconds, no_lives);
	draw_score_value(xi + SCORE_VALUE_TO_LEFT_X, yi + SCORE_VALUE_TO_TOP_Y, player_score);
}

void (draw_score_value)(uint16_t x, uint16_t y, unsigned int score) {
  bool clock = false;
	uint8_t no_digits = util_get_no_digits(score);

	// get the digits of the score value from the last to the first
	while (no_digits > 0){
		uint8_t number = score / pow(10, no_digits - 1);
		draw_number(number, x, y, clock);
		
		// next number
		score %= (unsigned int)pow(10, no_digits - 1);
		x += NUMBERS_WIDTH + SPACE_BETWEEN_NUMBERS; 
		--no_digits;
	}
}

void (clean_screen)(uint16_t w, uint16_t h, uint32_t color) {
  video_draw_rectangle(0, 0, w, h, color);
}
