#include "game.h"

#include <stdlib.h>
#include <time.h>

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

extern uint16_t plataform_x;

extern size_t plataform_to_draw;
extern uint8_t no_lives;

bool lost, game_started = false, is_move_ball = false;

extern uint8_t minutes, seconds;

uint16_t ball_speed = BALL_SPEED;
uint16_t plataform_speed = PLATAFORM_SPEED;

#include "../../modules/video/video.h"

extern unsigned h_res, v_res;


int(play_solo_game)(uint16_t mode) {
  struct Player p1 = {"Joao", 0};

  // limits of solo game
  uint16_t scenario_limit_left = SOLO_SCENARIO_CORNER_X + BORDER_WIDTH;
  uint16_t scenario_limit_right = SOLO_SCENARIO_CORNER_X + SCENARIO_WIDTH - BORDER_WIDTH;

   plataform_x = SOLO_SCENARIO_CORNER_X + PLATAFORM_TO_LEFT_X_INIT;
 
  if (start_video_mode(mode) != OK){
    return_to_text_mode();
    return 1;
  }
  
  draw_start_menu();
  sleep(5);

  if (draw_scenario(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y) != OK) {
    return_to_text_mode();
    return 1;
  }

  draw_pause_menu();
  sleep(10);
  vg_exit();
  return 0;

  // to subscribe the Timer interrupts
  uint8_t timer_bit_no;
  if (timer_subscribe_int(&timer_bit_no) != OK)
    return 1;

  // to subscribe the KBC interrupts
  uint8_t kbc_bit_no;
  if (keyboard_subscribe_int(&kbc_bit_no) != OK)
    return 1;

  int ipc_status;
  message msg;

  uint32_t timer_irq_set = BIT(timer_bit_no);
  uint32_t kbc_irq_set = BIT(kbc_bit_no);

  // initial informations relative to the ball
  uint16_t ball_x = (uint16_t) SOLO_SCENARIO_CORNER_X + BALL_TO_LEFT_X;
  uint16_t ball_y = (uint16_t) SOLO_SCENARIO_CORNER_Y + BALL_TO_TOP_Y;
  bool up = true, left = rand() & 1;

  while ((kbc_scancode != ESC_BREAKCODE_KEY) && (0 != no_lives)) {
    int r;
    // get a request message
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    // received notification
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
      // hardware interrupt notification
      case HARDWARE:

        if (msg.m_notify.interrupts & timer_irq_set) { // timer interruption
          timer_int_handler();
          if (timer_counter % 60 == 0) { // true every 1 second (freq = 60Hz)
            start_clock(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y); // the player moved the plataform for the first time (3 lives) - start the clock
          }
          if (is_move_ball) move_ball(&ball_x, &ball_y, &up, &left, SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
        }

        if (msg.m_notify.interrupts & kbc_irq_set) { // KBC interruption
          kbc_ih(); // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT
          if (kbc_ih_error == 0) { // if there was no error
            if (!(kbc_scancode & BYTE_MSB)) { // if MSB = 0 -> make code
              if (move_plataform(scenario_limit_right, scenario_limit_left)) {
                draw_plataform(plataforms[plataform_to_draw], plataform_x,
                               SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y,
                               SOLO_SCENARIO_CORNER_X);
                // just  only if there was a movement from the player
                game_started = true; // timer starts to count  
                is_move_ball = true; // the ball start moving 
              }
            }
          }
          // tickdelay(micros_to_ticks(WAIT_KBC));
        }
        break;
      default:
        break;
      }
    } 
  }

  // check the reason why we break for the cicle
  if (0 == no_lives) game_over_display(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
  else game_win_display(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y, p1);
  
  sleep(5);

  // To unsubscribe the Timer interrupts
  if (timer_unsubscribe_int() != OK) return 1;

  // To unsubscribe the KBC interrupts
  if (keyboard_unsubscribe_int() != OK) return 1;

  if (return_to_text_mode() != OK) return 1;

  return 0;
}

void (start_clock)(uint16_t xi, uint16_t yi){
  if (game_started){
    seconds = timer_counter / 60;
    minutes = seconds / 60;
    seconds = (seconds < 60 ? seconds : seconds % 60);

    draw_clock(minutes, (uint8_t)seconds, xi + FIRST_NUMBER_TO_LEFT_X, yi + FIRST_NUMBER_TO_TOP_Y);

    if (seconds % 30 == 0) { // every 30 seconds
      if (plataform_to_draw != 4) { // if not in it's final form
        ++plataform_to_draw; // decreases plataform width
        ++ball_speed; // increases ball speed
        plataform_speed += 10;
        draw_plataform(plataforms[plataform_to_draw], plataform_x, yi + PLATAFORM_TO_TOP_Y, xi);
      }
    }
  } 
  else timer_counter = 0;
}

