#ifndef _XPM_H
#define _XPM_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include <stdint.h>

#include "../../xpm/block.h"
#include "../../xpm/heart.h"
#include "../../xpm/plataform.h"

static xpm_map_t blocks[] = {
  blue_block_xpm,
  green_block_xpm,
  orange_block_xpm,
  yellow_block_xpm,
  red_block_xpm,
  purple_block_xpm,
  pink_block_xpm};

static xpm_map_t plataforms[] = {
  plataform_initial,
  plataform_mid1,
  plataform_mid2,
  plataform_mid3,
  plataform_final};

#endif
