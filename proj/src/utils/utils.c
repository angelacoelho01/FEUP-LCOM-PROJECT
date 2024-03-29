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

int (util_get_LSB)(uint16_t val, uint8_t *lsb) {
  // get the lsb with a bitwise operation
  (*lsb) = (uint8_t) (0x00FF & val);
  return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb) {
  (*msb) = (uint8_t) ((uint16_t)(0xFF00 & val) >> 8);
  return 0;
}

uint8_t (util_get_no_digits)(unsigned int n){
  uint8_t count = 0;
  while(n != 0){
    n /= 10;
    ++count;
  }
  return count;
}
