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

int (kbc_read_status_reg)(uint8_t *status){
  if (util_sys_inb(KBC_ST_REG, status) != OK){
    return 1;
  }

  return 0;
}

int (kbc_issue_cmd)(uint8_t cmd){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    if( (status & KBC_IBF) == 0 ) { // is empty - we can write
      if(sys_outb(KBC_CMD_REG, cmd) == OK){
        return 0;
      }
    } 
  }
  return 1;
}

int (kbc_read_reg)(uint8_t *data){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    if((status & KBC_OBF) == 1){ // Output buffer full - data available for reading
      if(util_sys_inb(OUT_BUF_REG, data) == OK){
        return 0;
      }
    }
  }

  return 1;
}

int (kbc_write_reg)(uint8_t data){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    if((status & KBC_IBF) == 0){ // Input buffer empty - we can write
      if(sys_outb(IN_BUF_REG, data) == OK){
        return 0;
      }
    }
  }
  
  return 1;
}

int (kbc_enable_int)(uint8_t *cmd_byte) {
  // enable interrups - writing an appropriate KBC command byte.
  // read the command byte before to restore it later
  // Read Use KBC command 0x20, which must be written to 0x64
  if(kbc_issue_cmd(READ_COMD_BYTE) != OK){ return 1; }
  // the value of the “command byte” must be read from 0x60
  if(kbc_read_reg(cmd_byte) != OK){ return 1; }
  
  // enable interrupts by writing command byte before exiting
  // write_new cmd_byte to enable interrupts
  uint8_t enable_int_cmd = MOUSE_ENABLE_INT2 | KBC_ENABLE_INT ;
  // new value of the “command byte” must be written to 0x60 - argument
  if(kbc_write_reg(enable_int_cmd) != OK){ return 1; }
  // Write Use KBC command 0x60, which must be written to 0x64 
  if(kbc_issue_cmd(WRITE_CMD_BYTE) != OK){ return 1; }
  
  return 0;
}

int(kbc_poll_handler)(){
  uint8_t stat;

  if(util_sys_inb(KBC_ST_REG, &stat) != OK){ // Reads the status register 
    return 1;
  }else{
    if((stat & KBC_OBF) && (stat & KBC_AUX) == 0){ // Output buffer full - data available for reading
      if(util_sys_inb(OUT_BUF_REG, &scancode) != OK){ // Read output buffer
          printf("Error.\n");
          return 1;
      }

      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0){ // check if there was some error 
        printf("Error - invalid data\n");
        return 1;
      }else{
        return 0; // byte read valid
      }
      
    }else{
      return 1;
    }
  }
}
