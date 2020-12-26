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

int (draw_solo_button)(uint16_t x, uint16_t y, bool over){
  //Solo button
  if(over){
    if(video_load_xpm(menu_buttons_over[BUTTON_SOLO_OVER]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if(video_load_xpm(menu_buttons[BUTTON_SOLO]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  video_draw_pixmap(x, y);
  return 0;
}

int (draw_1v1_button)(uint16_t x, uint16_t y, bool over){
  //1v1 button
  if(over){
    if(video_load_xpm(menu_buttons_over[BUTTON_1V1_OVER]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if(video_load_xpm(menu_buttons[BUTTON_1V1]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  video_draw_pixmap(x, y);
  return 0;

}

int (draw_leaderboard_button)(uint16_t x, uint16_t y, bool over){
  //Leaderboard button
  if(over){
    if(video_load_xpm(menu_buttons_over[BUTTON_LEADERBOARD_OVER]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if(video_load_xpm(menu_buttons[BUTTON_LEADERBOARD]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  video_draw_pixmap(x, y);
  return 0;
}

int (draw_exit_button)(uint16_t x, uint16_t y, bool over){
  //Exit button
  if(over){
    if(video_load_xpm(menu_buttons_over[BUTTON_EXIT_OVER]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if(video_load_xpm(menu_buttons[BUTTON_EXIT]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  video_draw_pixmap(x, y);
  return 0;
}

int (draw_continue_button)(uint16_t x, uint16_t y, bool over){
  //Continue button
  if(over){
    if(video_load_xpm(menu_buttons_over[BUTTON_CONTINUE_OVER]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if(video_load_xpm(menu_buttons[BUTTON_CONTINUE]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  video_draw_pixmap(x, y);
  return 0;
}

int (draw_reset_button)(uint16_t x, uint16_t y, bool over){
  //Reset button
  if(over){
    if(video_load_xpm(menu_buttons_over[BUTTON_RESET_OVER]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if(video_load_xpm(menu_buttons[BUTTON_RESET]) != OK){
      printf("Error draw_plataform: vg_load_xpm!\n");
      return 1;
    }
  }
  video_draw_pixmap(x, y);
  return 0;
}

int (draw_start_menu)(){ 
  //Draw borders
  draw_menu_borders(0, 0, h_res, v_res);

  //Draw background
  draw_menu_background(MENU_BORDER_SIZE, MENU_BORDER_SIZE, h_res, v_res);

  //Draw game title
  if(draw_game_title(TITLE_TO_X, TITLE_TO_Y) != OK) return 1;

  //Draw solo button
  if(draw_solo_button(MAIN_SOLO_BUTTON_TO_X, MAIN_SOLO_BUTTON_TO_Y, false) != OK) return 1;

  //Draw 1v1 button
  if(draw_1v1_button(MAIN_1V1_BUTTON_TO_X, MAIN_1V1_BUTTON_TO_Y, false) != OK) return 1;

  //Draw leaderboard button
  if(draw_leaderboard_button(MAIN_LEADERBOARD_BUTTON_TO_X, MAIN_LEADERBOARD_BUTTON_TO_Y, false) != OK) return 1;

  //Draw exit button
  if(draw_exit_button(MAIN_EXIT_BUTTON_TO_X, MAIN_EXIT_BUTTON_TO_Y, false) != OK) return 1;

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

  //Draw continue button
  if(draw_continue_button(MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X, MENU_PAUSE_CORNER_Y + PAUSE_CONTINUE_BUTTON_TO_Y, false) != OK) 
    return 1;

  //Draw reset button
  if(draw_reset_button(MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X,
                      MENU_PAUSE_CORNER_Y + PAUSE_RESET_BUTTON_TO_Y, false) != OK)
    return 1;

  //Draw exit button
  if(draw_exit_button(MENU_PAUSE_CORNER_X + PAUSE_BUTTONS_TO_X,
                      MENU_PAUSE_CORNER_Y + PAUSE_EXIT_BUTTON_TO_Y, false) != OK)
    return 1;

  return 0;
}
