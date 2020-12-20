#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../macros/player_macros.h"

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct Player{
  char _name[MAX_SIZE_NAME];
  unsigned int _score;
};

unsigned int (player_calculate_score)(uint8_t minutes, uint8_t seconds, uint8_t no_lives);

int (player_compare)(const void* p1, const void* p2);

void (player_sort)(struct Player players[], size_t no_players);

#endif
