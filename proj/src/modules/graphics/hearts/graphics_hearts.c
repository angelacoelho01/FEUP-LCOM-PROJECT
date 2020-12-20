#include "graphics_hearts.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

int (draw_hearts)(size_t n, uint8_t number_of_lives, uint16_t xi, uint16_t yi){
  // clear the reagion of the hearts first
  video_draw_rectangle(xi - (HEART_WIDTH*3) - (SPACE_BETWEEN_HEARTS*2), yi, (HEART_WIDTH*3) + (SPACE_BETWEEN_HEARTS*2), HEART_HEIGHT, TIMER_BACKGROUND_COLOR);

  // draw the amout of hearts correponding with the amount of hearts of the player in game
  for (int i = 0; i < number_of_lives; i++){
    xi -= HEART_WIDTH;
    if (video_load_xpm(hearts[n]) != OK){ // only big heart
      printf("Error draw_hearts: vg_load_xpm!\n");
      return 1;
    }

    video_draw_pixmap(xi, yi);
    xi -= SPACE_BETWEEN_HEARTS;
  }

  return 0;
}
