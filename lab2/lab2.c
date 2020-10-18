#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>

extern unsigned long counter; // to use the global counter variable defined in timer.c

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {

  uint8_t st;
  if (timer_get_conf(timer, &st) != OK){
    printf("Error when calling function timer_get_conf!\n");
    return 1;
  }
  if (timer_display_conf(timer, st, field) != OK){
    printf("Error when calling function timer_display_conf!\n");
    return 1;
  }
  
  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
   return  timer_set_frequency(timer, freq);
}

int(timer_test_int)(uint8_t time) {
  
  uint8_t bit_no;
  if(timer_subscribe_int(&bit_no) != OK){
    printf("error in %s: fail to subscribe timer!\n", __func__);
    return 1;
  }

  // while 'time' invoke one per second the timer_print_elapsed_time()
   // INTERRUPT LOOP
  
  //int tique_counter = 0; -> com tique_counter
  int ipc_status;
  message msg;

  uint32_t irq_set = BIT(bit_no);
  
  // while (counter < time) { -> com tique_counter
  while( counter/60 < time ) { 
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
            //tique_counter++; -> com tique_counter
            //if (tique_counter % 60 == 0){ // passou 1 segundo, admitindo que a freq normal é 60 -> com tique_counter
            timer_int_handler();
            if (counter % 60 == 0){
              timer_print_elapsed_time();
              // tique_counter = 0; // para voltar a contar o proximo segundo -> com tique_counter
              // timer_int_handler(); // numero de seg que ja passaram -> com tique_counter
            }
          }
          break;
        default:
          break; // no other notifications expected: do nothing 	
      }
    } 
  }

  if(timer_unsubscribe_int() != OK){
    printf("error in %s : timer unsubscribe!\n", __func__);
    return 1;
  }

  return 0;
}
