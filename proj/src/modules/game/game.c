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

extern uint16_t plataform_x, scenario_limit_right, scenario_limit_left;
extern size_t plataform_to_draw;
extern uint8_t no_lives;

extern bool lost;  
bool game_started = false, is_move_ball = false;

extern uint8_t minutes, seconds;

uint16_t ball_speed = BALL_SPEED;
uint16_t plataform_speed = PLATAFORM_SPEED;

int(play_solo_game)(uint16_t mode) {
  struct Player p1 = {"Joao", 0};
 
  if (start_video_mode(mode) != OK)
    return 1;

  if (draw_scenario(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y) != OK) {
    return_to_text_mode();
    return 1;
  }

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
  uint16_t ball_y = (uint16_t)SOLO_SCENARIO_CORNER_Y + BALL_TO_TOP_Y;
  bool up = true, left = true;

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
            start_clock(); // the player moved the plataform for the first time (3 lives) - start the clock
          }
          if (is_move_ball) move_ball(&ball_x, &ball_y, &up, &left);
        }

        if (msg.m_notify.interrupts & kbc_irq_set) { // KBC interruption
          kbc_ih(); // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT
          if (kbc_ih_error == 0) { // if there was no error
            if (!(kbc_scancode & BYTE_MSB)) { // if MSB = 0 -> make code
              if (move_plataform()) {
                draw_plataform(plataforms[plataform_to_draw], plataform_x,
                               SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y_INIT,
                               SOLO_SCENARIO_CORNER_X);
                game_started =
                    true; // the ball start moving and the timer starts to count - just only if there was a movement from the player
                is_move_ball = true;
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
  if (0 == no_lives) {
    game_over(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
  } else{
    game_win(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y, p1);
  }

  sleep(5);

  // To unsubscribe the Timer interrupts
  if (timer_unsubscribe_int() != OK) return 1;

  // To unsubscribe the KBC interrupts
  if (keyboard_unsubscribe_int() != OK) return 1;

  if (return_to_text_mode() != OK) {
    printf("Error play_game: return to text mode.\n");
    return 1;
  }

  return 0;
}

void (start_clock)(){
  if (game_started){
    seconds = timer_counter / 60;
    minutes = seconds / 60;
    seconds = (seconds < 60 ? seconds : seconds % 60);

    draw_clock(minutes, (uint8_t)seconds, SOLO_SCENARIO_CORNER_X + FIRST_NUMBER_TO_LEFT_X,
                SOLO_SCENARIO_CORNER_Y + FIRST_NUMBER_TO_TOP_Y);

    if (seconds % 30 == 0) { // every 30 seconds
      if (plataform_to_draw != 4) { // if not in it's final form
        ++plataform_to_draw; // decreases plataform width
        ++ball_speed; // increases ball speed
        plataform_speed += 10;
        draw_plataform(plataforms[plataform_to_draw], plataform_x,
                        SOLO_SCENARIO_CORNER_Y +
                            PLATAFORM_TO_TOP_Y_INIT,
                        SOLO_SCENARIO_CORNER_X);
      }
    }
  } else {
    timer_counter = 0;
  }
}

bool (move_plataform)(){
  uint16_t width = plataform_width[plataform_to_draw];

  if ((kbc_scancode == RIGHT_ARROW_MAKECODE) || (kbc_scancode == D_MAKECODE)){
    uint16_t plataform_end = plataform_x + width;
    
    if (plataform_end < scenario_limit_right){ // right Arrow or D => shift to the right
      if((plataform_end + plataform_speed) < scenario_limit_right)
        plataform_x += plataform_speed;
      else
        plataform_x = scenario_limit_right - width;
      
      return true;
    }
  }
  else if((kbc_scancode == LEFT_ARROW_MAKECODE) || (kbc_scancode == A_MAKECODE)){
    if (plataform_x > scenario_limit_left){ // left Arrow or A=> shift to the left
      if((plataform_x - plataform_speed) > scenario_limit_left)
        plataform_x -= plataform_speed;
      else
        plataform_x = scenario_limit_left;
      
      return true;
    }
  }

  return false; 
}

void (reset_game)(uint16_t* ball_x, uint16_t* ball_y, bool* up, bool* left){
  no_lives--;
  // we most keep the info of the blocks in the scenario - this are the ones that will be draw
  if (draw_scenario (SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y) != OK) return_to_text_mode();
  
  *ball_x = (uint16_t) SOLO_SCENARIO_CORNER_X + BALL_TO_LEFT_X;
  *ball_y = (uint16_t) SOLO_SCENARIO_CORNER_Y + BALL_TO_TOP_Y;
  *up = true; *left = true;
  is_move_ball = false; // do not move the ball till the player move the plataform again
  lost = false; // to keep track of the next try
  plataform_x = SOLO_SCENARIO_CORNER_X + PLATAFORM_TO_LEFT_X;
}

void (move_ball)(uint16_t* x, uint16_t* y, bool* up, bool* left){
  uint16_t xi = *x, yi = *y;
  if(*up){
    if((*y - ball_speed) > BALL_TOP_LIMIT) *y -= ball_speed;
    else{
      *y = BALL_TOP_LIMIT;
      *up = false;
    }
  }
  else{
    if((*y + ball_speed + BALL_HEIGHT) <= BALL_DOWN_LIMIT) *y += ball_speed;
    else{
      uint32_t pixel_color = get_pixel_color(xi, yi+ ball_speed + BALL_HEIGHT);
      if(pixel_color == SCENARIO_BACKGROUND_COLOR){
        lost = true;
        *y += ball_speed;
      }
      else{
        *y = BALL_DOWN_LIMIT;
        *up = true;
      }
    }
  }

  if(*left){
    if((*x - ball_speed) > BALL_LEFT_LIMIT) *x -= ball_speed;
    else{
      *x = BALL_LEFT_LIMIT;
      *left = false;
    }
  }
  else{
    if((*x + ball_speed) < BALL_RIGHT_LIMIT) *x += ball_speed;
    else{
      *x = BALL_RIGHT_LIMIT;
      *left = true;
    }
  }
  if(lost && (*y + ball_speed + BALL_HEIGHT) >= FRAME_DOWN_LIMIT)
    reset_game(x, y, up, left);
  else{
    clean_ball(xi, yi);
    draw_ball(*x, *y);
  }
}
