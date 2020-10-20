#include <lcom/lcf.h>

#include <lcom/keyboard.h>

#include <stdbool.h>
#include <stdint.h>

void (kbc_ih)(void){
    //Read the status register and the outuput buffer
    //If there was some error, the byte read from the OB should be discarded
}