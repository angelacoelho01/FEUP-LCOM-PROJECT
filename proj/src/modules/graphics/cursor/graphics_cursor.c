#include "graphics_cursor.h"

#include "../../video/video.h"

extern unsigned h_res, v_res;


void (cursor_initializer)(){
  // solo button in the main menu
  button_details temp0 = {menu_buttons_xpms[BUTTON_SOLO], menu_buttons_over_xpms[BUTTON_SOLO], MAIN_SOLO_BUTTON_TO_X, MAIN_SOLO_BUTTON_TO_Y}; 
  main_menu[0] = temp0;

  // 1v1 button in the main menu
  button_details temp1 = {menu_buttons_xpms[BUTTON_1V1], menu_buttons_over_xpms[BUTTON_1V1], MAIN_1V1_BUTTON_TO_X, MAIN_1V1_BUTTON_TO_Y};
  main_menu[1] = temp1;

  // leaderboard button in the main menu
  button_details temp2 = {menu_buttons_xpms[BUTTON_LEADERBOARD], menu_buttons_over_xpms[BUTTON_LEADERBOARD], MAIN_LEADERBOARD_BUTTON_TO_X, MAIN_LEADERBOARD_BUTTON_TO_Y}; 
  main_menu[2] = temp2;

  // exit button in the main menu
  button_details temp3 = {menu_buttons_xpms[BUTTON_EXIT], menu_buttons_over_xpms[BUTTON_EXIT], MAIN_EXIT_BUTTON_TO_X, MAIN_EXIT_BUTTON_TO_Y};
  main_menu[3] = temp3;

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
void (check_options_on_over)(/*vai receber um array com as opçoes desse menu, array de structs de buttons_details com coordenadas e xpms respetivas*/) {

  // clear previous region
  // --?
  // nao vai apagar nada do que desenhou antes
  draw_cursor(cursor.normal_xpm);
}
