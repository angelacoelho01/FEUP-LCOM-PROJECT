#include "player.h"

#include <stdlib.h>

unsigned int (player_calculate_score)(uint8_t minutes, uint8_t seconds, uint8_t no_lives){
  if(minutes >= 5) return 250;
  else return (3500 - (minutes * 5000) - (seconds * 1000) - (3 * no_lives) * 250);
}

int (player_compare)(const void* p1, const void* p2){
  const struct Player player1 = *(const struct Player*)p1, player2 = *(const struct Player*)p2;
  return ((int)(player1._score) - (int)(player2._score));
}

void (player_sort)(struct Player players[], size_t no_players){
  qsort(players, no_players, sizeof(struct Player), player_compare);
}
