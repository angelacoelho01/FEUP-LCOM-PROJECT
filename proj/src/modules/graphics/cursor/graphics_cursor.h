#ifndef _GRAPHICS_CURSOR_H
#define _GRAPHICS_CURSOR_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../video/xpm.h"
#include "../../macros/menus_macros.h"

struct Mouse_cursor {
  unsigned int x;
  unsigned int y;
  xpm_map_t normal_xpm;
  xpm_map_t on_over_xpm;
};

// struct that caracterize a button in a menu
typedef struct Button_details {
  xpm_map_t button;
  xpm_map_t button_over;
  uint16_t x;
  uint16_t y;
} button_details; 

// all the descriptions if the buttons that constitute the main menu 
static button_details main_menu[] = {
  // solo button in the main menu
  {button_solo, button_solo_over, MAIN_SOLO_BUTTON_TO_X, MAIN_SOLO_BUTTON_TO_Y}, 
  // 1v1 button in the main menu
  {button_1v1, button_1v1_over, MAIN_1V1_BUTTON_TO_X, MAIN_1V1_BUTTON_TO_Y}, 
  // leaderboard button in the main menu
  {button_leaderboard, button_leaderboard_over, MAIN_LEADERBOARD_BUTTON_TO_X, MAIN_LEADERBOARD_BUTTON_TO_Y}, 
  // exit button in the main menu
  {button_exit, button_exit_over, MAIN_EXIT_BUTTON_TO_X, MAIN_EXIT_BUTTON_TO_Y}
};

static struct Mouse_cursor cursor = { CURSOR_INICIAL_X, CURSOR_INICIAL_Y, cursor_normal, cursor_pointer };

int (draw_cursor)(xpm_map_t xpm);

bool (change_cursor_position)(struct packet *p);

void (check_options_on_over)();

#endif
