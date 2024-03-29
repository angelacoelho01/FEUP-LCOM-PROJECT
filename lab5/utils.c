#include <lcom/lcf.h>

#include <stdint.h>

#ifdef LAB3
uint32_t cnt = 0;
#endif

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t temp;
  if (sys_inb(port, &temp) != OK){
    printf("Error when calling sys_inb!\n");
    return 1;
  }

  *value = (uint8_t) temp;

  // counting the number of calls of the sys_inb() function
  #ifdef LAB3
  cnt++;
  #endif
  
  return 0;
}
