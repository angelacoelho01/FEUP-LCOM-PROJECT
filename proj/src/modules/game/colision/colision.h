#ifndef _COLISION_H
#define _COLISION_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCKS_POSITION_SIZE 28
static size_t blocks_position_size = BLOCKS_POSITION_SIZE;

struct coordinates{
  unsigned int x;
  unsigned int y;
};

struct block_position{
  struct coordinates upper_left_corner;
  struct coordinates upper_right_corner;
  struct coordinates lower_left_corner;
  struct coordinates lower_right_corner;
};

static struct block_position blocks_pos[BLOCKS_POSITION_SIZE]; 
static unsigned int no_blocks_positions = 0;

void (get_block_position)(unsigned int x, unsigned int y);

void (get_upper_right_corner)(struct block_position* pos);

void (get_lower_left_corner)(struct block_position* pos);

void (get_lower_right_corner)(struct block_position* pos);

bool (get_block_pos)(unsigned int i, struct block_position* pos);

void (print_blocks_position)();

int (compare_block_pos)(const void* p1, const void* p2);

void (sort_block_pos)();

bool (compare_coordinates)(const struct coordinates coord1, const struct coordinates coord2);

int (find_block_pos)(struct block_position pos);

bool (delete_block_pos)(const struct block_position* pos);

#endif
