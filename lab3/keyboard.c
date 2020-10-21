#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"


char ih_error = 0;
uint8_t scancode;
uint32_t cnt = 0;

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t temp;
  // O estado do timer irá ser guardado no endereço &temp
  if (sys_inb(port, &temp) != OK){
    printf("Error when calling sys_inb!\n");
    return 1;
  }

  *value = (uint8_t) temp;

  #ifdef LAB3
  cnt++;
  #endif

  return 0;
}

void(kbc_ih)(){
    uint8_t stat;
    if(util_sys_inb(KBC_ST_REG, &stat) == OK){
      if(stat & KBC_OBF){
        if((stat & KBC_TO_ERR) != 0){
          printf("Timeout error - invalid data\n");
          ih_error = 1;
        }
        else if((stat & KBC_PAR_ERR) != 0){
          printf("Parity error - invalid data\n");
          ih_error = 1;
        }
      }
      if(sys_outb(KBC_CMD_REG, READ_COMD_BYTE) != OK)
        printf("Error.\n");
      if(util_sys_inb(OUT_BUF_REG, &scancode) != OK)
        printf("Error.\n");
    }
    else
      ih_error = 1;
}

int hook_id = 0; // inicializado com qualquer valor entre 0..7

int (keyboard_subscribe_int)(uint8_t *bit_no) {

  *bit_no = hook_id; 
  if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id) != OK){
    printf("ERROR in subcribe_int: sys_irqsetpolicy!!\n");
    return 1;
  }

  return 0;
}


int (keyboard_unsubscribe_int)() {

  if (sys_irqrmpolicy(&hook_id) != OK){
    printf("ERROR in unsubcribe_int: iqrmpolicy!\n");
    return 1;
  }

  return 0;
}
