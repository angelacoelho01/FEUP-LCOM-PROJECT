#pragma once

/** @defgroup utils utils
 * @{
 *
 * LCOM's utility functions
 */

#include <stdint.h>

/**
 * @brief Invokes sys_inb() system call but reads the value into a uint8_t variable.
 *
 * @param port the input port that is to be read
 * @param value address of 8-bit variable to be update with the value read
 * @return Return 0 upon success and non-zero otherwise
 */
int (util_sys_inb)(int port, uint8_t *value);

int(util_get_LSB)(uint16_t val, uint8_t *lsb);

int (util_get_MSB)(uint16_t val, uint8_t *msb);

uint8_t (util_get_no_digits)(unsigned int n);

uint16_t (util_get_lower_left_corner)(uint16_t xi);

uint16_t (util_get_lower_right_corner)(uint16_t xi);

uint16_t (util_get_upper_right_corner)(uint16_t xi);
