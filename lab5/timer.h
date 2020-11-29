#ifndef _TIMER_H
#define _TIMER_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>

#include "utils.h"
#include "macros.h"

int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

void (timer_int_handler)();

#endif 
