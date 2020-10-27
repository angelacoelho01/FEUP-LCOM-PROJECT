#include <lcom/lcf.h>
// #include <lcom/lab2.h> // to use timer defined em lab2 ?
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "../lab2/i8254.h"
#include "../lab2/timer.c"
#include "i8042.h"
#include "keyboard.h"
#include "utils.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g08/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g08/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

// from kbc handler
extern char ih_error;
extern uint8_t scancode;

// from timer handler handler
extern unsigned long counter;

#ifdef LAB3
extern uint32_t cnt;
#endif

int(kbd_test_scan)() {
  
  // To subscribe the KBC interrupts
  uint8_t bit_no;
  if(keyboard_subscribe_int(&bit_no) != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  int ipc_status;
  message msg;

  uint32_t irq_set = BIT(bit_no);
  
  // driver_receive() loop
  // Terminate when it reads the breakcode of the ESC key: 0x81
  while(scancode != ESC_BREAKCODE_KEY) { 
    int r;
    // Get a request message. 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { // received notification 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt 
            kbc_ih(); // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT     
            if(ih_error == 0){ // if there was no error
              // print the scancode readed 
              uint8_t bytes[] = {scancode};
              if(!(scancode & BYTE_MSB)){ // if MSB = 0 -> make
                if(kbd_print_scancode(true, 1, bytes) != OK)
                  return 1;
              }
              else{ // if MSB = 1 -> break
                if(kbd_print_scancode(false, 1, bytes) != OK)
                  return 1;
              }
            }
            tickdelay(micros_to_ticks(WAIT_KBC));
          }
          break;
        default:
          break; // no other notifications expected: do nothing
      }
    } else{ // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  // To unsubscribe the KBC interrupts
  if(keyboard_unsubscribe_int() != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  #ifdef LAB3 // Counting the number of sys_inb() calls
  if(kbd_print_no_sysinb(cnt) != OK)
    return 1;
  #endif

  return 0;
}

int(kbd_test_poll)() {

  while(scancode != ESC_BREAKCODE_KEY) { // Exit when user releases the ESC key
    // read scancodes sent 
    if(kbc_poll_handler() == OK){ // if there was no error
      // print the scancode readed 
      uint8_t bytes[] = {scancode};
      if(!(scancode & BYTE_MSB)){ // if MSB = 0 -> make
        if(kbd_print_scancode(true, 1, bytes) != OK)
          return 1;
      }
      else{ // if MSB = 1 -> break
        if(kbd_print_scancode(false, 1, bytes) != OK)
          return 1;
      }
    }
    tickdelay(micros_to_ticks(WAIT_KBC));
  }

  #ifdef LAB3 // Print the number of sys_inb() kernel calls
  if(kbd_print_no_sysinb(cnt) != OK) { return 1; }
  #endif

  if(kbc_enable_int() != OK){ 
    printf("error when enable interrupts");
    return 1; 
  }
 
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  // To subscribe the KBC interrupts
  uint8_t kbc_bit_no;
  if(keyboard_subscribe_int(&kbc_bit_no) != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  // To subscribe the timer interrupts
  uint8_t timer_bit_no;
  if(timer_subscribe_int(&timer_bit_no) != OK){
    printf("error in %s: fail to subscribe timer!\n", __func__);
    return 1;
  }

  int ipc_status;
  message msg;

  uint32_t kbd_int_bit = BIT(kbc_bit_no);
  uint32_t timer0_int_bit = BIT(timer_bit_no);
  
  // driver_receive() loop
  // Terminate when it reads the breakcode of the ESC key: 0x81
  while((scancode != ESC_BREAKCODE_KEY) && (counter < n*60)) { 
    int r;
    // Get a request message. 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { // received notification 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: // hardware interrupt notification
          if (msg.m_notify.interrupts & kbd_int_bit) { // Keyboard subscribed interrupt 
            counter = 0; // scancode received - reset counter
            kbc_ih(); // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT     
            if(ih_error == 0){ // if there was no error
              // print the scancode readed 
              uint8_t bytes[] = {scancode};
              if(!(scancode & BYTE_MSB)){ // if MSB = 0 -> make
                if(kbd_print_scancode(true, 1, bytes) != OK)
                  return 1;
              }
              else{ // if MSB = 1 -> break
                if(kbd_print_scancode(false, 1, bytes) != OK)
                  return 1;
              }
            }
            tickdelay(micros_to_ticks(WAIT_KBC));
          }

          if (msg.m_notify.interrupts & timer0_int_bit) { // Timer0 subscribed interrupt 
            timer_int_handler(); // incrementa counter
            /*
            if (counter % 60 == 0){ // true se passou mais 1 segundo, admitindo freq normal = 60 
              timer_print_elapsed_time();
            }
            */
          }

          break;
        default:
          break; // no other notifications expected: do nothing
      }
    } else{ // received a standard message, not a notification
      // no standard messages expected: do nothing
    }
  }

  // To unsubscribe the KBC interrupts
  if(keyboard_unsubscribe_int() != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  // To unsubscribe the timer interrupts
  if(timer_unsubscribe_int() != OK){
    printf("error in %s : timer unsubscribe!\n", __func__);
    return 1;
  }

  return 0;
}
