#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"

char ih_error = 0;
uint8_t scancode;

void(kbc_ih)(){
    uint8_t stat;

    if(util_sys_inb(KBC_ST_REG, &stat) != OK){ // Reads the status register 
      ih_error = 1;
    }else{
      if(stat & KBC_OBF){ // Output buffer full - data available for reading
        if(util_sys_inb(OUT_BUF_REG, &scancode) != OK){ // Read output buffer
            printf("Error.\n");
            ih_error = 1;
        }

        if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0){ // check if there was some error 
          printf("Error - invalid data\n");
          ih_error = 1;
        }else{
          ih_error = 0; // byte read valid
        }
        
      }else{
        ih_error = 1;
      }
    }

}

int hook_id = 1; // inicializado com qualquer valor entre 0..7

int (keyboard_subscribe_int)(uint8_t *bit_no) {

  *bit_no = hook_id; 
  // KBC interrupt subscription in exclusive mode
  if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK){
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

int (kbc_enable_int)(uint8_t *cmd_byte) {
  /*Must enable interrupts by writing command byte before
exiting
I Should read the command byte before to restore it later -> by parametro
*/
return 1;
}

int (kbc_issue_cmd)(uint8_t cmd /*, adaptar para cmd com argumentos*/){
  uint8_t stat;

  if (util_sys_inb(KBC_ST_REG, &stat) != OK){
    return 1;
  }else{
    if( (stat & KBC_IBF) == 0 ) { // is empty - we can write
      sys_outb(KBC_CMD_REG, cmd); /* no args command */
      return 0;
    }else { // Input buffer full - don’t write commands or arguments

      return 1;
    }
  }
}

int (kbc_read_reg)(uint8_t *data){
  return 1;
}

int (kbc_write_reg)(uint8_t data){
  return 1;
}

