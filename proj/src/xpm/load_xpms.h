#ifndef _LOAD_XPMS_H
#define _LOAD_XPMS_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "xpm.h"

#define NO_BLOCKS 7
#define NO_PLATAFORMS 5
#define NO_NUMBERS 10
#define NO_HEARTS 2
#define NO_LABELS 3
#define NO_START_MENU_TITLES 4
#define NO_PAUSE_MENU_TITLES 2
#define NO_MENU_BUTTONS 6

xpm_image_t ball_xpm;
xpm_image_t blocks_xpms[NO_BLOCKS];
xpm_image_t plataforms_xpms[NO_PLATAFORMS];
xpm_image_t numbers_gray_xpms[NO_NUMBERS];
xpm_image_t numbers_blue_xpms[NO_NUMBERS];
xpm_image_t hearts_xpms[NO_HEARTS];
xpm_image_t labels_xpms[NO_LABELS];
xpm_image_t start_menu_titles_xpms[NO_START_MENU_TITLES];
xpm_image_t pause_menu_titles_xpms[NO_PAUSE_MENU_TITLES];
xpm_image_t menu_buttons_xpms[NO_MENU_BUTTONS];
xpm_image_t menu_buttons_over_xpms[NO_MENU_BUTTONS];
xpm_image_t mouse_cursor_normal_xpm;
xpm_image_t mouse_cursor_pointer_xpm;

void (load_all_xpms)();

#endif
