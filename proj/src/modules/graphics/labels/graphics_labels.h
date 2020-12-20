#ifndef _GRAPHICS_LABELS_H
#define _GRAPHICS_LABELS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

bool (draw_game_over_label)(uint16_t x, uint16_t y);

bool (draw_game_win_label)(uint16_t x, uint16_t y);

bool (draw_score_label)(uint16_t x, uint16_t y);

#endif
