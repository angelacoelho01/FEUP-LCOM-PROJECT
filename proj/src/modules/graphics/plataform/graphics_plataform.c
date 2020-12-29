#include "graphics_plataform.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

void (draw_plataform)(uint16_t x, uint16_t y, uint16_t scenario_x, xpm_image_t plataform_xpm){
  // clear the reagion of the plataform first
  video_draw_rectangle(scenario_x + BORDER_WIDTH, y, SCENARIO_WIDTH - (BORDER_WIDTH*2), PLATAFORM_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  video_draw_pixmap(x, y, plataform_xpm);
}
