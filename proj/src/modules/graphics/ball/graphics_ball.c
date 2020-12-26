#include "graphics_ball.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

void (clean_ball)(uint16_t x, uint16_t y){
  video_draw_rectangle(x, y, BALL_WIDTH, BALL_HEIGHT, SCENARIO_BACKGROUND_COLOR);
}

int (draw_ball)(uint16_t x, uint16_t y){
  if (video_load_xpm(ball) != OK){
    printf("Error draw_plataform: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}
