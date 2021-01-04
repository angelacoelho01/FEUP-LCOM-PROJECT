#include "load_xpms.h"

void (load_all_xpms)(){

  // Load ball xpm
  ball_xpm.bytes = xpm_load(ball, XPM_8_8_8, &ball_xpm);

  // Load blocks xpms
  for(unsigned i = 0; i < NO_BLOCKS; i++)
    blocks_xpms[i].bytes = xpm_load(blocks[i], XPM_8_8_8, &blocks_xpms[i]);

  // Load pltaforms xpms
  for(unsigned i = 0; i < NO_PLATAFORMS; i++)
    plataforms_xpms[i].bytes = xpm_load(plataforms[i], XPM_8_8_8, &plataforms_xpms[i]);

  // Load gray numbers xpms
  for(unsigned i = 0; i < NO_NUMBERS; i++)
    numbers_gray_xpms[i].bytes = xpm_load(numbers[i], XPM_8_8_8, &numbers_gray_xpms[i]);

  // Load blue numbers xpms
  for(unsigned i = 0; i < NO_NUMBERS; i++)
    numbers_blue_xpms[i].bytes = xpm_load(numbers_blue[i], XPM_8_8_8, &numbers_blue_xpms[i]);

  // Load hearts xpms
  for(unsigned i = 0; i < NO_HEARTS; i++)
    hearts_xpms[i].bytes = xpm_load(hearts[i], XPM_8_8_8, &hearts_xpms[i]);

  // Load labels xpms
  for(unsigned i = 0; i < NO_LABELS; i++)
    labels_xpms[i].bytes = xpm_load(labels[i], XPM_8_8_8, &labels_xpms[i]);

  // Load start menu title (divided in 4 parts)
  for(unsigned i = 0; i < NO_START_MENU_TITLES; i++)
    start_menu_titles_xpms[i].bytes = xpm_load(start_menu_titles[i], XPM_8_8_8, &start_menu_titles_xpms[i]);

  // Load pause menu title (divided in 2 parts)
  for(unsigned i = 0; i < NO_PAUSE_MENU_TITLES; i++)
    pause_menu_titles_xpms[i].bytes = xpm_load(pause_menu_titles[i], XPM_8_8_8, &pause_menu_titles_xpms[i]);

  // Load menu buttons
  for(unsigned i = 0; i < NO_MENU_BUTTONS; i++)
    menu_buttons_xpms[i].bytes = xpm_load(menu_buttons[i], XPM_8_8_8, &menu_buttons_xpms[i]);

  // Load menu buttons over
  for(unsigned i = 0; i < NO_MENU_BUTTONS; i++)
    menu_buttons_over_xpms[i].bytes = xpm_load(menu_buttons_over[i], XPM_8_8_8, &menu_buttons_over_xpms[i]);

  // Load mouse cursor normal
  mouse_cursor_normal_xpm.bytes = xpm_load(mouse_cursor_normal, XPM_8_8_8, &mouse_cursor_normal_xpm);

  // Load mouse cursor pointer
  mouse_cursor_pointer_xpm.bytes = xpm_load(mouse_cursor_pointer, XPM_8_8_8, &mouse_cursor_pointer_xpm);
}
