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


#include "plataform/garphics_plataform.h"
#include "numbers/graphics_numbers.h"
#include "labels/graphics_labels.h"
#include "hearts/graphics_hearts.h"
#include "clock/graphics_clock.h"
#include "ball/graphics_ball.h"
#include "blocks/graphics_blocks.h"

#include "../keyboard/keyboard.h"
#include "../video/video.h"
#include "../../utils/utils.h"
#include "../../xpm/labels.h"
#include "../game/player/player.h"

int (draw_scenario)(uint16_t xi, uint16_t yi);

void (game_over_display)(uint16_t xi, uint16_t yi);

void (game_win_display)(uint16_t xi, uint16_t yi, struct Player player);

bool (draw_score_value)(uint16_t x, uint16_t y, unsigned int score);

#endif /* __GAME_H */
