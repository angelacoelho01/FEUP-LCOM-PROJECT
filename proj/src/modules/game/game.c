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

int(play_solo_game)(uint16_t mode) {

  if (start_video_mode(mode) != OK)
    return 1;

  if (draw_scenario(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y) != OK) {
    return_to_text_mode();
    return 1;
  }

  // To subscribe the Timer interrupts
  uint8_t timer_bit_no;
  if (timer_subscribe_int(&timer_bit_no) != OK)
    return 1;

  // To subscribe the KBC interrupts
  uint8_t kbc_bit_no;
  if (keyboard_subscribe_int(&kbc_bit_no) != OK)
    return 1;

  int ipc_status;
  message msg;

  uint32_t timer_irq_set = BIT(timer_bit_no);
  uint32_t kbc_irq_set = BIT(kbc_bit_no);

  bool game_started = false;
  uint16_t ball_x = SOLO_SCENARIO_CORNER_X + BALL_TO_LEFT_X, ball_y = SOLO_SCENARIO_CORNER_Y + BALL_TO_TOP_Y;
  while (kbc_scancode != ESC_BREAKCODE_KEY) {
    int r;
    // Get a request message.
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
          if(ball_y-1 > BALL_LIMIT_TOP)
            draw_ball(ball_x, --ball_y);
          if (timer_counter % 60 == 0) { // true every 1 second (freq = 60Hz)
            if (game_started) start_game(); // the player moved the plataform for the first
                                // time (3 lives) - start the clock
            else timer_counter = 0;
          }
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
                    true; // the ball start moving and the timer starts to count
                          // just only there was a movement from the player
              }
            }
          }
          tickdelay(micros_to_ticks(WAIT_KBC));
        }
        break;
      default:
        break;
      }
    } 
  }

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

void (start_game)(){
  unsigned int seconds = timer_counter / 60;
  uint8_t minutes = seconds / 60;
  seconds = (seconds < 60 ? seconds : seconds % 60);

  draw_clock(minutes, (uint8_t)seconds,
              SOLO_SCENARIO_CORNER_X + FIRST_NUMBER_TO_LEFT_X,
              SOLO_SCENARIO_CORNER_Y + FIRST_NUMBER_TO_TOP_Y);

  if (seconds % 30 == 0) { //Decreases platform every 30 seconds
    if (plataform_to_draw != 4) { // if not in it's final form
      ++plataform_to_draw;
      draw_plataform(plataforms[plataform_to_draw], plataform_x,
                      SOLO_SCENARIO_CORNER_Y +
                          PLATAFORM_TO_TOP_Y_INIT,
                      SOLO_SCENARIO_CORNER_X);
    }
  }
}

bool (move_plataform)(){
  uint16_t width = plataform_width[plataform_to_draw];

  if((kbc_scancode == RIGHT_ARROW_MAKECODE) || (kbc_scancode == D_MAKECODE)){
    uint16_t plataform_end = plataform_x + width;
    if (plataform_end < scenario_limit_right){ //Right Arrow => shift to the right
      if((plataform_end + PLATAFORM_DISPLACEMENT) < scenario_limit_right)
        plataform_x += PLATAFORM_DISPLACEMENT;
      else
        plataform_x = scenario_limit_right - width;
      
      return true;
    }
  }
  else if((kbc_scancode == LEFT_ARROW_MAKECODE) || (kbc_scancode == A_MAKECODE)){
    if (plataform_x > scenario_limit_left){ //Left Arrow => shift to the left
      if((plataform_x - PLATAFORM_DISPLACEMENT) > scenario_limit_left)
        plataform_x -= PLATAFORM_DISPLACEMENT;
      else
        plataform_x = scenario_limit_left;
      
      return true;
    }
  }

  return false; 
}
