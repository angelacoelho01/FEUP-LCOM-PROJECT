#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "../macros/i8254.h"

int timer_hook_id = 0;
unsigned long timer_counter = 0; // global timer_counter variable 

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  // obtain defined timer selection and port according to the chosen timer
  uint8_t timer_sel; 
  uint8_t port; 
  if(timer == 0){
    timer_sel = TIMER_SEL0;
    port = TIMER_0;
  } else if (timer == 1){
    timer_sel = TIMER_SEL1;
    port = TIMER_1; 
  } else{
    timer_sel = TIMER_SEL2;
    port = TIMER_2;
  }

  // read the input timer configuration before change it
  uint8_t st;
  if (timer_get_conf(timer, &st) != OK){
    printf("Error in function timer_get_conf!\n");
    return 1;
  }
  // IMP: make sure to keep the 4 last digits of the st

  // write control word to configure the chosen timer -> preferably, LSB followed by MSB
  uint8_t control_world = timer_sel | TIMER_LSB_MSB | (uint8_t)(st & 0x0F);
  if (sys_outb(TIMER_CTRL, control_world) != OK){
    printf("Error in function sys_out: set controller new control word!\n");
    return 1;
  }

  // Load timer’s register with the value of the divisor to
  // generate the frequency corresponding to the desired rate
  uint16_t val = TIMER_FREQ / freq ; 
  uint8_t byte;
  
  // update LSB byte in the port of the timer -> 'sys_outb'
  int success = util_get_LSB(val, &byte);
  if (sys_outb(port, byte) != OK){
    printf("Error in function util_sys_inb: load timer's register with the LSB!\n");
    return 1;
  }

  // update MSB byte in the port of the timer -> 'sys_outb'
  success = util_get_MSB(val, &byte);
  if (sys_outb(port, byte) != OK){
    printf("Error in function util_sys_inb: load timer's register with the MSB!\n");
    return 1;
  }
  
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = timer_hook_id; 
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id) != OK){
    printf("Error subscribing mouse interruptions!\n");
    return 1;
  }
  return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&timer_hook_id) != OK){
    printf("Error unsubscribing mouse interruptions!\n");
    return 1;
  }
  return 0;
}

void (timer_int_handler)() {
  // increment a global timer_counter variable
  timer_counter++;
}

//Constroi um read-back command
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  //Irá criar o read back command de acordo com o timer selcionado
  uint8_t rbcommand = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  
  //Irá guardar o registo relativo ao timer selecionado
  int timer_register;
  if(timer == 0)
    timer_register = TIMER_0;
  else if (timer == 1)
    timer_register = TIMER_1;
  else
    timer_register = TIMER_2;

  //Escreve o read back command no registo de controlo e valor de retorno = 0 se for bem sucedido
  if (sys_outb(TIMER_CTRL, rbcommand) != OK){
    printf("Error when calling the function sys_outb! set controller a read back command.\n");
    return 1;
  }

  //Obtém o estado, para st, do timer pretendido e valor de retorno = 0 se for bem sucedido
  if (util_sys_inb(timer_register, st) != OK){
    printf("Error when calling the function util_sys_inb!\n");
    return 1;
  }
  
  //Se as 2 funções anteriores forem bem sucedidas, retorna 0
  return 0;
}

// Recebe o timer, o status e o field, as opções que passamos
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

  union timer_status_field_val val;
  uint8_t st_copy = st;

  // atualizar os campos da union de acordo com o 'field' que queremos apresentar 
  switch (field) {
    case 0:
    {
      val.byte = st_copy;
      break;
    }
    case 1:
    {
        // deslocar 'field' correspondente para as posições menos significativas
        int left = 2, right = 6;
        st_copy = (uint8_t)(st << left) >> right;
        val.in_mode = st_copy;
        break;
    }
    case 2:
    {
        int left = 4, right = 5;
        st_copy = (uint8_t)(st << left) >> right;

        // tratar casos de x10 e x11
        if (6 == st_copy) st_copy = 2;
        else if (7 == st_copy) st_copy = 3;

        val.count_mode = st_copy;
        break;
    }
    case 3:
    {
        int left = 7, right = 6;
        st_copy = (uint8_t)(st << left) >> right;
        val.bcd = st_copy;
        break; 
    }
  }

  // retorna 0 se bem sucedida
  return timer_print_config(timer, field, val);
}
