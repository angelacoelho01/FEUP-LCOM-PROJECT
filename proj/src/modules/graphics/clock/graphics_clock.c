#include "graphics_clock.h"

#include "../../macros/block_breaker.h"
#include "../numbers/graphics_numbers.h"
#include "../../video/video.h"

int (draw_clock)(uint8_t minutes, uint8_t seconds, uint16_t xi, uint16_t yi){
  bool clock = true;
  // clear the reagion of the clock first
  video_draw_rectangle(xi, yi, (NUMBERS_WIDTH*4) + (SPACE_BETWEEN_NUMBERS*7), NUMBERS_HEIGHT, TIMER_BACKGROUND_COLOR);

  // minutes first digit
  if (draw_number(minutes / 10, xi, yi, clock) != OK) return 1;
  // minutes last digit
  if (draw_number(minutes % 10, xi + NUMBERS_WIDTH + SPACE_BETWEEN_NUMBERS, yi, clock) != OK) return 1;

  // separador :
  // Top point
  video_draw_rectangle(xi + (NUMBERS_WIDTH*2) + (SPACE_BETWEEN_NUMBERS*3), yi + 6, SPACE_BETWEEN_NUMBERS, SPACE_BETWEEN_NUMBERS, NUMBERS_COLOR);
  // bottom point
  video_draw_rectangle(xi + (NUMBERS_WIDTH*2) + (SPACE_BETWEEN_NUMBERS*3), yi + 6 + SPACE_BETWEEN_NUMBERS*2, SPACE_BETWEEN_NUMBERS, SPACE_BETWEEN_NUMBERS, NUMBERS_COLOR);

  // seconds first digit
  if (draw_number(seconds / 10, xi + (NUMBERS_WIDTH*2) + (SPACE_BETWEEN_NUMBERS*6), yi, clock) != OK) return 1;
  // seconds last digit
  if (draw_number(seconds % 10, xi + (NUMBERS_WIDTH*3) + (SPACE_BETWEEN_NUMBERS*7), yi, clock) != OK) return 1;

  return 0;
}
