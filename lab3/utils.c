#include <lcom/lcf.h>

#include <stdint.h>


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
