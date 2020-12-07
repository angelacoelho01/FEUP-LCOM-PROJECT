#ifndef __GAME_H
#define __GAME_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "../video/video.h"

int (start_video_mode)(uint16_t mode);

int (draw_scenario)(uint16_t mode);

int (return_to_text_mode)();

// the plataform is a xpm (there are plataform with different widht - chosen accordly to the time that has already passed)
int (draw_plataform)(uint16_t mode, xpm_map_t xpm, uint16_t x, uint16_t y);

void (draw_blocks)();

#endif /* __GAME_H */
