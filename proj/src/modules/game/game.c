#include "game.h"

#include <time.h>
#include <stdlib.h>

extern vbe_mode_info_t mode_conf;
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;

int (start_video_mode)(uint16_t mode){
  srand(time(NULL));
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
  return 0;
}

int (draw_scenario)(uint16_t mode){
  if (draw_plataform(mode, plataform_initial, 0, 0) != OK){
    printf("Error draw_scenario: draw_plataform!");
    vg_exit();
    return 1;
  }
  
  sleep(5);
  
  return 0;
}

int (return_to_text_mode)(){
  if(vg_exit() != OK){
    printf("Error returning to text mode.\n");
    return 1;
  }
  return 0;
}

int (draw_plataform)(uint16_t mode, xpm_map_t xpm, uint16_t x, uint16_t y){
  if(video_load_xpm(xpm) != OK){
    printf("Error draw_plataform: vg_load_xpm!");
    vg_exit();
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}


void (draw_blocks)(){
  uint16_t x = 240, y = 60;
  unsigned int width = 40, height = 20;
  uint32_t no_blocks_h = (320-10)/width, no_blocks_v = (480-80)/height;

  for(uint16_t i = 0; i  < no_blocks_v; i++){
    for(uint16_t j = 0; j < no_blocks_h; j++){
      xpm_row_t* xpm = blocks[rand() % BLOCK_NUMBERS];
      video_load_xpm(xpm);
      video_draw_pixmap(x, y);

      x += width;
    }
    x = 240;
    y += height; 
  }

  sleep(10);

}
