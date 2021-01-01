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

static struct Mouse_cursor cursor = { CURSOR_INICIAL_X, CURSOR_INICIAL_Y, cursor_normal, cursor_pointer };

// struct that caracterize a button in a menu
typedef struct Button_details {
  xpm_map_t button;
  xpm_map_t button_over;
  uint16_t x;
  uint16_t y;
} button_details; 

// all the descriptions of the buttons that constitute the main menu 
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

// all the descriptions of the buttons that constitute the pause menu 
static button_details pause_menu[] = {
  // continue button in the pause menu 
  {button_continue, button_continue_over, MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_CONTINUE_BUTTON_TO_Y}, 
  // reset button in the pause menu 
  {button_reset, button_reset_over, MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_RESET_BUTTON_TO_Y}, 
  // exit button in the pause menu 
  {button_exit, button_exit_over, MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_EXIT_BUTTON_TO_Y}
};

// all the descriptions of the buttons that constitute the leaderboard menu 
static button_details leaderboard_menu[] = {
  // exit button in the leaderboard menu 
  {button_exit, button_exit_over, LEADER_EXIT_BUTTON_TO_X, LEADER_EXIT_BUTTON_TO_Y}
};

int (draw_cursor)(xpm_map_t xpm);

int (draw_menu_button)(button_details b, bool over);

bool (change_cursor_position)(struct packet *p);

/**
 * Change the xpm of the button and of the cursor if it is over a option in that menu
 * @param options_menu all the descriptions of the buttons that constitute the menu
 * @param n the number of elements of the array
 * @param on_over represent if a option was selected before this check
 */
void (check_options_on_over)(button_details *options_menu, int n, bool *on_over);

#endif
