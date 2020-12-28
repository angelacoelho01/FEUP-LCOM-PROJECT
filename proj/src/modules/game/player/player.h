#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../macros/player_macros.h"

#include <sys/mman.h>
#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_MAX_PLAYERS 50
#define MAX_SIZE_PLAYER_NAME 50

struct Player{
  char name[MAX_SIZE_PLAYER_NAME];
  unsigned int score;
};

struct PlayerManager{
  struct Player players[NO_MAX_PLAYERS];
  unsigned no_players;
}playerManager;

void (print_players)();

unsigned int (calculate_player_score)(uint8_t minutes, uint8_t seconds, uint8_t no_lives);

int (compare_players)(const void* p1, const void* p2);

void (sort_players)();

int (find_player)(const struct Player* player);

struct Player (add_player)(char name[],unsigned score);

void (set_player_score)(unsigned score, struct Player* player);

void (get_players_info)(char* line, size_t len);

int (remove_player)(struct Player* player);

void (prepare_string)(char str[]);

int (write_players)(char path[]);

int (read_players)(char path[]);

#endif
