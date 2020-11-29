#include "timer.h"

int hook_id = TIMER0_IRQ; // inicializado com qualquer valor entre 0..7

int (timer_subscribe_int)(uint8_t *bit_no) {
  
  *bit_no = hook_id; 
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK){
    printf("ERROR in subcribe_int: sys_irqsetpolicy!!\n");
    return 1;
  }

  return 0;
}

int (timer_unsubscribe_int)() {
    
  if (sys_irqrmpolicy(&hook_id) != OK){
    printf("ERROR in unsubcribe_int: iqrmpolicy!\n");
    return 1;
  }

  return 0;
}

unsigned long counter = 0; // global counter variable 

void (timer_int_handler)() {
  // increment a global counter variable
  counter++;
}


