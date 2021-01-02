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

int (draw_game_title)(uint16_t x, uint16_t y){
  for(unsigned i = 0; i < 4; i++){
    if(video_load_xpm(start_menu_titles[i]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
    
    video_draw_pixmap(x, y);
    x += TITLE_WIDTH/4;
  }
  return 0;
}

int (draw_pause_title)(uint16_t x, uint16_t y){

  for(unsigned i = 0; i < 2; i++){
    if(video_load_xpm(pause_menu_titles[i]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
    video_draw_pixmap(x, y);
    x += PAUSE_TITLE_WIDTH/2;
  }
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

int (draw_start_menu)(){ 
  //Draw borders
  draw_menu_borders(0, 0, h_res, v_res);

  //Draw background
  draw_menu_background(MENU_BORDER_SIZE, MENU_BORDER_SIZE, h_res, v_res);

  //Draw game title
  if(draw_game_title(TITLE_TO_X, TITLE_TO_Y) != OK) return 1;

  //Draw main menu buttons - solo, 1v1, leaderboard, exit
  for (int i = 0; i < 4; i++) {
    if (draw_menu_button(main_menu[i], false) != OK) return 1;
  }

  return 0;
}

int (draw_pause_menu)(){
  //Draw borders
  draw_menu_borders(MENU_PAUSE_CORNER_X-MENU_BORDER_SIZE, MENU_PAUSE_CORNER_Y-MENU_BORDER_SIZE, MENU_PAUSE_WIDTH, MENU_PAUSE_HEIGHT);

  //Draw background
  draw_menu_background(MENU_PAUSE_CORNER_X, MENU_PAUSE_CORNER_Y, MENU_PAUSE_WIDTH, MENU_PAUSE_HEIGHT);

  //Draw pause title
  if(draw_pause_title(MENU_PAUSE_CORNER_X + PAUSE_TITLE_TO_X, 
                      MENU_PAUSE_CORNER_Y + PAUSE_TITLE_TO_Y ) != OK) 
    return 1;

  //Draw pause menu buttons - continue, reset, exit
  for (int i = 0; i < 3; i++) {
    if (draw_menu_button(pause_menu[i], false) != OK) return 1;
  }

  return 0;
}

// implement navigate between menus

// the initial event 
struct menu_ev menu_evt = {NO_OPT};

// detect a selection - click over an option
struct menu_ev* (menu_select_option_detect)(struct mouse_ev *mouse_evt, enum menu_ev_t event) {
  if (mouse_evt->type == LB_PRESSED) { // to select a option
    menu_evt.type = event;
  }
	
	return (&menu_evt);
}

// the state machine
typedef enum {MAIN_MENU, GAME_SOLO, GAME_SOLO_CONTINUE, GAME_1V1, GAME_1V1_CONTINUE, PAUSE_SOLO_MENU, PAUSE_1V1_MENU, LEADERBOARD, EXIT_GAME} state_menus_t;
// provavelmente vai ser necessario alguma variavel booleana global que indica se é para fazer reset ao mode em jogo ou não

bool (navigate_between_menus)(struct menu_ev *evt) {
  bool end = false;
  static state_menus_t menus_st = MAIN_MENU; // initial state; keep state
  
  switch (menus_st) {
    case MAIN_MENU:
      if(evt->type == OPT_SOLO) 
        menus_st = GAME_SOLO;
      if(evt->type == OPT_1V1) 
        menus_st = GAME_1V1;
      if(evt->type == OPT_LEADERBOARD) 
        menus_st = LEADERBOARD;
      if(evt->type == OPT_EXIT) {
        menus_st = EXIT_GAME;
        end = true;
      }
      break;
    case GAME_SOLO: case GAME_SOLO_CONTINUE:
      if(evt->type == OPT_PAUSE) 
        menus_st = PAUSE_SOLO_MENU;
      break;
    case GAME_1V1: case GAME_1V1_CONTINUE:
      if(evt->type == OPT_PAUSE) 
        menus_st = PAUSE_1V1_MENU;
      break;
    case PAUSE_SOLO_MENU:
      if(evt->type == OPT_EXIT) 
        menus_st = MAIN_MENU;
      if(evt->type == OPT_RESET) 
        menus_st = GAME_SOLO;
      if(evt->type == OPT_CONTINUE) 
        menus_st = GAME_SOLO_CONTINUE;
      break;
    case PAUSE_1V1_MENU:
      if(evt->type == OPT_EXIT) 
        menus_st = MAIN_MENU;
      if(evt->type == OPT_RESET) 
        menus_st = GAME_1V1;
      if(evt->type == OPT_CONTINUE) 
        menus_st = GAME_1V1_CONTINUE;
      break;
    case LEADERBOARD:
      if(evt->type == OPT_BACK) 
        menus_st = MAIN_MENU;
      if(evt->type == OPT_EXIT) {
        menus_st = EXIT_GAME;
        end = true;
      }
      break;
    default:
      break;
  }

  return (end);
}
