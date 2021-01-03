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

#include "collision/collision.h"

#include "../graphics/ball/graphics_ball.h"
#include "../graphics/blocks/graphics_blocks.h"
#include "../graphics/clock/graphics_clock.h"
#include "../graphics/hearts/graphics_hearts.h"
#include "../graphics/labels/graphics_labels.h"
#include "../graphics/menus/graphics_menus.h"
#include "../graphics/cursor/graphics_cursor.h"
#include "../graphics/numbers/graphics_numbers.h"
#include "../graphics/plataform/graphics_plataform.h"

#include "../../xpm/load_xpms.h"

static uint16_t plataform_width[] = {
  86, 74, 62, 50, 38
};

struct Block{
  uint16_t xi;
  uint16_t xf;
};

static struct Block blocks_coord[100];

int (game_start)(uint16_t mode);

void (game_solo_inicializer)(uint16_t *scenario_limit_left, uint16_t *scenario_limit_right, uint16_t *ball_x, uint16_t *ball_y, bool *up, bool *left);

void (play_solo_game_kbc)(uint16_t scenario_limit_right, uint16_t scenario_limit_left);

void (play_solo_game_mouse)(struct mouse_ev* mouse_evt, uint16_t scenario_limit_right, uint16_t scenario_limit_left, struct packet mouse_pp);

void (play_solo_game_timer)(uint16_t ball_x, uint16_t ball_y, bool up, bool left, struct Player p1, bool *flag_first);

void (start_clock)(uint16_t xi, uint16_t yi);

void (next_life)(uint16_t* ball_x, uint16_t* ball_y, bool* up, bool* left, uint16_t xi, uint16_t yi);

bool (move_plataform)(uint16_t right_limit, uint16_t left_limit);

bool (move_plataform_mouse)(uint16_t right_limit, uint16_t left_limit, int16_t displacement);

void (move_ball)(uint16_t* x, uint16_t* y, bool* up, bool* left, uint16_t scenario_xi, uint16_t scenario_yi);

void (block_break)();

#endif /* __GAME_H */
