#ifndef __GAME_H
#define __GAME_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "../video/video.h"

int (draw_scenario)(uint16_t mode);

// the plataform is a xpm (there are plataform with different widht - chosen accordly to the time that has already passed)
int (draw_plataform)(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif /* __GAME_H */
