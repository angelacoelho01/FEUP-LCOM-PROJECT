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

  return game_start(mode);

}
