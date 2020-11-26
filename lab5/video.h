#ifndef _VIDEO_H
#define _VIDEO_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "macros.h"

int (video_set_graphic_mode)(uint16_t mode);

int(video_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);

uint8_t calculate_size_in_bytes(uint8_t bits);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif
