#ifndef _LCOM_VIDEO_H
#define _LCOM_VIDEO_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "../macros/bios_vbe.h"

#include "video_gr.h"
#include "xpm.h"

void (video_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);

int (map_memory)();

int (video_set_graphic_mode)(uint16_t mode);

void (set_mode_settings)(uint16_t mode);

int (start_video_mode)(uint16_t mode);

int (return_to_text_mode)();

uint8_t (get_bytes_size)(uint8_t bits);

int (get_xpm_image_type)(uint16_t mode);

void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

void (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

void (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

int (video_load_xpm)(xpm_map_t xpm);

void (video_draw_pixmap)(uint16_t xi, uint16_t yi);

void (movement_sprite)(uint16_t *pos, uint16_t posf, int16_t speed, int32_t* length);


#endif /* _LCOM_VIDEO_H */
