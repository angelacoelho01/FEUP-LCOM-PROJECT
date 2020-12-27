#include "graphics_ball.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

void (clean_ball)(uint16_t x, uint16_t y){
  video_draw_rectangle(x, y, BALL_WIDTH, BALL_HEIGHT, SCENARIO_BACKGROUND_COLOR);
}

void (draw_ball)(uint16_t x, uint16_t y){
  video_draw_pixmap(x, y, ball_xpm);
}
