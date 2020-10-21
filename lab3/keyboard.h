#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

/**
 *@brief Reads the status register and the output buffer (OB).
 *       If there was some error, the byte read from the OB should be discarded.
 *
 *@param
 *
 *@return
 */
void (kbc_ih)();

int(keyboard_subscribe_int)(uint8_t *bit_no);

int(keyboard_unsubscribe_int)();

#endif /* __KEYBOARD_H */
