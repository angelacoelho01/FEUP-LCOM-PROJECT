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

//Constroi um read-back command
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  int timer_register;
  //Irá criar o read back command de acordo com o timer selcionado
  uint8_t rbcommand = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  //Irá guardar o registo relativo ao timer selecionado
  if(timer == 0)
    timer_register = TIMER_0;
  else if (timer == 1)
    timer_register = TIMER_1;
  else
    timer_register = TIMER_2;
  //Escreve o read back command no registo de controlo e result1 = 0 se for bem sucedido
  int result1 = sys_outb(TIMER_CTRL, rbcommand);
  //Obtém o estado, para st, do timer pretendido e result2 = 0 se for bem sucedido
  int result2 = util_sys_inb(timer_register, st);
  
  //Se as 2 funções anteriores forem bem sucedidas, retorna 0
  return (result1 | result2);
}

//Recebe o timer, o status e o field, as opções que passamos
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

  switch (field)
  {
  case 0:
    //tsf_all = configuration/status
    printf("%u\n", st);
    break;
  
  case 1:
    //tsf_initial = timer initialization mode
    break;

  case 2:
    //tsf_mode = timer counting mode 
    break;

  case 3:
    //tsf_base = timer counting base

  default:
    break;
  }
                        
  /* To be implemented by the students */
  //union timer_status_field_val conf;
  //Usar um switch ou if para o field
 
  
  //timer_print_config(timer, field, conf);
 // printf("%s is not yet implemented!\n", __func__);

  return 1;
}
