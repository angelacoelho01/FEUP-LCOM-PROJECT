#ifndef __GAME_H
#define __GAME_H

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>
#include <machine/int86.h>

#include "../macros/block_breaker.h"
#include "../macros/i8042.h"

#include "../keyboard/keyboard.h"
#include "../mouse/mouse.h"
#include "../timer/timer.h"
#include "../video/video.h"
#include "../../utils/utils.h"
#include "../graphics/graphics.h"

static uint16_t plataform_width[] = {
  86, 74, 62, 50, 38
};

int (play_solo_game)(uint16_t mode);

void (start_game)();

bool (move_plataform)();

#endif /* __GAME_H */
