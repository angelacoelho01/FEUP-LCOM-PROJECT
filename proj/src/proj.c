// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include "modules/video/video.h"
#include "modules/keyboard/keyboard.h"
#include "modules/timer/timer.h"
#include "modules/mouse/mouse.h"
#include "utils/utils.h"
#include "modules/game/game.h"

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
  //printf("Usage: <mode - hex> <mini3 logo - true|false> <grayscale - true|false> <delay (secs)>\n");
  printf("Usage: <mode - hex>\n");
  return 1;
}

int(proj_main_loop)(int argc, char *argv[]) {
  /* 
   * Substitute the code below by your own
   */

  //
  // if you're interested, try to extend the command line options so that the usage becomes:
  // <mode - hex> <minix3 logo  - true|false> <grayscale - true|false> <delay (secs)>
  //
  //bool minix3_logo, grayscale;
  //uint8_t delay;
  uint16_t mode;


  /*if (argc != 4)
    return print_usage();*/
    if(argc != 1)
    return print_usage();

  //Parse mode info (it has some limitations for the sake of simplicity)
  if (sscanf(argv[0], "%hx", &mode) != 1) {
    printf("%s: invalid mode (%s)\n", __func__, argv[0]);
    return print_usage();
  }

  //Parse minix3_logo info 
  /*char temp1[5];
  if(sscanf(argv[1], "%s", temp1) != 1){
    printf("%s: error in reading minix3 logo (%s)\n", __func__, argv[1]);
    return print_usage();
  }
  //If the return value of strncmp != 0, then the strings are different
  minix3_logo = strncmp(temp1, "true", 5) ? false : true;

  //Parse grayscale infor
  char temp2[5];
  if(sscanf(argv[2], "%s", temp2) != 1){
    printf("%s: error in reading grasyscale (%s)\n", __func__, argv[2]);
    return print_usage();
  }
  //If the return value of the strncmp != 0, then the strings are different
  grayscale = strncmp(temp2, "true", 5) ? false : true;

  //Parse the number of the delay seconds
  char temp3[5];
  if(sscanf(argv[3], "%s", temp3) != 1){
    printf("%s: invalid number of delay seconds (%s)\n", __func__, argv[3]);
    return print_usage();
  }
  delay = atoi(temp3);*/

  /*
  Test my function
  */
  // draw inicial scenario - only draw the plataform in a concrete position - to see if its working
  // not the real xpm for the plataform
  start_video_mode(mode);
  draw_blocks();
  return_to_text_mode();

  return 0;
}
