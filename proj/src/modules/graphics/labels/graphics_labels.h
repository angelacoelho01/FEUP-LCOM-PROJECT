#ifndef _GRAPHICS_LABELS_H
#define _GRAPHICS_LABELS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../../xpm/load_xpms.h"

enum labels_t{
  GAME_OVER_LABEL,
  WINNER_LABEL,
  SCORE_LABEL
};

void (draw_game_over_label)(uint16_t x, uint16_t y);

void (draw_game_win_label)(uint16_t x, uint16_t y);

void (draw_score_label)(uint16_t x, uint16_t y);

#endif
