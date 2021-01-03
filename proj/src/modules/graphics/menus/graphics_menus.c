#include "graphics_menus.h"

#include "../../video/video.h"

#include "../../../xpm/labels.h"

extern unsigned h_res, v_res;

void (menu_initializer)(){
  // solo button in the main menu
  button_details temp0 = {menu_buttons_xpms[BUTTON_SOLO], menu_buttons_over_xpms[BUTTON_SOLO], MAIN_SOLO_BUTTON_TO_X, MAIN_SOLO_BUTTON_TO_Y, OPT_SOLO}; 
  main_menu[0] = temp0;

  // 1v1 button in the main menu
  button_details temp1 = {menu_buttons_xpms[BUTTON_1V1], menu_buttons_over_xpms[BUTTON_1V1], MAIN_1V1_BUTTON_TO_X, MAIN_1V1_BUTTON_TO_Y, OPT_1V1};
  main_menu[1] = temp1;

  // leaderboard button in the main menu
  button_details temp2 = {menu_buttons_xpms[BUTTON_LEADERBOARD], menu_buttons_over_xpms[BUTTON_LEADERBOARD], MAIN_LEADERBOARD_BUTTON_TO_X, MAIN_LEADERBOARD_BUTTON_TO_Y, OPT_LEADERBOARD}; 
  main_menu[2] = temp2;

  // exit button in the main menu
  button_details temp3 = {menu_buttons_xpms[BUTTON_EXIT], menu_buttons_over_xpms[BUTTON_EXIT], MAIN_EXIT_BUTTON_TO_X, MAIN_EXIT_BUTTON_TO_Y, OPT_EXIT};
  main_menu[3] = temp3;

    // continue button in the pause menu 
  button_details temp4 ={menu_buttons_xpms[BUTTON_CONTINUE], menu_buttons_over_xpms[BUTTON_CONTINUE], MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_CONTINUE_BUTTON_TO_Y, OPT_CONTINUE};
  pause_menu[0] = temp4;

  // reset button in the pause menu 
  button_details temp5 = {menu_buttons_xpms[BUTTON_RESET], menu_buttons_over_xpms[BUTTON_RESET], MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_RESET_BUTTON_TO_Y, OPT_RESET};
  pause_menu[1] = temp5;

  // exit button in the pause menu 
  button_details temp6 = {menu_buttons_xpms[BUTTON_EXIT], menu_buttons_over_xpms[BUTTON_EXIT], MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_EXIT_BUTTON_TO_Y, OPT_EXIT};
  pause_menu[2] = temp6;

    // back button in the leaderboard menu 
  button_details temp7 = {menu_buttons_xpms[BUTTON_BACK], menu_buttons_over_xpms[BUTTON_BACK], LEADER_BACK_BUTTON_TO_X, LEADER_BACK_BUTTON_TO_Y, OPT_BACK};
  leaderboard_menu[0] = temp7;

  // exit button in the leaderboard menu 
  button_details temp8 = {menu_buttons_xpms[BUTTON_EXIT], menu_buttons_over_xpms[BUTTON_EXIT], LEADER_EXIT_BUTTON_TO_X, LEADER_EXIT_BUTTON_TO_Y, OPT_EXIT};
  leaderboard_menu[1] = temp8;

  //struct Mouse_cursor temp = { CURSOR_INICIAL_X, CURSOR_INICIAL_Y, mouse_cursor_normal_xpm, mouse_cursor_pointer_xpm };
  //cursor = temp;
}

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

void (draw_menu_button)(button_details b, bool over) {
  if(over)
    video_draw_pixmap(b.x, b.y, b.button_over);
  else 
    video_draw_pixmap(b.x, b.y, b.button);
}

void (draw_start_menu)(){ 
  //Draw borders
  draw_menu_borders(0, 0, h_res, v_res);

  //Draw background
  draw_menu_background(MENU_BORDER_SIZE, MENU_BORDER_SIZE, h_res, v_res);

  //Draw game title
  draw_game_title(TITLE_TO_X, TITLE_TO_Y);

  //Draw main menu buttons - solo, 1v1, leaderboard, exit
  for (int i = 0; i < 4; i++) 
    draw_menu_button(main_menu[i], false);
}

void (draw_pause_menu)(){
  //Draw borders
  draw_menu_borders(MENU_PAUSE_CORNER_X-MENU_BORDER_SIZE, MENU_PAUSE_CORNER_Y-MENU_BORDER_SIZE, MENU_PAUSE_WIDTH, MENU_PAUSE_HEIGHT);

  //Draw background
  draw_menu_background(MENU_PAUSE_CORNER_X, MENU_PAUSE_CORNER_Y, MENU_PAUSE_WIDTH, MENU_PAUSE_HEIGHT);

  //Draw pause title
  draw_pause_title(MENU_PAUSE_CORNER_X + PAUSE_TITLE_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_TITLE_TO_Y);

  //Draw pause menu buttons - continue, reset, exit
  for (int i = 0; i < 3; i++) 
    draw_menu_button(pause_menu[i], false);

}

// implement navigate between menus

// detect a selection - click over an option

bool (menu_select_option_detect)(struct mouse_ev *mouse_evt) {
  if (mouse_evt->type == LB_PRESSED) { // to select a option
    return true;
  }
	
	return false;
}

state_menus_t (navigate_between_menus)(enum menu_ev_t type) {
 
  switch (menus_st) {
    case MAIN_MENU:
      if(type == OPT_SOLO) 
        menus_st = GAME_SOLO;
      if(type == OPT_1V1) 
        menus_st = GAME_1V1;
      if(type == OPT_LEADERBOARD) 
        menus_st = LEADERBOARD;
      if(type == OPT_EXIT) {
        menus_st = EXIT_GAME;
      }
      break;
    case GAME_SOLO: case GAME_SOLO_CONTINUE:
      if(type == OPT_PAUSE) 
        menus_st = PAUSE_SOLO_MENU;
      if(type == OPT_EXIT) 
        menus_st = MAIN_MENU;
      break;
    case GAME_1V1: case GAME_1V1_CONTINUE:
      if(type == OPT_PAUSE) 
        menus_st = PAUSE_1V1_MENU;
      if(type == OPT_EXIT) 
        menus_st = MAIN_MENU;
      break;
    case PAUSE_SOLO_MENU:
      if(type == OPT_EXIT) 
        menus_st = MAIN_MENU;
      if(type == OPT_RESET) 
        menus_st = GAME_SOLO;
      if(type == OPT_CONTINUE) 
        menus_st = GAME_SOLO_CONTINUE;
      break;
    case PAUSE_1V1_MENU:
      if(type == OPT_EXIT) 
        menus_st = MAIN_MENU;
      if(type == OPT_RESET) 
        menus_st = GAME_1V1;
      if(type == OPT_CONTINUE) 
        menus_st = GAME_1V1_CONTINUE;
      break;
    case LEADERBOARD:
      if(type == OPT_BACK) 
        menus_st = MAIN_MENU;
      if(type == OPT_EXIT) {
        menus_st = EXIT_GAME;
      }
      break;
    default:
      break;
  }

  return (menus_st);
}
