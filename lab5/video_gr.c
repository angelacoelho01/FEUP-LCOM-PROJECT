#include "video_gr.h"

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    reg86_t r;

    r.al = 0x0C;
    r.al = color;
    for(unsigned int i = 0; i != len; i++){
        r.cx = x + i;
        x = r.cx;
        r.dx = y + i;
        y = r.dx;
    }

    if(sys_int86(&r) != OK) return 1;
    return 0;
}



    /*int r;
    //Physical memory range
    struct minix_mem_range mr;
    //VRAM's physical address
    unsigned int vram_base;
    //VRAM'S size
    unsigned int vram_size;

    void *video_mem;

    //Allow memory mapping
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK)
        printf("sys_privctl (ADD_MEM) failed: %d\n", r);

    //Map memory
    video_mem = vm_map_phsy(SELF, (void*)mr.m_basem, vram_size);

    if(video_mem == MAP_FAILED)
        printf("couldn't map video memory.\n");*/
