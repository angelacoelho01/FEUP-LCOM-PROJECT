#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include <math.h>

#include "../macros/block_breaker.h"
#include "../macros/i8042.h"

#include "../keyboard/keyboard.h"
#include "../video/video.h"
#include "../../utils/utils.h"
#include "../../xpm/labels.h"
#include "../player/player.h"

int (draw_scenario)(uint16_t xi, uint16_t yi);

int (draw_plataform)(xpm_map_t xpm, uint16_t x, uint16_t y, uint16_t scenario_x);

int (draw_blocks)(uint16_t xi, uint16_t yi);

void (clean_ball)(uint16_t x, uint16_t y);

int (draw_ball)(uint16_t x, uint16_t y);

int (draw_clock)(uint8_t minutes, uint8_t seconds, uint16_t xi, uint16_t yi);

int (draw_number)(size_t n, uint16_t x, uint16_t y, bool clock);

int (draw_hearts)(size_t n, uint8_t number_of_lives, uint16_t xi, uint16_t yi);

void (game_over_display)(uint16_t xi, uint16_t yi);

bool (draw_game_over_label)(uint16_t x, uint16_t y);

void (game_win_display)(uint16_t xi, uint16_t yi, struct Player player);

bool (draw_game_win_label)(uint16_t x, uint16_t y);

bool (draw_score_label)(uint16_t x, uint16_t y);

bool (draw_score_value)(uint16_t x, uint16_t y, unsigned int score);

#endif /* __GAME_H */
