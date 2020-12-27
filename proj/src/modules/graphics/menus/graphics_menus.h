#ifndef _GRAPHICS_MENUS_H
#define _GRAPHICS_MENUS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../../xpm/load_xpms.h"
#include "../../macros/menus_macros.h"

enum buttons{
  BUTTON_1V1,
  BUTTON_LEADERBOARD,
  BUTTON_SOLO,
  BUTTON_EXIT,
  BUTTON_CONTINUE,
  BUTTON_RESET
};

enum titles{
  GAME_TITLE,
  PAUSE_TITLE
};

void (draw_menu_borders)(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void (draw_menu_background)(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void (draw_game_title)(uint16_t x, uint16_t y);

void (draw_pause_title)(uint16_t x, uint16_t y);

void (draw_solo_button)(uint16_t x, uint16_t y, bool over);

void (draw_1v1_button)(uint16_t x, uint16_t y, bool over);

void (draw_leaderboard_button)(uint16_t x, uint16_t y, bool over);

void (draw_exit_button)(uint16_t x, uint16_t y, bool over);

void (draw_continue_button)(uint16_t x, uint16_t y, bool over);

void (draw_reset_button)(uint16_t x, uint16_t y, bool over);

void (draw_start_menu)();

void (draw_pause_menu)();

void (reset_screen)();

#endif
