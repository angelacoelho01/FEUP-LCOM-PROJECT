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

int timer_hook_id = 0; // Diferenciar instruções usando bit masks diferentes para os hook_id
int kbc_hook_id = 1; // inicializado com qualquer valor entre 0..7

int (keyboard_subscribe_int)(uint8_t *bit_no) {

  *bit_no = kbc_hook_id; 
  // KBC interrupt subscription in exclusive mode
  if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_hook_id) != OK){
    printf("ERROR in subcribe_int: sys_irqsetpolicy!!\n");
    return 1;
  }

  return 0;
}

int (keyboard_unsubscribe_int)() {

  if (sys_irqrmpolicy(&kbc_hook_id) != OK){
    printf("ERROR in unsubcribe_int: iqrmpolicy!\n");
    return 1;
  }

  return 0;
}

int (kbc_read_status_reg)(uint8_t *status){
  if (util_sys_inb(KBC_ST_REG, status) != OK){
    printf("Error when reading status register");
    return 1;
  }

  return 0;
}

int (kbc_issue_cmd)(uint8_t cmd){
  uint8_t status;
  while( 1 ) {
    if (kbc_read_status_reg(&status) == OK){
      if( (status & KBC_IBF) == 0 ) { // is empty - we can write
        if(sys_outb(KBC_CMD_REG, cmd) == OK){ // escreve um comando em registo 0x64
          return 0;
        }else{
          printf("Error in writing a command");
        }
      }else{
        printf("INPUT BUFFER IS FULL, WE CANNOT WRITE");
      }
      tickdelay(micros_to_ticks(WAIT_KBC));
    }
  }
  return 1;
}

int (kbc_read_reg)(uint8_t *data){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    if((status & KBC_OBF) == 1){ // Output buffer full - data available for reading
      if(util_sys_inb(OUT_BUF_REG, data) == OK){ // lê do registo 0x60 - return value
        return 0;
      }
    }else{
      printf("Data not available for reading");
    }
  }

  return 1;
}

int (kbc_write_reg)(uint8_t data){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    if((status & KBC_IBF) == 0){ // Input buffer empty - we can write
      if(sys_outb(IN_BUF_REG, data) == OK){ // escreve em 0x60 o novo valor - argumento
        return 0;
      }
    }else {
      printf("We cannot write - input buffer full");
    }
  }
  
  return 1;
}

int (kbc_enable_int)() {
  uint8_t cmd_byte;
  // read the command byte 
  // Read Use KBC command 0x20, which must be written to 0x64
  if(kbc_issue_cmd(READ_COMD_BYTE) != OK){ return 1; }
  // the value of the “command byte” must be read from 0x60 - return value
  if(kbc_read_reg(&cmd_byte) != OK){ return 1; }
  
  // write_new cmd_byte to enable interrupts
  cmd_byte = cmd_byte | KBC_ENABLE_INT ; // ativar bit 0, manter o restante
  // Write Use KBC command 0x60, which must be written to 0x64 
  if(kbc_issue_cmd(WRITE_CMD_BYTE) != OK){ return 1; }
  // new value of the “command byte” must be written to 0x60 - argument
  if(kbc_write_reg(cmd_byte) != OK){ return 1; }
  
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
