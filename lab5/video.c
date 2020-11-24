#include "video.h"

vbe_mode_info_t mode_conf;

//NOTE THAT: reg86_t == struct reg86


int (video_set_graphic_mode)(uint16_t mode){
    reg86_t reg;
    //Zero the struct
    memset(&reg, 0, sizeof(reg));	
    //VBE call, function 02, sets the VBE mode
    reg.ax = VBE_SET_MODE;
    //Set bit 14: linear framebuffer?
    reg.bx = 1<<14 | mode;
    //BIOS video services
    reg.intno = BIOS_SERVICE_VIDEO;
    //Make the BIOS call and checks it
    if(sys_int86(&reg) != OK){
        printf("set_graph_mode: sys_int86() failed\n");
        return 1;
    }
    return 0;
}

//Initializes the vbe_mode_info_t with the input VBE mode, including
//screens dimensions, color depth and VRAM physical address
 int(video_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p){
  //Get the size of a vbe_mode_info_t variable
  uint32_t size=sizeof(vbe_mode_info_t);

  //Creates a struct that keeps info regardin the mapping of physical memory to virtual memory
  mmap_t adress;

  //Allocates a memory block in the region up to the 1MByte physical address with the size of a
  //vbe_mode_info_t vairble and initializes the input mmap_t struct with the mapping information
  lm_alloc(size,&adress);

  struct reg86 reg;  
  //Starts an address of memory startin in reg, filled with 0 and with the size of the struct reg 
  memset(&reg, 0, sizeof(reg));  
  //VBE get mode info
  reg.ax = VBE_GET_MODE_INFO;  
  //The mode number        
  reg.cx = mode;
  //Set a segment base?
  reg.es = PB2BASE(adress.phys);    
  //Set the offset accordingly
  reg.di = PB2OFF(adress.phys);            
  //BIOS videos servic
  reg.intno = BIOS_SERVICE_VIDEO;
  //Gets the virtual address
  *vmi_p =*(vbe_mode_info_t*)adress.virt;
  //Frees the allocated memory
  lm_free(&adress);
  return 0;
}

