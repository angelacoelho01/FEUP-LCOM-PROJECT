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
  //Starts an address of memory startign in reg, filled with 0 and with the size of the struct reg 
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
  //*vmi_p =*(vbe_mode_info_t*)adress.virt;
  memcpy(vmi_p, adress.virt, sizeof(vbe_mode_info_t));
  //Frees the allocated memory
  lm_free(&adress);
  return 0;
}

uint8_t calculate_size_in_bytes(uint8_t bits) {
    return (uint8_t)(bits / BYTE_SIZE) +  (bits % BYTE_SIZE ? 1 : 0);
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){  
    int r;
    //Physical memory range
    struct minix_mem_range mr;
    //VRAM's physical address
    unsigned int vram_base = mode_conf.PhysBasePtr;  
    //VRAM'S size
    unsigned int vram_size = (mode_conf.XResolution * mode_conf.YResolution * mode_conf.BitsPerPixel)/8; 
    void *video_mem;

    //Allow memory mapping
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK)
        printf("sys_privctl (ADD_MEM) failed: %d\n", r);

    //Map memory
    video_mem = vm_map_phys(SELF, (void*)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED)
        printf("couldn't map video memory.\n");

    uint8_t* ptr;
    ptr = video_mem;

    //In case it is the indexed color mode, pixel_size = 1
    uint8_t pixel_size = calculate_size_in_bytes(mode_conf.BitsPerPixel);

    for (uint32_t i = 0; i < len; i++){
        uint32_t y_coord = y * mode_conf.XResolution * pixel_size;
        uint32_t x_coord = (x + i) * pixel_size;
        memcpy(ptr + y_coord + x_coord, &color, pixel_size);
    }

    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
    for(uint32_t line = 0 ; line != height; line++)
        if(vg_draw_hline(x, y+line, width, color) != OK) return 1;
    return 0;
 }

