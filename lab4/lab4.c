// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you


#include "../lab2/i8254.h"
#include "../lab2/timer.c"
#include "i8042.h"
#include "mouse.h"
#include "utils.h"


// from MOUSE handler
extern char ih_error;
extern uint8_t byte;
extern struct packet pp;

// from timer handler
extern unsigned long counter;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  //Enable data reporting
	if(mouse_enable_data_reporting() != OK){
		printf("Error in %s.", __func__);
		return 1;
	}

	//Subscribes mouse's interrupts
	uint8_t bit_no;
	if(mouse_subscribe_int(&bit_no) != OK){
		printf("Error in %s.", __func__);
		return 1;
	}

  int ipc_status;
  message msg;

  uint32_t irq_set = BIT(bit_no);

  uint32_t n = 0;
  uint8_t num_bytes = 0;

  //Driver receive loop
  //Ends when it reads a certain number of packets - cnt
  while(n < cnt){
    int r;
    //Get a request message
    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver_receive faile with : %d", r);
      continue;
    }
    //Checks if it received a notification
    if(is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        //Hardware interrupt notification
        case HARDWARE:
          //Subscribed interrupt
          if(msg.m_notify.interrupts & irq_set){
           //Reads one byte from the kbc’s output buffer per interrupt
            mouse_ih();
            //If there was no error
            if(ih_error == 0){
              if(get_packet(byte))
                mouse_print_packet(&pp);
                //Reset number of bytes
                if(num_bytes == 2)
                  num_bytes = 0;
            }
          }
          tickdelay(micros_to_ticks(WAIT_KBC));
        break;
      default:
        break;
      }
    }
  }

      // To unsubscribe the Mouse interrupts
  if(mouse_unsubscribe_int() != OK){
	  printf("Error in %s.", __func__);
	  return 1;
  }
	
	// Disable data reporting
	if(mouse_disable_data_reporting() != OK){
		printf("Error in %s.", __func__);
		return 1;
	}
  
  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* To be completed */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
