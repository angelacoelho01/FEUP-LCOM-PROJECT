#ifndef _GRAPHICS_CURSOR_H
#define _GRAPHICS_CURSOR_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../../xpm/xpm.h"
#include "../../macros/menus_macros.h"
#include "../menus/graphics_menus.h"

struct Mouse_cursor {
  unsigned int x;
  unsigned int y;
  xpm_image_t normal_xpm;
  xpm_image_t on_over_xpm;
};

// struct that caracterize a button in a menu
typedef struct Button_details {
  xpm_image_t button;
  xpm_image_t button_over;
  uint16_t x;
  uint16_t y;
} button_details; 

// all the descriptions if the buttons that constitute the main menu 
static button_details main_menu[4];
static struct Mouse_cursor cursor;

void (cursor_initializer)(); 

void (draw_cursor)(xpm_image_t xpm_image);

bool (change_cursor_position)(struct packet *p);

void (check_options_on_over)();

#endif
