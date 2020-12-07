#include "game.h"

#include <time.h>
#include <stdlib.h>

// TIMER VARIABLES
extern int timer_hook_id;
extern unsigned long timer_counter;

// KEYBOARD VARIABLES
extern char kbc_ih_error;
extern uint8_t kbc_scancode;

// VIDEO VARIABLES
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
uint8_t lives = 3; // the amount of lives left for the player

// quando existir um menu a parte de inicializar o mode e return para o texto vai possivelmente passar para lá
int (play_solo_game)(uint16_t mode){
  srand(time(NULL));

  if (start_video_mode(mode) != OK){
    printf("Error play_game: start video mode.\n");
    return 1;
  }

  if (draw_scenario(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y) != OK){
    printf("Error play_game: draw_scenario.\n");
    return_to_text_mode();
    return 1;
  }

  // To subscribe the Timer interrupts
  uint8_t timer_bit_no;
  if(timer_subscribe_int(&timer_bit_no) != OK){
    printf("error in %s: fail to subscribe timer!\n", __func__);
    return 1;
  }

  // To subscribe the KBC interrupts
  uint8_t kbc_bit_no;
  if(keyboard_subscribe_int(&kbc_bit_no) != OK){
    printf("Error in %s.\n", __func__);
    return 1;
  }

  int ipc_status;
  message msg;

  uint32_t timer_irq_set = BIT(timer_bit_no);
  uint32_t kbc_irq_set = BIT(kbc_bit_no);

  bool game_started = false;
  
  // driver_receive() loop
  // Terminate when ... 
  while (kbc_scancode != ESC_BREAKCODE_KEY) { // wait 5 seconds 
    int r;
    // Get a request message. 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }

    // received notification
    if (is_ipc_notify(ipc_status)) {  
      switch (_ENDPOINT_P(msg.m_source)) {
        // hardware interrupt notification
        case HARDWARE: 
          if (msg.m_notify.interrupts & timer_irq_set){
            timer_int_handler();
            if (timer_counter % 60 == 0){ // true de 1 em 1 seg, admitindo freq normal = 60 
              if (game_started){ // the player moved the plataform for the first time (3 lives) - start the clock
                // TO DO:: call draw_clock(minutes, seconds, SOLO_SCENARIO_CORNER_X + FIRST_NUMBER_TO_LEFT_X, SOLO_SCENARIO_CORNER_Y + FIRST_NUMBER_TO_TOP_Y)
                // with the corresponding minutes and seconds
                unsigned int seconds = timer_counter / 60;
                uint8_t minutes = seconds / 60;
                seconds = (seconds < 60 ? seconds : seconds % 60);
                
                draw_clock(minutes, (uint8_t)seconds, SOLO_SCENARIO_CORNER_X + FIRST_NUMBER_TO_LEFT_X, SOLO_SCENARIO_CORNER_Y + FIRST_NUMBER_TO_TOP_Y);

                if ((timer_counter / 60) % 30 == 0){ // de 30 em 30 segundos - diminuir a barra
                  if (plataform_to_draw != 4){ // if not in it's final form
                    ++plataform_to_draw;
                    draw_plataform(plataforms[plataform_to_draw], plataform_x, SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y_INIT, SOLO_SCENARIO_CORNER_X);
                  }
                }
              } else {
                timer_counter = 0;
              }          
            }
          }

          if (msg.m_notify.interrupts & kbc_irq_set) { // KBC subscribed interrupt 
            kbc_ih(); // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT     
            if (kbc_ih_error == 0){ // if there was no error
              // seta direita -> MAKE: 0x4d BREAcK: 0xe0 0xcd 0xe0
              // seta esquerda -> MAKE: 0x4b BREAK: 0xe0 0xcd 0xe0
              // OBJECTIVE:: moves the plataform according the scancode read
              // --> MOVES ONE PIXEL AT A TIME ONLY <--
              if (!(kbc_scancode & BYTE_MSB)){ // if MSB = 0 -> make code
                bool key_flag = false;
                if (kbc_scancode == RIGHT_ARROW_MAKECODE){ // to the right, if not already on the limit
                  // 86 é a width da barra no seu estado inicial
                  if ((plataform_x + plataform_width[plataform_to_draw]) < scenario_limit_right){
                    key_flag = true;
                    ++plataform_x;
                  }
                } else if (kbc_scancode == LEFT_ARROW_MAKECODE){ // to the left, if not already on the limit
                  if (plataform_x > scenario_limit_left){
                    key_flag = true;
                    --plataform_x;
                  }
                }

                if (key_flag){
                  draw_plataform(plataforms[plataform_to_draw], plataform_x, SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y_INIT, SOLO_SCENARIO_CORNER_X);
                  game_started = true; // the ball start moving and the timer starts to count just only there was a movement from the player
                }
              }
            }
            tickdelay(micros_to_ticks(WAIT_KBC)); // <<-- ?? -->>
          }
          break;
        default:
          break; // no other notifications expected: do nothing
      }
    } else{ // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  // To unsubscribe the Timer interrupts
  if(timer_unsubscribe_int() != OK){
    printf("error in %s : timer unsubscribe!\n", __func__);
    return 1;
  }

  // To unsubscribe the KBC interrupts
  if(keyboard_unsubscribe_int() != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  if (return_to_text_mode() != OK){
    printf("Error play_game: return to text mode.\n");
    return 1;
  }

  return 0;
}

int (start_video_mode)(uint16_t mode){

  if (video_get_mode_info(mode, &mode_conf) != OK){
    printf("Error start_video_mode: video_get_mode_info!\n");
    return 1;
  }

  if (map_memory() != OK){
    printf("Error start_video_mode: map_memory!\n");
    return 1;
  }

  if (video_set_graphic_mode(mode) != OK){
    printf("Error start_video_mode: video_set_graphic_mode!\n");
    return_to_text_mode();
    return 1;
  }

  // set the corresponding main variables to this mode
  // eg.: xpm_type, bytes_per_pixel, ...
  if (set_mode_settings(mode) != OK){
    printf("Error play_game: start video mode.\n");
    return 1;
  }

  return 0;
}

int (return_to_text_mode)(){
  if(vg_exit() != OK){
    printf("Error returning to text mode.\n");
    return 1;
  }

  return 0;
}

// assim no modo de jogo 1v1 apenas basta defenir mandar desenhar o cenario, mas em relacao a dois cantos superiores esquerdos diferentes
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
  if (draw_hearts(0, lives, xi + SCENARIO_WIDTH - FIRST_HEART_TO_RIGHT_X, yi + FIRST_HEART_TO_TOP_Y) != OK){
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
