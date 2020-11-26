#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>

#include "utils.h"
#include "macros.h"

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

int (keyboard_check_obf)(uint8_t st);

int (keyboard_read_obf)(uint8_t* st);

int (keyboard_read_status)(uint8_t* st);

int (keyboard_read_scancode)();

#endif
