#include "colision.h"

#include "../../macros/block_breaker.h"

void (get_block_position)(unsigned int x, unsigned int y){
  struct block_position pos;
  struct coordinates coord = {x,y};
  pos.upper_left_corner = coord;
  get_upper_right_corner(&pos);
  get_lower_left_corner(&pos);
  get_lower_right_corner(&pos);
  blocks_pos[no_blocks_positions++] = pos;
}

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

bool (get_block_pos)(unsigned int i, struct block_position* pos){
  if(i > blocks_position_size) return false;
  *pos = blocks_pos[i];
  return true;
}

void (print_blocks_position)(){
  sort_block_pos();
  for(size_t i = 0; i < blocks_position_size; i++){
    printf("no = %d\n", i);
    printf("upper left corner: (%d, %d)\n", blocks_pos[i].upper_left_corner.x, blocks_pos[i].upper_left_corner.y);
    printf("upper right corner: (%d, %d)\n", blocks_pos[i].upper_right_corner.x, blocks_pos[i].upper_right_corner.y);
    printf("lower left corner: (%d, %d)\n", blocks_pos[i].lower_left_corner.x, blocks_pos[i].lower_left_corner.y);
    printf("lower right corner: (%d, %d)\n", blocks_pos[i].lower_right_corner.x, blocks_pos[i].lower_right_corner.y);
  }
}

int (compare_block_pos)(const void* p1, const void* p2){
  const struct block_position pos1 = *(const struct block_position*)p1;
  const struct block_position pos2 = *(const struct block_position*)p2;
  if(pos1.upper_left_corner.y == pos2.upper_left_corner.y)
    return ((int)pos1.upper_left_corner.x - (int)pos2.upper_left_corner.x);
  return ((int)pos2.upper_left_corner.y - (int)pos1.upper_left_corner.y);
}

// sorts in rever order in order to make a faster implementation
void (sort_block_pos)(){
  qsort(blocks_pos, blocks_position_size, sizeof(struct block_position), compare_block_pos);
}

bool (compare_coordinates)(const struct coordinates coord1, const struct coordinates coord2){
  printf("COORD1 = (%d, %d), COORD2 = (%d, %d)\n", coord1.x, coord1.y, coord2.x, coord2.y);
  return ((coord1.x == coord2.x) && (coord1.y == coord2.y));
}

int (find_block_pos)(const struct block_position pos){
  for(size_t i = 0; i < blocks_position_size; i++){
    if(compare_coordinates(blocks_pos[i].upper_left_corner, pos.upper_left_corner) &&
      compare_coordinates(blocks_pos[i].upper_right_corner, pos.upper_right_corner) &&
      compare_coordinates(blocks_pos[i].lower_left_corner, pos.lower_left_corner) &&
      compare_coordinates(blocks_pos[i].lower_right_corner, pos.lower_right_corner)) return i;
  }
  return -1;
}

bool (delete_block_pos)(const struct block_position* pos){
  if(find_block_pos(*pos) == -1) return false;
  for(size_t i = find_block_pos(*pos); i < blocks_position_size; i++)
    blocks_pos[i] = blocks_pos[i+1];
  blocks_position_size--;
  free((void*)pos);
  return true;
}
