#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "../lab2/i8254.h"
#include "../lab2/timer.c"
#include "i8042.h"
#include "mouse.h"
#include "utils.h"

// from MOUSE handler
extern char ih_error;
extern uint8_t byte;

// from timer handler
extern unsigned long counter;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/g08/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g08/lab4/output.txt");

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
	if(mouse_enable_data_report() != OK){ 
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
  struct packet pp;

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
              if(get_packet(byte, &num_bytes, &pp) == 0){ // indicates that a packet is complete
                mouse_print_packet(&pp);
                n++;
              }
            }else{
              printf("error in mouse_ih()");
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

  // Disable data reporting - duvidas na implementacao
	if(mouse_disable_data_reporting() != OK){
		printf("Error in %s.", __func__);
		return 1;
	}

  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  //Enable data reporting 
	if(mouse_enable_data_report() != OK){ 
		printf("Error in %s.", __func__);
		return 1;
	}

	//Subscribes mouse's interrupts
	uint8_t mouse_bit_no;
	if(mouse_subscribe_int(&mouse_bit_no) != OK){
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

  uint32_t mouse_irq_set = BIT(mouse_bit_no);
  uint32_t timer_irq_set = BIT(timer_bit_no);

  uint8_t num_bytes = 0;
  struct packet pp;

  //Driver receive loop
  //Ends when it reads a certain number of packets - cnt
  while(counter < idle_time*60){
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
          if(msg.m_notify.interrupts & mouse_irq_set){
            counter = 0;
            //Reads one byte from the kbc’s output buffer per interrupt
            mouse_ih();
            //If there was no error
            if(ih_error == 0){
              if(get_packet(byte, &num_bytes, &pp) == 0){ // indicates that a packet is complete
                mouse_print_packet(&pp);
              }
            }else{
              printf("error in mouse_ih()");
            }
          }
          if(msg.m_notify.interrupts & timer_irq_set){
            timer_int_handler();
          }
          tickdelay(micros_to_ticks(WAIT_KBC));
        break;
      default:
        break;
      }
    }
  }

  // To unsubscribe the timer interrupts
  if(timer_unsubscribe_int() != OK){
    printf("error in %s : timer unsubscribe!\n", __func__);
    return 1;
  }

  // To unsubscribe the Mouse interrupts
  if(mouse_unsubscribe_int() != OK){
	  printf("Error in %s.", __func__);
	  return 1;
  }

  // Disable data reporting - duvidas na implementacao
	if(mouse_disable_data_reporting() != OK){
		printf("Error in %s.", __func__);
		return 1;
	}

  return 0;

}

// S, SL1, SL2, F
// quando rdown os outros incluindo o left tem de ser largados

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  // verificar ordemm destes
  //Enable data reporting 
	if(mouse_enable_data_report() != OK){ 
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

  uint8_t num_bytes = 0;
  struct packet pp;

  bool flag = false;
  bool draw = false;

  while(!draw){
    int r;
    //Get a request message
    if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
      printf("driver_receive faile with : %d", r);
      continue;
    }
    //Checks if it received a notification
    if(is_ipc_notify(ipc_status)){
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: //Hardware interrupt notification
          //Subscribed interrupt
          if(msg.m_notify.interrupts & irq_set){
            mouse_ih();
            if(ih_error == 0){ //If there was no error
              if(get_packet(byte, &num_bytes, &pp) == 0){ // indicates that a packet is complete
                mouse_print_packet(&pp);
                flag = true;
              }
            }else continue;
          }

          if (flag == true){ // verifica o estado de todos os botoes
          // de acordo com isto chama o check_draw com o evento respetivo
          // no check_draw é que o automato é processado
          /* Now, do application dependent event handling */
          if (pp.lb == 1) {
            printf("botao esquerdo primido?\n");
            //check_draw(LDOW); <- atualiza o estado do automato de acordo com a transição que deve tomar (verifica situações de tolerancia e slope e c_len minimo)
            // draw = true;
          }

          if (pp.lb == 0) {
            printf("botao esquerdo levantado?\n");
            // draw = true;
          }


          if (pp.rb == 1) {
            printf("botao direito primido?\n");
          }
           if (pp.rb == 0) {
            printf("botao direito levantado?\n");
            // draw = true;
          }

          if (pp.mb == 1){
            printf("botao meio primido?\n");
          }
           if (pp.mb == 0) {
            printf("botao meio levantado?\n");
            // draw = true;
          }
          flag = false;
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

  // Disable data reporting - duvidas na implementacao
	if(mouse_disable_data_reporting() != OK){
		printf("Error in %s.", __func__);
		return 1;
	}

  return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
  
  // disable minix's mouse IH - write the cmd byte to kbc - lcf_start()
    
  uint8_t n = 0;
  uint8_t num_bytes = 0;
  struct packet pp;

  // Disable (0xF5)
  if(mouse_disable_data_reporting() != OK){
    printf("Error in mouse_disable_data_reporting().\n");
    return 1;
  }

  // Set Remote mode
  if(mouse_set_remote() != OK){
    printf("Error in mouse_set_remote()\n");
    return 1;
  }
  
  while(n < cnt){
    tickdelay(micros_to_ticks(period*1000));
    if(mouse_poll_handler() == OK){ // read from read Data
      if(get_packet(byte, &num_bytes, &pp) == 0){ // indicates that a packet is complete
        mouse_print_packet(&pp);
        n++;
      }
    }
  }

  // Set stream mode before exiting
  if(mouse_set_stream() != OK){
    printf("Error in mouse_set_stream().\n");
    return 1;
  }

  // Disable (0xF5)
  if(mouse_disable_data_reporting() != OK){
    printf("Error in mouse_disable_data_reporting().\n");
    return 1;
  }

  // Reset the KBC’s command byte to its default value
  if(reset_kbc_status() != OK){
    printf("Error in reset_kbc_status().\n");
    return 1;
  }

  return 0;
}
