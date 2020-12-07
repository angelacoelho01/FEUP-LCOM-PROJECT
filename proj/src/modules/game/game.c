#include "game.h"

#include <time.h>
#include <stdlib.h>

extern vbe_mode_info_t mode_conf;
// extern xpm_row_t const plataform[];
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;
// typedef xpm_row_t *const 	xpm_map_t 

static xpm_map_t blocks[] = {
  blue_block_xpm,
  green_block_xpm,
  orange_block_xpm,
  yellow_block_xpm,
  red_block_xpm,
  purple_block_xpm,
  pink_block_xpm
};

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
  //uint16_t m = 0x105;
  

  // printf(" AQUI ");
  // passada aqui a plataform pois aquela a desenhar vai variar consoante o tempo 
  // com o passar do tempo vamos desenhar uma plataform mais pequena
  // os diferentes tamanhos correspondem a xpms da plataform com diferentes width
  if (draw_plataform(mode, minix3_xpm, 0, 0) != OK){
    printf("Error draw_scenario: draw_plataform!");
    vg_exit();
    return 1;
  }

  //vg_draw_rectangle(10, 10, 40, 50, 0xB82A0B);
  
  sleep(5);
  
  // printf(" AQUI2 ");

  return 0;
}

int (return_to_text_mode)(){
  if(vg_exit() != OK){
    printf("Error returning to text mode.\n");
    return 1;
  }
  return 0;
}


// the plataform is a xpm (there are plataform with different widht - chosen accordly to the time that has already passed)
int (draw_plataform)(uint16_t mode, xpm_map_t xpm, uint16_t x, uint16_t y){
  // NOTA: o enum nao esta por ordem é mais facil associar o nome do numero do que o numero
  // considerando apenas modes não gray
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


void (draw_blocks)(){
  /*unsigned int width = mode_conf.XResolution/no_blocks;
  unsigned int height = mode_conf.YResolution/(1.5*no_blocks);*/
  uint16_t x = 240, y = 60;
  unsigned int width = 40, height = 20;
  uint32_t no_blocks_h = (320-10)/width, no_blocks_v = (480-80)/height;

  for(uint16_t i = 0; i  < no_blocks_v; i++){
    for(uint16_t j = 0; j < no_blocks_h; j++){
      xpm_row_t* xpm = blocks[rand() % BLOCK_NUMBERS];
      //Gets the color throught the given functions and according to the color mode
      //Draws a rectangle; in case it doesn't work, returns to text mode
      vg_load_xpm(xpm);
      vg_draw_pixmap(x, y);

      //Goes to the next column according to the calculated width
      x += width;
    }
    //Resets the column to start a new line
    x = 240;
    //Goes to the next line according to the calculated height
    y += height; 
  }

  sleep(10);

}
