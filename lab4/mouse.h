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

int (reset_kbc_status)();

int (get_packet)(uint8_t byte, uint8_t *num_bytes, struct packet *pp);

int (mouse_set_remote)();

int (mouse_set_stream)();

int(mouse_poll_handler)();

bool(check_draw)(struct mouse_ev *evt, uint8_t x_len, uint8_t tolerance);

#endif /* __MOUSE_H */
