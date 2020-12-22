#ifndef _MOUSE_H
#define _MOUSE_H

#include <stdbool.h>
#include <stdint.h>

void (mouse_ih)();

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (mouse_enable_data_report)();

int (mouse_disable_data_reporting)();

int (get_packet)(uint8_t byte, uint8_t *num_bytes, struct packet *pp);

int (mouse_set_remote)();

int (mouse_set_stream)();

int (mouse_poll_handler)();

struct mouse_ev* (mouse_event_detect)(struct packet *p);

bool (check_horizontal_line)(struct mouse_ev *evt, uint8_t tolerance);

#endif /* __MOUSE_H */
