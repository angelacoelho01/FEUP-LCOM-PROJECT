 #pragma once
  
 #include <stdint.h>
  
 // #include "vbe.h"

 void *(vg_init)(uint16_t mode);
  
 int (vg_exit)(void);
  
 int (vg_display_vbe_contr_info)(struct vg_vbe_contr_info *info_p);
