#ifndef _COLISION_H
#define _COLISION_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../macros/block_breaker.h"


struct coordinates{
  uint16_t x;
  uint16_t y;
};

struct block_position{
  struct coordinates upper_left_corner;
  struct coordinates upper_right_corner;
  struct coordinates lower_left_corner;
  struct coordinates lower_right_corner;
};

void (get_upper_right_corner)(struct block_position* pos);

void (get_lower_left_corner)(struct block_position* pos);

void (get_lower_right_corner)(struct block_position* pos);

#endif
