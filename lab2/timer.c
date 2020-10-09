#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

//Construir um read-back command
//Escrever no st a informação que o timer vai ter na saída
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */
  uint8_t rbcommand = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer) ;
  if(sys_outb(TIMER_CTRL, rbcommand))
    return -1;
  //O primeiro argumento indica o timer do qual iremos ler o status (st)
  //Para que seja bem implementada nos testes, deve usar-se util_sys_inb em vez de usar apenas sys_inb
   if(!util_sys_inb(TIMER_0, st))
    return -2;
  //printf("%s is not yet implemented!\n", __func__);
  return 1;

}

//Recebe o timer, o status e o field, as opções que passamos
int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  //union timer_status_field_val conf;
  //Usar um switch ou if para o field
 
  
  //timer_print_config(timer, field, conf);
 // printf("%s is not yet implemented!\n", __func__);

  return 1;
}
