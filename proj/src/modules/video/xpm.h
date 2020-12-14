#ifndef _XPM_H
#define _XPM_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>

#include "../../xpm/block.h"
#include "../../xpm/plataform.h"
#include "../../xpm/ball.h"
#include "../../xpm/number_gray.h"
#include "../../xpm/number_blue.h"
#include "../../xpm/heart.h"

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
  heart_mini
};

#endif
