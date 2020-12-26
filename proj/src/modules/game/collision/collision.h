#ifndef _COLLISION_H
#define _COLLISION_H

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
  xpm_row_t* xpm;
};

struct ball_position{
  struct coordinates center;
  struct coordinates upper_left_corner;
  struct coordinates upper_right_corner;
  struct coordinates lower_left_corner;
  struct coordinates lower_right_corner;
  
};

static struct block_position blocks_pos[BLOCKS_POSITION_SIZE]; 
static unsigned int no_blocks_positions = 0;

/**
 * For each block gets its corners coordinates and its relative xpm, adding it to the array 
 * block_pos with all the remaining blocks (the ones that have not been broken yet) information.
 *
 * @param x the x coordinate of the block upper left corner
 * @param y the y coordinate of the block upper left corner
 * @param xpm the xpm relative to the block
 */
void (get_all_blocks_positions)(unsigned int x, unsigned int y, xpm_row_t* xpm);

/**
 * Gets the upper right corner coordinates.
 *
 * @param pos the struct block_position where to update the upper right corner coordinates
 */
void (get_upper_right_corner)(struct block_position* pos);

/**
 * Gets the lower left corner coordinates.
 *
 * @param pos the struct block_position where to update the lower left corner coordinates
 */
void (get_lower_left_corner)(struct block_position* pos);

/**
 * Gets the lower right corner coordinates.
 *
 * @param pos the struct block_position where to update the lower right corner coordinates
 */
void (get_lower_right_corner)(struct block_position* pos);

/**
 * Gets the information relative to a block (corners coordinates and relative xpm) by index.
 *
 * @param i the index
 * @param pos the struct to update with the block
 * @return true, if the block was found in the blocks_pos array (with all the remaining blocks);
 * false, otherwise
 */
bool (get_block_position)(unsigned int i, struct block_position* pos);

/**
 * Prints all the remaining blocks corners coordinates.
 */
void (print_blocks_position)();

/**
 * Compares the upper left corner coordinates for two blocks, in order to sort the blocks_pos array
 * in descending order according to the y position of the upper left corner and, in case of a tie,
 * in descending order of the x position of the upper left corner.
 *
 * @param p1 the first position coordinates
 * @param p2 the second position coordinates
 * @return true, if both x and y positions are equal for the two coordinates; false, otherwise
 */
int (compare_block_pos)(const void* p1, const void* p2);

/**
 * Sorts the array with all the remaining blocks information according to the compare_block_pos
 * function. Therefore, the blocks are sorted in descending order according to the y position of
 * the upper left corner and, in case of a tie, in descending order of the x position of the upper
 * left corner.
 */
void (sort_block_pos)();

/**
 * Compares the x and y positions of two coordinates.
 *
 * @param p1 the first position coordinates
 * @param p2 the second position coordinates
 * @return true, if both x and y positions are equal for the two coordinates; false, otherwise
 */
bool (compare_coordinates)(const struct coordinates coord1, const struct coordinates coord2);

/**
 * Searches for a certain block in the remaining blocks.
 *
 * @param pos the relative information of the block to be found
 * @return the relative index of the block on the blocks_pos array, if found; -1, otherwise
 */
int (find_block_pos)(struct block_position pos);

/**
 * For each block broken, it is deleted from the blocks_pos array that just has the remaining
 * blocks information.
 *
 * @param pos the information relative to the block to be deleted
 * @return true, if the block was found in the blocks_pos array and it was deleted successfully;
 * false, otherwise
 */
bool (delete_block_pos)(const struct block_position* pos);

/**
 * Deletes a block from the blocks_pos array by index.
 *
 * @param i the index of the block to be deleted
 * @return true, if the index doesn't exceed the blocks_pos size and if it is a non negative number;
 * false, otherwise
 */
bool (delete_block_pos_by_index)(unsigned int i);

/**
 * Gets the blocks_pos array with all the remaining blocks information.
 *
 * @return the pointer to the first element of the blocks_pos array
 */
struct block_position* (get_list_blocks_positions)();

/**
 * Gets the number of the remaining blocks, that is the size of the blocks_pos array.
 *
 * @return the number of the remaining blocks
 */
size_t (get_list_size)();

/*-----------------------------------BALL--------------------------------------------*/

/**
 * Gets the ball x and y positions for each corner and also the center, given the x and y positions
 * of the upper left corner.
 *
 * @param x the x position of the upper left corner coordinates
 * @param y the y position of the upper left corner coordinates
 * @return the struct with ball positions for each corner and center
 */
struct ball_position (get_ball_position)(unsigned int x, unsigned int y);


bool (collision_from_bottom)(struct block_position block_pos, struct ball_position ball_pos);

bool (collisiton_from_right)(struct block_position block_pos, struct ball_position ball_pos, uint16_t ball_speed, uint16_t* x, uint16_t* y);

bool (collision_from_left)(struct block_position block_pos, struct ball_position ball_pos, uint16_t ball_speed, uint16_t* x, uint16_t* y);

void (handle_collision)(bool* left, uint16_t ball_speed, uint16_t* x, uint16_t* y);

uint16_t (get_ball_top_limit)(uint16_t x, uint16_t y, uint16_t scenario_yi);

uint16_t (get_ball_right_limit)(uint16_t x, uint16_t y, uint16_t scenario_xi);

uint16_t (get_ball_left_limit)(uint16_t x, uint16_t y, uint16_t scenario_xi);

#endif
