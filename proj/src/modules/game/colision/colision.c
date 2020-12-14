#include "colision.h"

void (get_upper_right_corner)(struct block_position* pos){
  uint16_t xi = pos->upper_left_corner.x, yi = pos->upper_left_corner.y;
  pos->upper_right_corner.x = xi + BLOCKS_WIDTH;
  pos->upper_right_corner.y = yi;
}

void (get_lower_left_corner)(struct block_position* pos){
  uint16_t xi = pos->upper_left_corner.x, yi = pos->upper_left_corner.y;
  pos->lower_left_corner.x = xi;
  pos->lower_left_corner.y = yi + BLOCKS_HEIGHT;
}

void (get_lower_right_corner)(struct block_position* pos){
  uint16_t xi = pos->upper_left_corner.x, yi = pos->upper_left_corner.y;
  pos->lower_right_corner.x = xi + BLOCKS_WIDTH;
  pos->lower_right_corner.y = yi + BLOCKS_HEIGHT;
}

