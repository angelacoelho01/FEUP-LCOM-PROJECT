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
        xpm_image_t block_xpm = blocks_xpms[rand() % NO_BLOCKS];
        video_draw_pixmap(x, y, block_xpm);
        get_all_blocks_positions(x,y, block_xpm);
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
      video_draw_pixmap(pos[i].upper_left_corner.x, pos[i].upper_left_corner.y, pos[i].xpm_image);
    }
  }
  return 0;
}
