#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"
int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t temp;
  // O estado do timer irá ser guardado no endereço &temp
  if (sys_inb(port, &temp) != OK){
    printf("Error when calling sys_inb!\n");
    return 1;
  }

  *value = (uint8_t) temp;
  
  return 0;
}

void(kbc_ih)(){
    uint8_t stat;
    uint8_t scancode;
    util_sys_inb(KBC_ST_REG, &stat);
    if(stat & KBC_PAR_ERR)
        printf("Parity error - invalid data\n");
    else if(stat & KBC_TO_ERR)
        printf("Timeout error - invalid data\n");
    else
        util_sys_inb(OUT_BUF_REG, &scancode);
}

/*int kbd_print_scancode(bool make, uint8_t size, uint8_t bytes[]){
    
    if(make){
        printf("Makecode: ");
    }
    else{
        printf("BreakCode: ");
    }
    for(uint8_t i = 0; i < size; i++){
        printf("0%x ", bytes[i]);
    }
    return 0;
}*/


/*int hook_id = 0; // inicializado com qualquer valor entre 0..7

int (keyboard_subscribe_int)(uint8_t *bit_no) {

  bit_no = hook_id; 
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
}*/

