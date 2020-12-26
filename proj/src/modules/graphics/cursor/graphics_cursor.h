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

int (draw_cursor)(xpm_map_t xpm);

bool (change_cursor_position)(struct packet *p);

void (check_options_on_over)();

#endif
