#include "graphics_menus.h"

#include "../../video/video.h"

extern unsigned h_res, v_res;

void (draw_menu_borders)(){
  video_draw_rectangle(0, 0, h_res, v_res, MENUS_BORDERS);  
}

void (draw_menu_background)(){
  video_draw_rectangle(MENU_BORDER_SIZE, MENU_BORDER_SIZE, h_res - 2*MENU_BORDER_SIZE, v_res - 2*MENU_BORDER_SIZE, MENUS_BACKGROUND_COLOR);  
}

int (draw_game_title)(uint16_t x, uint16_t y){
  if(video_load_xpm(titles[0]) != OK){
    printf("Error draw_plataform: vg_load_xpm!\n");
    return 1;
  }
  video_draw_pixmap(x, y);
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
  draw_menu_borders();

  //Draw background
  draw_menu_background();

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
