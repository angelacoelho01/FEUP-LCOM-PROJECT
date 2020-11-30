// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "video.h"
#include "keyboard.h"
#include "timer.h"

extern uint8_t scancode;
extern int hook_id;
extern vbe_mode_info_t mode_conf;
extern unsigned bits_per_pixel;
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;
extern unsigned int counter;
extern vg_vbe_contr_info_t controller_info;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g08/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g08/lab5/output.txt");

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

  if(vg_draw_rectangle(x,y, width, height, color) != OK){
    vg_exit();
    return 1;
  }

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

  if(video_get_mode_info(mode, &mode_conf) != OK) return 1;
  if(map_memory() != OK) return 1;

  //Sets the video card to a certain graphic mode
  if(video_set_graphic_mode(mode) != OK) return 1;

  uint16_t width, height;
  //Gets the width and height of each rectangle
  get_size(no_rectangles, &width, &height);
  //Initializes color with the first
  uint32_t color = first;
  //Initializes coordinates at (0,0)
  uint16_t x = 0, y = 0;
  for(uint16_t i = 0; i  < no_rectangles; i++){
    for(uint16_t j = 0; j < no_rectangles; j++){
        //Gets the color throught the given functions and according to the color mode
        get_color(&color, first, i, j, no_rectangles, step);
        //Draws a rectangle; in case it doesn't work, returns to text mode
        if(vg_draw_rectangle(x, y, width, height, color) != OK){
          vg_exit();
          return 1;
        } 
        //Goes to the next column according to the calculated width
        x += width;
    }
    //Resets the column to start a new line
    x = 0;
    //Goes to the next line according to the calculated height
    y += height; 
  }

  if(keyboard_subscribe_int(&bit_no) != OK) return 1;

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
  //Start to change the video mode to 0x105
  uint16_t mode = 0x105;
  if(video_get_mode_info(mode, &mode_conf) != OK) return 1;
  if(map_memory() != OK) return 1;
  if(video_set_graphic_mode(mode) != OK) return 1;
  //Loads the xpm
  uint8_t* address;
  if((address = xpm_load(xpm, xpm_type, &xpm_image)) == NULL){
    vg_exit();
    return 1;
  }

  draw_pixmap(x, y);


  //Subscribe keyboard interruptions
  uint8_t bit_no;
  if(keyboard_subscribe_int(&bit_no) != OK) return 1;

  message msg;
  int ipc_status;
  uint32_t irq_set = BIT(bit_no);

  while(scancode != ESC_BREAKCODE_KEY){
    int r;
    if((r = driver_receive(ANY, &msg, &ipc_status)) != OK){
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    switch(_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
      {
        if(msg.m_notify.interrupts & irq_set){
          if(keyboard_read_scancode() != OK) return 1;
        }
        break;
      
      default:
        break;
      }
    }
  }

  //Unsubscribe keyboard interruptions
  if(keyboard_unsubscribe_int() != OK) return 1;
  //Returns to text mode
  if(vg_exit() != OK) return 1;
  return 0;

}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  
  uint16_t mode = 0x105;
  if(video_get_mode_info(mode, &mode_conf) != OK) return 1;
  if(map_memory() != OK) return 1;

  //Sets the video card to a certain graphic mode
  if(video_set_graphic_mode(mode) != OK) return 1;

  //Loads the xpm
  uint8_t* address;
  if((address = xpm_load(xpm, xpm_type, &xpm_image)) == NULL){
    vg_exit();
    return 1;
  }

  //Subscribes keyboard interruptions
  uint8_t keyboard_bit_no;
  if(keyboard_subscribe_int(&keyboard_bit_no) != OK) return 1;
  //Subscribes timer interruptions
  uint8_t timer_bit_no;
  if(timer_subscribe_int(&timer_bit_no) != OK) return 1;

  message msg;
  int ipc_status;
  uint32_t keyboard_irq_set = BIT(keyboard_bit_no), timer_irq_set = BIT(timer_bit_no);
  
  //Number of frames
  int no_frames = 0;
  uint16_t ticks_per_frame = sys_hz()/fr_rate;
  //Draws the first pixmap
  if (draw_pixmap(xi, yi) != OK) return 1;
  //The initial coordinates
  uint16_t x = xi, y = yi;   
  //The distance between the first and last position (by default, an horizontal movement)
  int32_t length = abs(xf - xi);
  if(xf == xi) length = abs(yf - yi);

 

  while(scancode != ESC_BREAKCODE_KEY){
    int r; 
    if((r = driver_receive(ANY, &msg, &ipc_status))!= 0){
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    switch(_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
        //In case it receives a keyboard interruption
        if(msg.m_notify.interrupts & keyboard_irq_set){
          if(keyboard_read_scancode() != OK) return 1;
        }
        //In case it receives a timer interruption
        if(msg.m_notify.interrupts & timer_irq_set){
          timer_int_handler();
          
          if((0 == (counter % ticks_per_frame)) && (0 != length)){
            no_frames++;
            //In case speed is non negative, then speed represents the nº of pixels between consecutive frames
            if(speed >= 0){
              if(sprite(&x, &y, xf, yf, speed, &length) != OK) return 1;
            }
            //In case speed is negative, then it represents the necessary frames to the next move of 1 pixel
            else {
              if(abs(speed) == no_frames){
                //When no_frames reaches the abs(speed), then it moves 1 pixel
                if(sprite(&x, &y, xf, yf, 1, &length) != OK) return 1;
                no_frames = 0;
              }
            }
          }
 
        }
        break;

      default:
        break;
    } 

  }

  //Returns to text mode
  if(vg_exit() != OK) return 1;
  //Unsubscribes keyboard interruptions
  if(keyboard_unsubscribe_int() != OK) return 1;
  //Unsubscribes timer interruptions
  if(timer_unsubscribe_int() != OK) return 1;

  return 0;
}

int(video_test_controller)() {
  printf("Under construction!\n");
  return 1;
}
