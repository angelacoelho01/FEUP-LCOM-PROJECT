#include "graphics_cursor.h"

#include "../../video/video.h"

extern unsigned h_res, v_res;


void (cursor_initializer)(){
  struct Mouse_cursor temp = { CURSOR_INICIAL_X, CURSOR_INICIAL_Y, mouse_cursor_normal_xpm, mouse_cursor_pointer_xpm };
  cursor = temp;
}

void (draw_cursor)(xpm_image_t xpm_image){
  video_draw_pixmap(cursor.x, cursor.y, xpm_image);
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
enum menu_ev_t (check_options_on_over)(button_details *options_menu, int n, bool *on_over) {
  // clear previous region
  // --?
  // nao vai apagar nada do que desenhou antes

  enum menu_ev_t event;  

  int now_over = -1;
  for (int i = 0; i < n; i++) {
    // cursor over an button
    if ((cursor.x >= options_menu[i].x) && (cursor.x <= options_menu[i].x + BUTTONS_BUTTON_WIDTH) && (cursor.y >= options_menu[i].y) && (cursor.y <= options_menu[i].y + BUTTONS_BUTTON_HEIGHT)) {
      now_over = i;
      break;
    }
  }

  if (now_over == -1 && *on_over == true) {
    // nothing more on over now - return to normal xpms

    for (int i = 0; i < n; i++) {
      draw_menu_button(options_menu[i], false);
    }
    event = NO_OPT;
    *on_over = false;
  }

  if (now_over != -1) {
    draw_menu_button(options_menu[now_over], true);
    draw_cursor(cursor.on_over_xpm);
    event = options_menu[now_over].option;
    *on_over = true;
  } else {
    draw_cursor(cursor.normal_xpm);
  }

  return event;
}
