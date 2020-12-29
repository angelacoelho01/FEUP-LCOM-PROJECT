#ifndef _GRAPHICS_HEARTS_H
#define _GRAPHICS_HEARTS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../../xpm/load_xpms.h"

enum hearts_t{
  BIG_HEART,
  SMALL_HEAR
};

void (draw_hearts)(enum hearts_t n, uint8_t number_of_lives, uint16_t xi, uint16_t yi);

#endif 
