#include "garphics_plataform.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

int (draw_plataform)(xpm_map_t xpm, uint16_t x, uint16_t y, uint16_t scenario_x){
  // clear the reagion of the plataform first
  video_draw_rectangle(scenario_x + BORDER_WIDTH, y, SCENARIO_WIDTH - (BORDER_WIDTH*2), PLATAFORM_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  if (video_load_xpm(xpm) != OK){
    printf("Error draw_plataform: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}
