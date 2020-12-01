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

int (kbc_read_status_reg)(uint8_t *status);

int (kbc_issue_cmd)(uint8_t cmd);

int (kbc_read_reg)(uint8_t *data);

int (kbc_write_reg)(uint8_t data);

int (kbc_enable_int)();

int (kbc_poll_handler)();

int (reset_kbc_status)();

#endif /* __KEYBOARD_H */
