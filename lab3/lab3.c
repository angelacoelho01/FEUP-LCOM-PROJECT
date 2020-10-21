#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "i8042.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern char ih_error;
extern uint8_t scancode;
extern uint32_t cnt;

int(kbd_test_scan)() {
  
  uint8_t bit_no;
  if(keyboard_subscribe_int(&bit_no) != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  int ipc_status;
  message msg;

  uint32_t irq_set = BIT(bit_no);

  while(1) { //Equanto não receber um ESC
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
            kbc_ih();            
            if(ih_error == 0){
              uint8_t bytes[] = {scancode};
              if(scancode & 0x01){
               if(kbd_print_scancode(true, 1, bytes) != OK)
                return 1;
              }
              else{
                if(kbd_print_scancode(false, 1, bytes))
                  return 1;
              }
              if(scancode == ESC_BREAKCODE_REG)
               break;
            }
            tickdelay(micros_to_ticks(WAIT_KBC));
          }
          break;
        default:
          break; // no other notifications expected: do nothing
      }
    } 
  }

  if(keyboard_unsubscribe_int() != OK){
    printf("Error in %s.", __func__);
    return 1;
  }

  if(kbd_print_no_sysinb(cnt) != OK)
    return 1;

  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