bool (move_plataform)(uint16_t right_limit, uint16_t left_limit){
  uint16_t width = plataform_width[plataform_to_draw];

  if ((kbc_scancode == RIGHT_ARROW_MAKECODE) || (kbc_scancode == D_MAKECODE)){
    uint16_t plataform_end = plataform_x + width;
    
    if (plataform_end < right_limit){ // right Arrow or D => shift to the right
      if((plataform_end + plataform_speed) < right_limit)
        plataform_x += plataform_speed;
      else
        plataform_x = right_limit - width;
      
      return true;
    }
  }
  else if((kbc_scancode == LEFT_ARROW_MAKECODE) || (kbc_scancode == A_MAKECODE)){
    if (plataform_x > left_limit){ // left Arrow or A=> shift to the left
      if((plataform_x - plataform_speed) > left_limit)
        plataform_x -= plataform_speed;
      else
        plataform_x = left_limit;
      
      return true;
    }
  }

  return false; 
}

void (next_life)(uint16_t* ball_x, uint16_t* ball_y, bool* up, bool* left, uint16_t xi, uint16_t yi){
  no_lives--;
  // we most keep the info of the blocks in the scenario - this are the ones that will be draw
  if (draw_scenario (xi, yi) != OK) return_to_text_mode();
  
  *ball_x = (uint16_t) xi + BALL_TO_LEFT_X;
  *ball_y = (uint16_t) yi + BALL_TO_TOP_Y;
  *up = true; *left = rand() & 1;
  is_move_ball = false; // do not move the ball till the player move the plataform again
  lost = false; // to keep track of the next try
  
  plataform_x = xi + PLATAFORM_TO_LEFT_X_INIT + (6*plataform_to_draw);
}

void (move_ball)(uint16_t* x, uint16_t* y, bool* up, bool* left, uint16_t scenario_xi, uint16_t scenario_yi){
 
  uint16_t xi = *x, yi = *y;
  // arranjar forma de nao calcular isto tantas vezes - mas ainda depender do canto do nivel - talvez por parametro ou ser global mas apenas inicializada dentro do play_solo
  uint16_t ball_top_limit = scenario_yi + BLOCKS_TO_TOP_Y + (BLOCKS_HEIGHT*NUMBER_BLOCKS_Y);
  uint16_t ball_down_limit = scenario_yi + PLATAFORM_TO_TOP_Y - BALL_HEIGHT;
  uint16_t ball_left_limit = scenario_xi + BORDER_WIDTH;
  uint16_t ball_right_limit = scenario_xi + SCENARIO_WIDTH - BORDER_WIDTH - BALL_WIDTH;
  unsigned int frame_down_limit = scenario_yi + PLATAFORM_TO_TOP_Y + PLATAFORM_HEIGHT + 20;

  if(*up){
    if((*y - ball_speed) > ball_top_limit) *y -= ball_speed;
    else{
      *y = ball_top_limit;
      *up = false;
      struct ball_position ball_pos = get_ball_position(*x,(unsigned int)*y);
      handle_collision(ball_pos);
    }
  }
  else{
    if((*y + ball_speed + BALL_HEIGHT) <= ball_down_limit) *y += ball_speed;
    else{
      uint32_t pixel_color = get_pixel_color(xi, yi+ ball_speed + BALL_HEIGHT);
      if(pixel_color == SCENARIO_BACKGROUND_COLOR){
        lost = true;
        *y += ball_speed;
      }
      else{
        *y = ball_down_limit;
        *up = true;
        lost = false; // to see the red borders too
      }
    }
  }

  if(*left){
    if((*x - ball_speed) > ball_left_limit) *x -= ball_speed;
    else{
      *x = ball_left_limit;
      *left = false;
    }
  }
  else{
    if((*x + ball_speed) < ball_right_limit) *x += ball_speed;
    else{
      *x = ball_right_limit;
      *left = true;
    }
  }
  if(lost && (*y + ball_speed + BALL_HEIGHT) >= frame_down_limit)
    next_life(x, y, up, left, scenario_xi, scenario_yi);
  else{
    clean_ball(xi, yi);
    draw_ball(*x, *y);
  }
}
