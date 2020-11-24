#ifndef _VIDEO_H
#define _VIDEO_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "video_macros.h"

int (video_set_graphic_mode)(uint16_t mode);

int(video_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p);

#endif
