#include "video.h"

vbe_mode_info_t mode_conf;


int (video_set_graph_mode)(uint16_t mode){
    reg86_t reg;

    memset(&reg, 0, sizeof(reg));	/* zero the structure */
    reg.ax = 0x4f02;
    reg.bx = 1<<14 | mode;
    reg.intno = 0x10;
    if(sys_int86(&reg) != OK){
        printf("set_graph_mode: sys_int86() failed\n");
        return 1;
    }
    return 0;
}

int (video_get_mode_conf)(uint16_t mode, vbe_mode_info_t* mode_conf){
  uint32_t size=sizeof(vbe_mode_info_t);

  mmap_t adress;
  lm_alloc(size,&adress);

  struct reg86 reg;  
  memset(&reg,0,sizeof(reg));  
  reg.ax = 0x4F01;          
  reg.cx = mode;
  reg.es = PB2BASE(adress.phys);    
  reg.di = PB2OFF(adress.phys);            
  reg.intno = 0x10;
  *mode_conf =*(vbe_mode_info_t*)adress.virt;
  lm_free(&adress);
  return 0;
}

