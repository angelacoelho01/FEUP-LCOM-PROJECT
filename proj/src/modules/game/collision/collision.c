#include "collision.h"

#include "../../macros/block_breaker.h"
#include "../../video/video.h"

void (get_all_blocks_positions)(unsigned int x, unsigned int y, xpm_row_t* xpm){
  struct block_position pos;
  struct coordinates coord = {x,y};
  pos.upper_left_corner = coord;
  get_upper_right_corner(&pos);
  get_lower_left_corner(&pos);
  get_lower_right_corner(&pos);
  pos.xpm = xpm;
  blocks_pos[no_blocks_positions++] = pos;
}

struct block_position* (get_list_blocks_positions)(){
  return blocks_pos;
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

bool (get_block_position)(unsigned int i, struct block_position* pos){
  if(i >= blocks_position_size) return false;
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

bool (delete_block_pos_by_index)(unsigned int i){
  if(i >= blocks_position_size) return false;
  return delete_block_pos(&blocks_pos[i]);
}

struct ball_position (get_ball_position)(unsigned int x, unsigned int y){
  struct coordinates coord_center = {x + (BALL_WIDTH/2), y + (BALL_HEIGHT/2)};
  struct coordinates coord_upper_left_corner = {x, y};
  struct coordinates coord_upper_right_corner = {x+BALL_WIDTH, y};
  struct coordinates coord_lower_left_corner = {x, y+BALL_HEIGHT};
  struct coordinates coord_lower_right_corner = {x+BALL_WIDTH, y+BALL_HEIGHT};
  struct ball_position ball_pos = {coord_center, coord_upper_left_corner, coord_upper_right_corner, coord_lower_left_corner, coord_lower_right_corner};

  return ball_pos;
}

bool (collision_from_bottom)(struct block_position block_pos, struct ball_position ball_pos){
  //Bottom collision
  if((((ball_pos.upper_left_corner.x >= block_pos.lower_left_corner.x) &&
    (ball_pos.upper_left_corner.x <= block_pos.lower_right_corner.x)) ||
    ((ball_pos.upper_right_corner.x >= block_pos.lower_left_corner.x) &&
    (ball_pos.upper_right_corner.x <= block_pos.lower_right_corner.x))) &&
    (block_pos.lower_right_corner.y == ball_pos.upper_right_corner.y))
    return true;
  return false;
}

bool (collision_from_left)(struct block_position block_pos, struct ball_position ball_pos){

  //Left side collision
  if((((ball_pos.upper_left_corner.y >= block_pos.upper_right_corner.y) &&
    (ball_pos.upper_left_corner.y <= block_pos.lower_right_corner.y)) ||
    ((ball_pos.lower_left_corner.y >= block_pos.upper_right_corner.y) &&
    (ball_pos.lower_left_corner.y <= block_pos.lower_right_corner.y))) &&
    (ball_pos.upper_left_corner.x == block_pos.upper_right_corner.x))
    return true;
    
  return false;
}

bool (collision_from_right)(struct block_position block_pos, struct ball_position ball_pos){
  //Right side collision
  if((((ball_pos.upper_right_corner.y >= block_pos.upper_left_corner.y) &&
    (ball_pos.upper_right_corner.y <= block_pos.lower_left_corner.y)) ||
    ((ball_pos.lower_right_corner.y >= block_pos.upper_left_corner.y) &&
    (ball_pos.lower_right_corner.y <= block_pos.lower_left_corner.y ))) &&
    (ball_pos.upper_right_corner.x == block_pos.upper_left_corner.x)) 
    return true;
  return false;
}

bool (handle_collision)(struct ball_position ball_pos, bool* left){
  for(size_t i = 0; i < blocks_position_size; i++){
    bool flag = false;
    if(collision_from_bottom(blocks_pos[i], ball_pos)){
      printf("BREAKS BLOCK FROM BOTTOM\n");
      flag = true; 
    }
    if(collision_from_left(blocks_pos[i], ball_pos)){
        printf("BREAKS BLOCK FROM LEFT\n");
        *left = false;
        flag = true;
    }

    if(collision_from_right(blocks_pos[i], ball_pos)){
      printf("BREAKS BLOCK FROM RIGHT\n");
      *left = true;
      flag = true;
    }
    if(flag){
      video_draw_rectangle(blocks_pos[i].upper_left_corner.x, blocks_pos[i].upper_left_corner.y,
                            BLOCKS_WIDTH, BLOCKS_HEIGHT, SCENARIO_BACKGROUND_COLOR);
      delete_block_pos_by_index(i);
    }
  }  
  return true;
}

size_t (get_list_size)(){
  return blocks_position_size;
}

uint16_t (get_ball_top_limit)(uint16_t x, uint16_t y, uint16_t scenario_yi){
  struct ball_position ball_pos = get_ball_position(x, y); 
  uint16_t top_limit = scenario_yi + BLOCKS_TO_TOP_Y;
  for(unsigned i = 0; i < blocks_position_size; i++){
    if(((ball_pos.upper_left_corner.x >= blocks_pos[i].lower_left_corner.x) &&
    (ball_pos.upper_left_corner.x <= blocks_pos[i].lower_right_corner.x)) ||
    ((ball_pos.upper_right_corner.x >= blocks_pos[i].lower_left_corner.x) &&
    (ball_pos.upper_right_corner.x <= blocks_pos[i].lower_right_corner.x)))
      top_limit = blocks_pos[i].lower_left_corner.y;
  }
  return top_limit;
}

uint16_t (get_ball_right_limit)(uint16_t x, uint16_t y, uint16_t scenario_xi){
  struct ball_position ball_pos = get_ball_position(x, y);
  uint16_t right_limit = scenario_xi + SCENARIO_WIDTH - BORDER_WIDTH - BALL_WIDTH;
  for(unsigned i = 1; i < blocks_position_size; i++){
    if((((ball_pos.upper_right_corner.y >= blocks_pos[i].upper_left_corner.y) &&
      (ball_pos.upper_right_corner.y <= blocks_pos[i].lower_left_corner.y)) ||
      ((ball_pos.lower_right_corner.y >= blocks_pos[i].upper_left_corner.y) &&
      (ball_pos.lower_right_corner.y <= blocks_pos[i].lower_left_corner.y)))){
        if((i % NUMBER_BLOCKS_X != 0) &&
          (ball_pos.upper_right_corner.x < blocks_pos[i].upper_left_corner.x) &&
          (ball_pos.upper_right_corner.x > blocks_pos[i-1].upper_left_corner.x))
            return blocks_pos[i].upper_left_corner.x;
      }
  }
  return right_limit;
}

uint16_t (get_ball_left_limit)(uint16_t x, uint16_t y, uint16_t scenario_xi){
  struct ball_position ball_pos = get_ball_position(x, y);
  uint16_t left_limit = scenario_xi + BORDER_WIDTH;
  for(unsigned i = 0; i < blocks_position_size; i++){
    if(((ball_pos.upper_left_corner.y >= blocks_pos[i].upper_right_corner.y) &&
      (ball_pos.upper_left_corner.y <= blocks_pos[i].lower_right_corner.y)) ||
      ((ball_pos.lower_left_corner.y >= blocks_pos[i].upper_right_corner.y) &&
      (ball_pos.lower_left_corner.y <= blocks_pos[i].lower_right_corner.y))){
        if((i % NUMBER_BLOCKS_X != 0) && 
        (ball_pos.upper_left_corner.x >= blocks_pos[i].upper_right_corner.x) &&
        (ball_pos.upper_left_corner.x < blocks_pos[i+1].upper_left_corner.x))
          return blocks_pos[i].upper_right_corner.x;
      }
  }
  return left_limit;
}


