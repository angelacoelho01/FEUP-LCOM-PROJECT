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

int (map_memory)();

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

void (get_color)(uint32_t* color, uint32_t first, uint16_t row, uint16_t col, uint8_t no_rectangles, uint8_t step);

void (get_size)(uint8_t no_rectangles, uint16_t* width, uint16_t* height);

int (draw_pixmap)(uint16_t xi, uint16_t yi);

int (sprite)(uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int32_t* length);

void (movement_sprite)(uint16_t *pos, uint16_t posf, int16_t speed, int32_t* length);

int (get_controller_info)(vg_vbe_contr_info_t *controller_info);

#endif
