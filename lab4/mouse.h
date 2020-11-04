#ifndef __MOUSE_H
#define __MOUSE_H

#include <stdbool.h>
#include <stdint.h>

int (kbc_read_status_reg)(uint8_t *status);

void (mouse_ih)();

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (kbc_issue_cmd)(uint8_t cmd);

int (kbc_read_reg)(uint8_t *data);

int (kbc_write_reg)(uint8_t data);

int (mouse_enable_data_report)();

int (mouse_disable_data_reporting)();

int (reset_mouse_status)();

int (get_packet)(uint8_t byte, uint8_t *num_bytes, struct packet *pp);

#endif /* __MOUSE_H */
