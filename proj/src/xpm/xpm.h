#ifndef _XPM_H
#define _XPM_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Game scenario xpms.
 **/ 
#include "ball.h"
#include "block.h"
#include "heart.h"
#include "labels.h"
#include "number_blue.h"
#include "number_gray.h"
#include "plataform.h"

/**
 * @brief Menus buttons xpms.
 **/ 
#include "menus/button_1v1.h"
#include "menus/button_exit.h"
#include "menus/button_solo.h"
#include "menus/button_continue.h"
#include "menus/button_leaderboard.h"
#include "menus/button_reset.h"
#include "menus/button_back.h"

/**
 * @brief Menus titles xpms.
 **/ 
#include "menus/game_title.h"
#include "menus/pause_title.h"

/**
 * @brief Mouse cursors.
 **/
#include "menus/mouse_cursor.h"


static xpm_map_t blocks[] = {
  blue_block_xpm,
  green_block_xpm,
  orange_block_xpm,
  yellow_block_xpm,
  red_block_xpm,
  purple_block_xpm,
  pink_block_xpm
};

static xpm_map_t plataforms[] = {
  plataform_initial,
  plataform_mid1,
  plataform_mid2,
  plataform_mid3,
  plataform_final
};

static xpm_map_t numbers[] = {
  number_0,
  number_1,
  number_2,
  number_3,
  number_4,
  number_5,
  number_6,
  number_7,
  number_8,
  number_9
};

static xpm_map_t numbers_blue[] = {
  number_blue_0,
  number_blue_1,
  number_blue_2,
  number_blue_3,
  number_blue_4,
  number_blue_5,
  number_blue_6,
  number_blue_7,
  number_blue_8,
  number_blue_9
};

static xpm_map_t hearts[] = {
  heart_big,
  heart_small
};

static xpm_map_t labels[] = {
  game_over_label,
  winner_label,
  score_label
};

static xpm_map_t start_menu_titles[] = {
  game_title_left,
  game_title_middle_left,
  game_title_middle_right,
  game_title_right
};

static xpm_map_t pause_menu_titles[] = {
  pause_title_left,
  pause_title_right
};

static xpm_map_t menu_buttons[] = {
  button_1v1,
  button_leaderboard,
  button_solo,
  button_exit,
  button_continue,
  button_reset,
  button_back
};

static xpm_map_t menu_buttons_over[] = {
  button_1v1_over,
  button_leaderboard_over,
  button_solo_over,
  button_exit_over,
  button_continue_over,
  button_reset_over,
  button_back_over
};

#endif
