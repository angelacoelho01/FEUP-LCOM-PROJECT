#include "graphics.h"

#include <time.h>
#include <stdlib.h>


extern vbe_mode_info_t mode_conf;
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;

// Varible that keep the x of the plataform, witch is change 
// according to the key pressed between the limits of the scenario: 
uint16_t plataform_x = SOLO_SCENARIO_CORNER_X + PLATAFORM_TO_LEFT_X; // para ja ainda so para o modo de jogo a solo

// Limits of the game
uint16_t scenario_limit_left = SOLO_SCENARIO_CORNER_X + BORDER_WIDTH;
uint16_t scenario_limit_right = SOLO_SCENARIO_CORNER_X + SCENARIO_WIDTH - BORDER_WIDTH;
uint16_t ball_limit_top = SOLO_SCENARIO_CORNER_Y + TIMER_BACK_HEIGHT;
uint16_t ball_limit_bottom = SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y_INIT; // when surpassed this value that means that the user lose a life

// Represents the plataform to be draw (after x time the plataform in game is one with a smaller width)
size_t plataform_to_draw = 0;
uint8_t no_lives = 3; // the amount of lives left for the player


int (draw_scenario)(uint16_t xi, uint16_t yi){
  // Draw the scenario background
  video_draw_rectangle(xi, yi, SCENARIO_WIDTH, SCENARIO_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  // Draw the background for the timer
  video_draw_rectangle(xi, yi, SCENARIO_WIDTH, TIMER_BACK_HEIGHT, TIMER_BACKGROUND_COLOR);

  // Draw the borders of the scenario
  // Top border
  video_draw_rectangle(xi, yi, SCENARIO_WIDTH, BORDER_WIDTH, SCENARIO_BORDER_COLOR);
  // Bottom border
  video_draw_rectangle(xi, yi + SCENARIO_HEIGHT - BORDER_WIDTH, SCENARIO_WIDTH, BORDER_WIDTH, SCENARIO_BORDER_COLOR);
  // Left border
  video_draw_rectangle(xi, yi, BORDER_WIDTH, SCENARIO_HEIGHT, SCENARIO_BORDER_COLOR);
  // Right border
  video_draw_rectangle(xi + SCENARIO_WIDTH - BORDER_WIDTH, yi, BORDER_WIDTH, SCENARIO_HEIGHT, SCENARIO_BORDER_COLOR);

  // Draw the matrix of blocks in is inicial position
  if (draw_blocks(xi + BLOCKS_TO_LEFT_X, yi + BLOCKS_TO_TOP_Y) != OK){
    printf("Error draw_scenario: draw_blocks!\n");
    return 1;
  }

  // Draw the plataform in is inicial coordenates and format
  if (draw_plataform(plataforms[plataform_to_draw], xi + PLATAFORM_TO_LEFT_X, yi + PLATAFORM_TO_TOP_Y_INIT, xi) != OK){
    printf("Error draw_scenario: draw_plataform!\n");
    return 1;
  }

  // Draw the ball in is inicial coordenates 
  if (draw_ball(xi + BALL_TO_LEFT_X, yi + BALL_TO_TOP_Y) != OK){
    printf("Error draw_scenario: draw_ball!\n");
    return 1;
  }

  // Draw the 3 inicial lives of the player
  if (draw_hearts(0, no_lives, xi + SCENARIO_WIDTH - FIRST_HEART_TO_RIGHT_X, yi + FIRST_HEART_TO_TOP_Y) != OK){
    printf("Error draw_scenario: draw_hearts!\n");
    return 1;
  }


  // Draw the inicial clock 00:00
  if (draw_clock(0, 0, xi + FIRST_NUMBER_TO_LEFT_X, yi + FIRST_NUMBER_TO_TOP_Y) != OK){
    printf("Error draw_scenario: draw_clock!\n");
    return 1;
  }
  
  return 0;
}


int (draw_plataform)(xpm_map_t xpm, uint16_t x, uint16_t y, uint16_t scenario_x){
  // clear the reagion of the plataform first
  video_draw_rectangle(scenario_x + BORDER_WIDTH, y, SCENARIO_WIDTH - (BORDER_WIDTH*2), PLATAFORM_HEIGHT, SCENARIO_BACKGROUND_COLOR);

  if (video_load_xpm(xpm) != OK){
    printf("Error draw_plataform: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}

int (draw_blocks)(uint16_t xi, uint16_t yi){
  uint16_t x = xi, y = yi;
  // unsigned int width = 40, height = 20;
  // uint32_t no_blocks_h = (320-10)/width, no_blocks_v = (480-80)/height;

  for(uint16_t i = 0; i  < NUMBER_BLOCKS_Y; i++){
    for(uint16_t j = 0; j < NUMBER_BLOCKS_X; j++){
      // Draw a block of a random color
      xpm_row_t* xpm = blocks[rand() % NUMBER_BLOCKS_COLORS];
      if (video_load_xpm(xpm) != OK){
        printf("Error draw_blocks: vg_load_xpm!\n");
        return 1;
      }
      video_draw_pixmap(x, y);

      x += BLOCKS_WIDTH;
    }
    // Next Line
    x = xi;
    y += BLOCKS_HEIGHT; 
  }

  return 0;
}

void (clean_ball)(uint16_t x, uint16_t y){
  video_draw_rectangle(x, y, BALL_WIDTH, BALL_HEIGHT, SCENARIO_BACKGROUND_COLOR);
}

int (draw_ball)(uint16_t x, uint16_t y){
  if (video_load_xpm(ball) != OK){
    printf("Error draw_plataform: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}

int (draw_clock)(uint8_t minutes, uint8_t seconds, uint16_t xi, uint16_t yi){
  // clear the reagion of the clock first
  video_draw_rectangle(xi, yi, (NUMBERS_WIDTH*4) + (SPACE_BETWEEN_NUMBERS*7), NUMBERS_HEIGHT, TIMER_BACKGROUND_COLOR);

  // minutes first digit
  if (draw_number(minutes / 10, xi, yi) != OK) return 1;
  // minutes last digit
  if (draw_number(minutes % 10, xi + NUMBERS_WIDTH + SPACE_BETWEEN_NUMBERS, yi) != OK) return 1;

  // separador :
  // Top point
  video_draw_rectangle(xi + (NUMBERS_WIDTH*2) + (SPACE_BETWEEN_NUMBERS*3), yi + 6, SPACE_BETWEEN_NUMBERS, SPACE_BETWEEN_NUMBERS, NUMBERS_COLOR);
  // bottom point
  video_draw_rectangle(xi + (NUMBERS_WIDTH*2) + (SPACE_BETWEEN_NUMBERS*3), yi + 6 + SPACE_BETWEEN_NUMBERS*2, SPACE_BETWEEN_NUMBERS, SPACE_BETWEEN_NUMBERS, NUMBERS_COLOR);

  // seconds first digit
  if (draw_number(seconds / 10, xi + (NUMBERS_WIDTH*2) + (SPACE_BETWEEN_NUMBERS*6), yi) != OK) return 1;
  // seconds last digit
  if (draw_number(seconds % 10, xi + (NUMBERS_WIDTH*3) + (SPACE_BETWEEN_NUMBERS*7), yi) != OK) return 1;

  return 0;
}

int (draw_number)(size_t n, uint16_t x, uint16_t y){
  if (video_load_xpm(numbers[n]) != OK){
    printf("Error draw_number: vg_load_xpm!\n");
    return 1;
  }

  video_draw_pixmap(x, y);

  return 0;
}

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
