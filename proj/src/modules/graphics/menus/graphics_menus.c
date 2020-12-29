#include "graphics_menus.h"

#include "../../video/video.h"

#include "../../../xpm/labels.h"

extern unsigned h_res, v_res;

void (draw_menu_borders)(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
  video_draw_rectangle(x, y, width, height, MENUS_BORDERS);  
}

void (draw_menu_background)(uint16_t x, uint16_t y, uint16_t width, uint16_t height){
  video_draw_rectangle(x, y, width - 2*MENU_BORDER_SIZE, height - 2*MENU_BORDER_SIZE, MENUS_BACKGROUND_COLOR);  
}

void (draw_game_title)(uint16_t x, uint16_t y){
  for(unsigned i = 0; i < NO_START_MENU_TITLES; i++){
    video_draw_pixmap(x, y, start_menu_titles_xpms[i]);
    x += TITLE_WIDTH/NO_START_MENU_TITLES;
  }
}

void (draw_pause_title)(uint16_t x, uint16_t y){
  for(unsigned i = 0; i < NO_PAUSE_MENU_TITLES ; i++){
    video_draw_pixmap(x, y, pause_menu_titles_xpms[i]);
    x += PAUSE_TITLE_WIDTH/NO_PAUSE_MENU_TITLES;
  }
}

void (draw_solo_button)(uint16_t x, uint16_t y, bool over){
  if(over) video_draw_pixmap(x, y, menu_buttons_over_xpms[BUTTON_SOLO]);
  else video_draw_pixmap(x, y, menu_buttons_xpms[BUTTON_SOLO]);
}

void (draw_1v1_button)(uint16_t x, uint16_t y, bool over){
  if(over) video_draw_pixmap(x, y, menu_buttons_over_xpms[BUTTON_1V1]);
  else video_draw_pixmap(x, y, menu_buttons_xpms[BUTTON_1V1]);
}

void (draw_leaderboard_button)(uint16_t x, uint16_t y, bool over){
  if(over) video_draw_pixmap(x, y, menu_buttons_over_xpms[BUTTON_LEADERBOARD]);
  else video_draw_pixmap(x, y, menu_buttons_xpms[BUTTON_LEADERBOARD]);
}

void (draw_exit_button)(uint16_t x, uint16_t y, bool over){
  if(over) video_draw_pixmap(x, y, menu_buttons_over_xpms[BUTTON_EXIT]);
  else video_draw_pixmap(x, y, menu_buttons_xpms[BUTTON_EXIT]);
}

void (draw_continue_button)(uint16_t x, uint16_t y, bool over){
  if(over) video_draw_pixmap(x, y, menu_buttons_over_xpms[BUTTON_CONTINUE]);
  else video_draw_pixmap(x, y, menu_buttons_xpms[BUTTON_CONTINUE]);
}

void (draw_reset_button)(uint16_t x, uint16_t y, bool over){
  if(over) video_draw_pixmap(x, y, menu_buttons_over_xpms[BUTTON_RESET]);
  else video_draw_pixmap(x, y, menu_buttons_xpms[BUTTON_RESET]);
}

void (draw_start_menu)(){ 
  //Draw borders
  draw_menu_borders(0, 0, h_res, v_res);

  //Draw background
  draw_menu_background(MENU_BORDER_SIZE, MENU_BORDER_SIZE, h_res, v_res);

  //Draw game title
  draw_game_title(TITLE_TO_X, TITLE_TO_Y);

  //Draw solo button
  draw_solo_button(MAIN_SOLO_BUTTON_TO_X, MAIN_SOLO_BUTTON_TO_Y, false);

  //Draw 1v1 button
  draw_1v1_button(MAIN_1V1_BUTTON_TO_X, MAIN_1V1_BUTTON_TO_Y, false);

  //Draw leaderboard button
  draw_leaderboard_button(MAIN_LEADERBOARD_BUTTON_TO_X, MAIN_LEADERBOARD_BUTTON_TO_Y, false);

  //Draw exit button
  draw_exit_button(MAIN_EXIT_BUTTON_TO_X, MAIN_EXIT_BUTTON_TO_Y, false);

}

void (draw_pause_menu)(){
  //Draw borders
  draw_menu_borders(MENU_PAUSE_CORNER_X-MENU_BORDER_SIZE, MENU_PAUSE_CORNER_Y-MENU_BORDER_SIZE, MENU_PAUSE_WIDTH, MENU_PAUSE_HEIGHT);

  //Draw background
  draw_menu_background(MENU_PAUSE_CORNER_X, MENU_PAUSE_CORNER_Y, MENU_PAUSE_WIDTH, MENU_PAUSE_HEIGHT);

  //Draw pause title
  draw_pause_title(MENU_PAUSE_CORNER_X + PAUSE_TITLE_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_TITLE_TO_Y);

  //Draw continue button
  draw_continue_button(MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_CONTINUE_BUTTON_TO_Y, false);

  //Draw reset button
  draw_reset_button(MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_RESET_BUTTON_TO_Y, false);

  //Draw exit button
  draw_exit_button(MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_EXIT_BUTTON_TO_Y, false);
}

void (reset_screen)(){
  //Draw borders
  draw_menu_borders(0, 0, h_res, v_res);

  //Draw background
  draw_menu_background(MENU_BORDER_SIZE, MENU_BORDER_SIZE, h_res, v_res);
}
