#include "graphics_labels.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"
#include "../../../xpm/labels.h"

void (draw_game_over_label)(uint16_t x, uint16_t y){
  // clear the reagion first
  video_draw_rectangle(x, y, GAME_OVER_WIDTH , GAMR_OVER_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  video_draw_pixmap(x, y, labels_xpms[GAME_OVER_LABEL]);
}

void (draw_game_win_label)(uint16_t x, uint16_t y){
  // clear the reagion first
  video_draw_rectangle(x, y, YOU_WIN_WIDTH , YOU_WIN_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  video_draw_pixmap(x, y, labels_xpms[WINNER_LABEL]);
}

void (draw_score_label)(uint16_t x, uint16_t y){
  // clear the reagion first
  video_draw_rectangle(x, y, SCORE_LABEL_WIDTH , SCORE_LABEL_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  video_draw_pixmap(x, y, labels_xpms[SCORE_LABEL]);
}
