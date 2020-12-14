#ifndef __GAME_H
#define __GAME_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "../macros/block_breaker.h"
#include "../macros/i8042.h"

#include "../keyboard/keyboard.h"
#include "../mouse/mouse.h"
#include "../timer/timer.h"
#include "../video/video.h"
#include "../../utils/utils.h"
#include "../graphics/graphics.h"

static uint16_t plataform_width[] = {
  86, 74, 62, 50, 38
};

struct Block{
  uint16_t xi;
  uint16_t xf;
};

static struct Block blocks_coord[100];

int (play_solo_game)(uint16_t mode);

void (start_game)();

void (reset_game)(uint16_t* ball_x, uint16_t* ball_y, bool* up, bool* left);

bool (move_plataform)();

void (move_ball)(uint16_t* x, uint16_t* y, bool* up, bool* left);

void (block_break)();

#endif /* __GAME_H */
