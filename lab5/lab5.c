// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "video.h"
#include "keyboard.h"

extern uint8_t scancode;
extern int hook_id;
extern vbe_mode_info_t mode_conf;
extern unsigned bits_per_pixel;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(video_get_mode_info(mode, &mode_conf) != OK) return 1;
  if(video_set_graphic_mode(mode) != OK) return 1;
  sleep(delay);
  if(vg_exit() != OK) return 1;
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
                            
  uint8_t bit_no;

  if(keyboard_subscribe_int(&bit_no) != OK) return 1;
  if(video_get_mode_info(mode, &mode_conf) != OK) return 1;
  if(map_memory() != OK) return 1;

  //Sets the video card to a certain graphic mode
  if(video_set_graphic_mode(mode) != OK) return 1;

  if(vg_draw_rectangle(x,y, width, height, color) != OK) return 1;

  message msg;
  int ipc_status;
  uint32_t irq_set = BIT(bit_no);

  while(scancode != ESC_BREAKCODE_KEY){

    int r; 
    if((r = driver_receive(ANY, &msg, &ipc_status))!= 0){
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    switch(_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
        if(msg.m_notify.interrupts & irq_set){
          if(keyboard_read_scancode() != OK) return 1;
        }
        break;
      
      default:
        break;
    } 

  }

  if(vg_exit() != OK) return 1;

  if(keyboard_unsubscribe_int() != OK) return 1;
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint8_t bit_no;

  if(keyboard_subscribe_int(&bit_no) != OK) return 1;
  if(video_get_mode_info(mode, &mode_conf) != OK) return 1;
  if(map_memory() != OK) return 1;

  //Sets the video card to a certain graphic mode
  if(video_set_graphic_mode(mode) != OK) return 1;

  uint16_t width, height;
  get_size(no_rectangles, &width, &height);
  printf("WIDTH = %d\nHEIGHT = %d\n", width, height);

  uint32_t color = first;
  uint16_t x = 0, y = 0;

  for(uint16_t i = 0; i  < no_rectangles; i++){
    for(uint16_t j = 0; j < no_rectangles; j++){
        color = get_color(first, i, j, no_rectangles, step);
        if(vg_draw_rectangle(x, y, width, height, color) != OK) return 1;
        x += width;
    }
    x = 0;
    y += height; 
  }

  //if(vg_draw_rectangle(x,y, width, height, color) != OK) return 1;

  message msg;
  int ipc_status;
  uint32_t irq_set = BIT(bit_no);

  while(scancode != ESC_BREAKCODE_KEY){

    int r; 
    if((r = driver_receive(ANY, &msg, &ipc_status))!= 0){
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    switch(_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
        if(msg.m_notify.interrupts & irq_set){
          if(keyboard_read_scancode() != OK) return 1;
        }
        break;
      
      default:
        break;
    } 

  }

  if(vg_exit() != OK) return 1;

  if(keyboard_unsubscribe_int() != OK) return 1;
  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
