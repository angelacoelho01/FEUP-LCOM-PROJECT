#ifndef __GAME_H
#define __GAME_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "../macros/menus_macros.h"
#include "../macros/block_breaker.h"
#include "../macros/i8042.h"

#include "../keyboard/keyboard.h"
#include "../mouse/mouse.h"
#include "../timer/timer.h"
#include "../video/video.h"
#include "../../utils/utils.h"
#include "../graphics/graphics.h"
#include "../game/player/player.h"
// #include "../cursor/graphics_cursor.h"

#include "collision/collision.h"

static uint16_t plataform_width[] = {
  86, 74, 62, 50, 38
};

struct Block{
  uint16_t xi;
  uint16_t xf;
};

static struct Block blocks_coord[100];

int (play_solo_game)(uint16_t mode);

void (start_clock)(uint16_t xi, uint16_t yi);

void (next_life)(uint16_t* ball_x, uint16_t* ball_y, bool* up, bool* left, uint16_t xi, uint16_t yi);

bool (move_plataform)(uint16_t right_limit, uint16_t left_limit);

bool (move_plataform_mouse)(uint16_t right_limit, uint16_t left_limit, int16_t displacement);

void (move_ball)(uint16_t* x, uint16_t* y, bool* up, bool* left, uint16_t scenario_xi, uint16_t scenario_yi);

void (block_break)();

#endif /* __GAME_H */
