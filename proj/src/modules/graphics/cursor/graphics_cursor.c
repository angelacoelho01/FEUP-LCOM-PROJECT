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

int (draw_menu_button)(button_details b, bool over) {
  if (over){
    if (video_load_xpm(b.button_over) != OK){
      printf("Error draw_menu_button (over): vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if (video_load_xpm(b.button) != OK){
      printf("Error draw_menu_button: vg_load_xpm!\n");
      return 1;
    }
  }

  video_draw_pixmap(b.x, b.y);
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
void (check_options_on_over)(button_details *options_menu, int n, bool *on_over) {
  // clear previous region
  // --?
  // nao vai apagar nada do que desenhou antes

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
    draw_cursor(cursor.normal_xpm);
    for (int i = 0; i < n; i++) {
      draw_menu_button(options_menu[i], false);
    }
  }

  if (now_over != -1) {
    draw_cursor(cursor.on_over_xpm);
    draw_menu_button(options_menu[now_over], true);
  }
}
