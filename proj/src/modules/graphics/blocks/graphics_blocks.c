#include "graphics_blocks.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"
#include "../../game/collision/collision.h"

extern bool game_started;

int (draw_blocks)(uint16_t xi, uint16_t yi){
  uint16_t x = xi, y = yi;
  // unsigned int width = 40, height = 20;
  // uint32_t no_blocks_h = (320-10)/width, no_blocks_v = (480-80)/height;

  if(!game_started){
    for(uint16_t i = 0; i  < NUMBER_BLOCKS_Y; i++){
      for(uint16_t j = 0; j < NUMBER_BLOCKS_X; j++){
        // Draw a block of a random color
        xpm_row_t* xpm = blocks[rand() % NUMBER_BLOCKS_COLORS];
        if (video_load_xpm(xpm) != OK){
          printf("Error draw_blocks: vg_load_xpm!\n");
          return 1;
        }
        video_draw_pixmap(x, y);
        get_all_blocks_positions(x,y, xpm);
        x += BLOCKS_WIDTH;
      }
      // Next Line
      x = xi;
      y += BLOCKS_HEIGHT; 
    }
  }
  else{
    size_t size = get_list_size();
    for(unsigned int i = 0; i < size; i++){
      struct block_position* pos = get_list_blocks_positions();
      if (video_load_xpm(pos[i].xpm) != OK){
        printf("Error draw_blocks: vg_load_xpm!\n");
        return 1;
      }
      video_draw_pixmap(pos[i].upper_left_corner.x, pos[i].upper_left_corner.y);
    }
  }
  return 0;
}
