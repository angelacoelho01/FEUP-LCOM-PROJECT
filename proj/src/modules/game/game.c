#include "game.h"

extern vbe_mode_info_t mode_conf;
// extern xpm_row_t const plataform[];
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;
// typedef xpm_row_t *const 	xpm_map_t 

int (draw_scenario)(uint16_t mode){
  //uint16_t m = 0x105;
  if (video_get_mode_info(mode, &mode_conf) != OK){
    printf("Error draw_scenario: video_get_mode_info!");
    return 1;
  }

  if (map_memory() != OK){
    printf("Error draw_scenario: map_memory!");
    return 1;
  }

  if (video_set_graphic_mode(mode) != OK){
    printf("Error draw_scenario: video_set_graphic_mode!");
    vg_exit();
    return 1;
  }

  // printf(" AQUI ");
  
  if (draw_plataform(mode, minix3_xpm, 10, 10) != OK){
    printf("Error draw_scenario: draw_plataform!");
    vg_exit();
    return 1;
  }

  vg_draw_rectangle(10, 10, 40, 50, 0xB82A0B);
  
  sleep(5);
  
  // printf(" AQUI2 ");
  vg_exit();

  return 0;
}

// the plataform is a xpm (there are plataform with different widht - chosen accordly to the time that has already passed)
int (draw_plataform)(uint16_t mode, xpm_map_t xpm, uint16_t x, uint16_t y){
  if (0x105 == mode) xpm_type = XPM_INDEXED;
  else if (0x110 == mode) xpm_type = XPM_1_5_5_5;
  else if (0x115 == mode) xpm_type = XPM_8_8_8;
  else if (0x11A == mode) xpm_type = XPM_5_6_5;
  else if (0x14C == mode) xpm_type = XPM_8_8_8_8;
  else xpm_type = INVALID_XPM;

  // download of the corresponding xpm to draw
  if(vg_load_xpm(xpm) != OK){
    printf("Error draw_plataform: vg_load_xpm!");
    vg_exit();
    return 1;
  }

  // display on the screen the xpm of the plataform
  if(vg_draw_pixmap(x, y) != OK){
    printf("Error draw_plataform: vg_draw_pixmap!");
    vg_exit();
    return 1;
  }

  return 0;
}
