#include "graphics_numbers.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

int (draw_number)(size_t n, uint16_t x, uint16_t y, bool clock){
  if(clock){
    if (video_load_xpm(numbers[n]) != OK){
      printf("Error draw_number: vg_load_xpm!\n");
      return 1;
    }
  }
  else{
    if (video_load_xpm(numbers_blue[n]) != OK){
      printf("Error draw_number: vg_load_xpm!\n");
      return 1;
    }
  }

  video_draw_pixmap(x, y);

  return 0;
}



