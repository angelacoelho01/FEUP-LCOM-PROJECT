// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include "modules/macros/block_breaker.h"
#include "modules/macros/i8042.h"

#include "modules/keyboard/keyboard.h"
#include "modules/mouse/mouse.h"
#include "modules/timer/timer.h"
#include "modules/video/video.h"
#include "utils/utils.h"
#include "modules/graphics/graphics.h"
#include "modules/game/player/player.h"

#include "modules/game/collision/collision.h"

#include "modules/graphics/ball/graphics_ball.h"
#include "modules/graphics/blocks/graphics_blocks.h"
#include "modules/graphics/clock/graphics_clock.h"
#include "modules/graphics/hearts/graphics_hearts.h"
#include "modules/graphics/labels/graphics_labels.h"
#include "modules/graphics/menus/graphics_menus.h"
#include "modules/graphics/numbers/graphics_numbers.h"
#include "modules/graphics/plataform/graphics_plataform.h"

#include "xpm/load_xpms.h"
#include "modules/game/game.h"

bool lost, game_started = false, is_move_ball = false;

uint16_t ball_speed = BALL_SPEED;
uint16_t plataform_speed = PLATAFORM_SPEED;
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

extern uint8_t minutes, seconds;

// #include "modules/game/player/player.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g08/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g08/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

static int print_usage() {
  printf("Usage: <mode - hex>\n");
  return 1;
}

int(proj_main_loop)(int argc, char *argv[]) {
  uint16_t mode;
  srand(time(NULL));


  if (argc != 1)
    return print_usage();

  // Parse mode info (it has some limitations for the sake of simplicity)
  if (sscanf(argv[0], "%hx", &mode) != 1) {
    printf("%s: invalid mode (%s)\n", __func__, argv[0]);
    return print_usage();
  }

  load_all_xpms();
  // limits of solo game
  uint16_t scenario_limit_left = SOLO_SCENARIO_CORNER_X + BORDER_WIDTH;
  uint16_t scenario_limit_right = SOLO_SCENARIO_CORNER_X + SCENARIO_WIDTH - BORDER_WIDTH;

  plataform_x = SOLO_SCENARIO_CORNER_X + PLATAFORM_TO_LEFT_X_INIT;

  struct Player p1 = add_player("Joao", 0);
  write_players("/home/lcom/labs/g08/proj/src/data/players_scores.txt");

  if (start_video_mode(mode) != OK){
    return_to_text_mode();
    return 1;
  }
  
  draw_start_menu();
  sleep(5);
  reset_screen();

  draw_scenario(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);

  //copy_to_double_buffer();
  //draw_pause_menu();
  //sleep(10);
  //vg_exit();
  //return 0;


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
        if (msg.m_notify.interrupts & kbc_irq_set) { // KBC interruption
          kbc_ih(); // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT
          if (kbc_ih_error == 0) { // if there was no error
            if (!(kbc_scancode & BYTE_MSB)) { // if MSB = 0 -> make code
              if (move_plataform(scenario_limit_right, scenario_limit_left)) {
                draw_plataform(plataform_x, SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y, SOLO_SCENARIO_CORNER_X, plataforms_xpms[plataform_to_draw]);
                // just  only if there was a movement from the player
                game_started = true; // timer starts to count  
                is_move_ball = true; // the ball start moving 
              }
            }
          }
        }

        if (msg.m_notify.interrupts & timer_irq_set) { // timer interruption
          timer_int_handler();
          //copy_from_double_buffer();
          //if(game_started) copy_from_double_buffer();
          if (timer_counter % 60 == 0) { // true every 1 second (freq = 60Hz)
            start_clock(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y); // the player moved the plataform for the first time (3 lives) - start the clock
          }
          if (is_move_ball) move_ball(&ball_x, &ball_y, &up, &left, SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
        }
          // tickdelay(micros_to_ticks(WAIT_KBC));
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
