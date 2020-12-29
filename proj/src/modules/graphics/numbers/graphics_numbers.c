#include "graphics_numbers.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

void (draw_number)(size_t n, uint16_t x, uint16_t y, bool clock){
  if(clock)
    video_draw_pixmap(x, y,numbers_gray_xpms[n]);
  else video_draw_pixmap(x, y, numbers_blue_xpms[n]);
}



