#ifndef _VIDEO_H
#define _VIDEO_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

int (video_set_graph_mode)(uint16_t mdode);

int (video_get_mode_conf)(uint16_t mode, vbe_mode_info_t* mode_conf);

#endif
