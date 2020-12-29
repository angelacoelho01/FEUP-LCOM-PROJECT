#include "player.h"

#include <stdlib.h>

void (print_players)(){
  for(unsigned i = 0; i < playerManager.no_players; i++)
    printf("%s %d\n", playerManager.players[i].name, playerManager.players[i].score);
}

unsigned int (calculate_player_score)(uint8_t minutes, uint8_t seconds, uint8_t no_lives){
  if(minutes >= 5) return (unsigned int)250;
  else return (unsigned int)(35000 - (minutes * 5000) - (seconds * 1000) - (3 - no_lives) * 250);
}

int (compare_players)(const void* p1, const void* p2){
  const struct Player player1 = *(const struct Player*)p1, player2 = *(const struct Player*)p2;
  return ((int)(player2.score) - (int)(player1.score));
}

void (sort_players)(){
  qsort(playerManager.players, playerManager.no_players, sizeof(struct Player), compare_players);
}

int (find_player)(const struct Player* player){
  for(unsigned i = 0; i < playerManager.no_players; i++){
    if(compare_players(&playerManager.players[i], player) == 0) 
      return i;
  }
  return -1;
}

struct Player (add_player)(char name[], unsigned score){
  struct Player new_player;
  new_player.score = score;
  strncpy(new_player.name, name, MAX_SIZE_PLAYER_NAME-1);
  playerManager.players[playerManager.no_players++] = new_player;
  return new_player;
}

void (set_player_score)(unsigned score, struct Player* player){
  player->score = score;
}

int (remove_player)(struct Player* player){
  int player_index = find_player(player);
  if(player_index == -1) return 1;
  for(unsigned i = player_index; i < playerManager.no_players; i++)
    playerManager.players[i] = playerManager.players[i+1];
  playerManager.no_players--;
  free((void*)player);
  return 0;
}

void (get_players_info)(char* line, size_t len){
  bool isName = true;
  size_t count = 0;
  char name[len], score[len];
  memset(&name, 0, sizeof(name));
  memset(&score, 0, sizeof(score));
  for(unsigned i = 0; i < len; i++){
    if(isName){
      if(line[i] == '-') name[count++] = ' ';
      else if(line[i] != ' ') name[count++] = line[i];
      else if(line[i] == ' '){
        isName = false;
        count = 0;
      }
    }
    else score[count++] = line[i];
  }
  add_player(name, atoi(score));
}

void (prepare_string)(char str[]){
  for(size_t i = 0; i < MAX_SIZE_PLAYER_NAME; i++)
    if(str[i] == ' ') str[i] = '-';
}

int (write_players)(char path[]){
  FILE* file;
  file = fopen(path, "w");
  if(file == NULL) return 1;
  sort_players();
  for(unsigned i = 0; i < playerManager.no_players; i++){
    char aux[MAX_SIZE_PLAYER_NAME];
    strncpy(aux, playerManager.players[i].name, MAX_SIZE_PLAYER_NAME-1);
    prepare_string(aux);
    fprintf(file, "%s %d\n", aux, playerManager.players[i].score);
  }
  fclose(file);
  return 0;
}

int (read_players)(char path[]){
  FILE* file;
  file = fopen(path, "r");
  if(file == NULL) return 1;
  ssize_t read;
  char* line = NULL;
  size_t len = 0;
  while((read = getline(&line, &len, file)) != -1)
    get_players_info(line, read);
  fclose(file);
  if (line) free(line);
  return 0;
}
