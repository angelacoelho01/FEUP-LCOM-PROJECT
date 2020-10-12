#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  
 /* int left = 8, right = 8;

  uint8_t val_lsb = (val << left) >> right;
  uint8_t test = val_lsb & val;

  if(test == val_lsb)
  {
    *lsb = val_lsb;
    return 0;
  }

  return 1;*/
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  
  /*int right = 8;

  uint8_t val_msb = val >> right;*/

  
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
