#ifndef _GRAPHICS_MENUS_H
#define _GRAPHICS_MENUS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../../xpm/load_xpms.h"
#include "../../macros/menus_macros.h"

// ---

// the possible events
enum menu_ev_t {
  OPT_SOLO, OPT_1V1, OPT_LEADERBOARD, OPT_EXIT, OPT_CONTINUE, OPT_RESET, OPT_BACK, OPT_PAUSE, NO_OPT
};

struct menu_ev {
  enum menu_ev_t type;
};

// ---

enum titles{
  GAME_TITLE,
  PAUSE_TITLE
};

enum Button{
  BUTTON_1V1,
  BUTTON_LEADERBOARD,
  BUTTON_SOLO,
  BUTTON_EXIT,
  BUTTON_CONTINUE,
  BUTTON_RESET,
  BUTTON_BACK
};


// struct that caracterize a button in a menu
typedef struct Button_details {
  xpm_image_t button;
  xpm_image_t button_over;
  uint16_t x;
  uint16_t y;
  enum menu_ev_t option;
} button_details; 

// all the descriptions of the buttons that constitute the main menu 
button_details main_menu[4];

// all the descriptions of the buttons that constitute the pause menu 
button_details pause_menu[3];

// all the descriptions of the buttons that constitute the leaderboard menu 
button_details leaderboard_menu[2];

void (menu_initializer)();

void (draw_menu_borders)(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void (draw_menu_background)(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void (draw_game_title)(uint16_t x, uint16_t y);

void (draw_pause_title)(uint16_t x, uint16_t y);

void (draw_menu_button)(button_details b, bool over);

void (draw_start_menu)();

void (draw_pause_menu)();

// implement navigate between menus


// the state machine
typedef enum {MAIN_MENU, GAME_SOLO, GAME_SOLO_CONTINUE, GAME_1V1, GAME_1V1_CONTINUE, PAUSE_SOLO_MENU, PAUSE_1V1_MENU, LEADERBOARD, EXIT_GAME} state_menus_t;

static state_menus_t menus_st = MAIN_MENU; // initial state; keep state

struct menu_ev* (menu_select_option_detect)(struct mouse_ev *mouse_evt, enum menu_ev_t event);

bool (navigate_between_menus)(struct menu_ev *evt);

#endif
