#include "graphics_labels.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"
#include "../../../xpm/labels.h"

bool (draw_game_over_label)(uint16_t x, uint16_t y){
  // clear the reagion first
  video_draw_rectangle(x, y, GAME_OVER_WIDTH , GAMR_OVER_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  if (video_load_xpm(game_over_label) != OK){
    printf("Error draw_game_over: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}

bool (draw_game_win_label)(uint16_t x, uint16_t y){
  // clear the reagion first
  video_draw_rectangle(x, y, YOU_WIN_WIDTH , YOU_WIN_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  if (video_load_xpm(winner_label) != OK){
    printf("Error draw_game_over: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}

bool (draw_score_label)(uint16_t x, uint16_t y){
  // clear the reagion first
  video_draw_rectangle(x, y, SCORE_LABEL_WIDTH , SCORE_LABEL_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  if (video_load_xpm(score_label) != OK){
    printf("Error draw_game_over: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}
