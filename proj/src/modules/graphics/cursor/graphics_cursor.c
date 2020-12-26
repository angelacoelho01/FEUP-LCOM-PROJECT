#include "graphics_cursor.h"

#include "../../video/video.h"

extern unsigned h_res, v_res;

int (draw_cursor)(xpm_map_t xpm){
  if (video_load_xpm(xpm) != OK){
    printf("Error draw_cursor: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(cursor.x, cursor.y);

  return 0;
}

bool (change_cursor_position)(struct packet *p) {
  bool to_change = false;

  if (!p->x_ov && p->delta_x != 0) {
    to_change = true;
		if ((int)cursor.x + p->delta_x < 0)
			cursor.x = 0; // left limits
		else if (cursor.x + p->delta_x >= h_res - CURSOR_WIDTH) 
			cursor.x = h_res - CURSOR_WIDTH; // right limits
		else
			cursor.x += p->delta_x;
  }

  if (!p->y_ov && p->delta_y != 0) {
    to_change = true;
		if ((int)cursor.y - p->delta_y < 0)
			cursor.y = 0; // left limits
		else if ((int)cursor.y - p->delta_y >= (int)v_res - CURSOR_HEIGHT) 
			cursor.y = v_res - CURSOR_HEIGHT; // right limits
		else
			cursor.y -= p->delta_y;
  }

  return (to_change);
}

// chamada quando o mouse varia de posição para verificar se ficará sobre uma opção do menu em questão
void (check_options_on_over)(/*vai receber um array com as opçoes desse menu, array de structs de buttons_details com coordenadas e xpms respetivas*/) {

  // clear previous region
  // --?
  // nao vai apagar nada do que desenhou antes
  draw_cursor(cursor.normal_xpm);
}
