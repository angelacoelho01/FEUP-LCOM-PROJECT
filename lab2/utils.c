#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  // se new value = 1234 = 0x04D2
  // entao LSB = 0xD2
  // e MSB = 0x04

  // get the lsb with a bitwise operation
  (*lsb) = (uint8_t) (0x00FF & val);
  printf("%x\n", *lsb); // to test purposes
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  (*msb) = (uint8_t) ((uint16_t)(0xFF00 & val) >> 8);
  printf("%x\n", *msb); // to test purposes
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {

  uint32_t temp;
  //O estado do timer irá ser guardado no endereço &temp
  int result = sys_inb(port, &temp);
  *value = (uint8_t) temp;
  
  //Se result = 0 é porque foi bem sucedida
  return result;

}
