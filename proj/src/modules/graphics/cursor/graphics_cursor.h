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

struct Mouse_cursor cursor;

void (cursor_initializer)();

void (draw_cursor)(xpm_image_t xpm);

bool (change_cursor_position)(struct packet *p);

/**
 * Change the xpm of the button and of the cursor if it is over a option in that menu
 * @param options_menu all the descriptions of the buttons that constitute the menu
 * @param n the number of elements of the array
 * @param on_over represent if a option was selected before this check
 */
enum menu_ev_t (check_options_on_over)(button_details *options_menu, int n, bool *on_over);

#endif
