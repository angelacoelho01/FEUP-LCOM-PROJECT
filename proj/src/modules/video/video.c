#include "video.h"

vbe_mode_info_t mode_conf;
//Process (virtual) address to which VRAM is mapped
static void* video_mem;
//Horizontal resolution in pixels
static unsigned h_res;
//Vertical resolution in pixels
static unsigned v_res;
//Number of VRAM bits per pixel
unsigned bits_per_pixel;

enum xpm_image_type xpm_type;
xpm_image_t xpm_image;

//Initializes the vbe_mode_info_t with the input VBE mode, including
//screens dimensions, color depth and VRAM physical address
 int(video_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p) {
    //Get the size of a vbe_mode_info_t variable
    uint32_t size = sizeof(vbe_mode_info_t);

    //Creates a struct that keeps info regardin the mapping of physical memory to virtual memory
    mmap_t address;

    //Allocates a memory block in the region up to the 1MByte physical address with the size of a
    //vbe_mode_info_t vairble and initializes the input mmap_t struct with the mapping information
    lm_alloc(size,&address);

    struct reg86 r;  
    //Starts an address of memory startign in reg, filled with 0 and with the size of the struct reg 
    memset(&r, 0, sizeof(r));  

    //Set a segment base
    r.es = PB2BASE(address.phys);    
    //Set the offset accordingly
    r.di = PB2OFF(address.phys);

    //VBE get mode info
    r.ax = VBE_GET_MODE_INFO;  
    //The mode number        
    r.cx = mode; 
            
    //BIOS videos servic
    r.intno = BIOS_SERVICE_VIDEO;
    //Gets the virtual address
    memcpy(vmi_p, address.virt, sizeof(vbe_mode_info_t));
    //Frees the allocated memory
    lm_free(&address);

    h_res = mode_conf.XResolution;
    v_res = mode_conf.YResolution;
    bits_per_pixel = mode_conf.BitsPerPixel;

    return 0;
}

int (map_memory)() {
    int r;
    //Physical memory range
    struct minix_mem_range mr;
    //VRAM's physical address
    unsigned int vram_base = mode_conf.PhysBasePtr;  
    //VRAM'S size
    unsigned int vram_size = (h_res * v_res * bits_per_pixel)/8; 
    //void *video_mem;

    //Allow memory mapping
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK){
        printf("sys_privctl (ADD_MEM) failed: %d\n", r);
        return 1;
    }

    //Map memory
    video_mem = vm_map_phys(SELF, (void*)mr.mr_base, vram_size);

    if(video_mem == MAP_FAILED){
        printf("couldn't map video memory.\n");
        return 1;
    }

    return 0;
}

int (video_set_graphic_mode)(uint16_t mode) {
    reg86_t r;
    //Zero the struct
    memset(&r, 0, sizeof(r));	
    //VBE call, function 02, sets the VBE mode
    r.ax = VBE_SET_MODE;
    //Set bit 14: linear framebuffer?
    r.bx = 1<<14 | mode;
    //BIOS video services
    r.intno = BIOS_SERVICE_VIDEO;
    //Make the BIOS call and checks it
    if(sys_int86(&r) != OK){
        printf("set_graph_mode: sys_int86() failed\n");
        return 1;
    }
    return 0;
}

uint8_t (get_bytes_size)(uint8_t bits) {
    return (uint8_t)(bits / BYTE_SIZE) +  (bits % BYTE_SIZE ? 1 : 0);
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    char* ptr = video_mem;
    uint8_t pixel_size = get_bytes_size(bits_per_pixel);

    uint32_t y_coord = y * h_res * pixel_size;
    uint32_t x_coord = x * pixel_size;
    memcpy(ptr + y_coord + x_coord, &color, pixel_size);

    return 0;

}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {  
    for(uint32_t i = 0; i < len; i++){
       if(vg_draw_pixel(x+i, y, color) != OK) return 1;
    }
    return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

    //Checks if the y position is valid
    if(y >= v_res){
        printf("Y is an invalid position!\n");
        return 1;
    }
    //Checks if the x position is valid
    if(x >= h_res){
        printf("X is an invalid position!\n");
        return 1;
    }
    //Checks if the height is valid according to the y position
    if((y + height) > v_res){
        printf("Invalid height value according to the y (%d) position!\n", y);
        height = (mode_conf.YResolution - y - 1);
    }
    //Checks if the width is valid according to the x position
    if((x + width) > h_res){
        printf("Invalid width value according to the x (%d) position!\n", x);
        width = (mode_conf.XResolution - x - 1);
    }

    for(uint32_t line = 0 ; line != height; line++)
        if(vg_draw_hline(x, y+line, width, color) != OK) return 1;
    return 0;
 }

int (vg_load_xpm)(xpm_map_t xpm) {
  //Loads the xpm
  uint8_t *address;
  if((address = xpm_load(xpm, xpm_type, &xpm_image)) == NULL){
    return 1;
  }

  return 0;
}

int (vg_draw_pixmap)(uint16_t xi, uint16_t yi) {
     //Checks if the y position is valid
    if(yi >= v_res){
        printf("Y is an invalid position!\n");
        return 1;
    }
    //Checks if the x position is valid
    if(xi >= h_res){
        printf("X is an invalid position!\n");
        return 1;
    }
    uint16_t y = yi, x = xi;
    for(size_t i = 0; i < xpm_image.size; i++){
        if((x - xi) == xpm_image.width){
            x = xi;
            y++;
            //printf("\n");
        }
        if(vg_draw_pixel(x, y, xpm_image.bytes[i]) != OK) return 1;
        x++;
    }

    return 0;
}

//Gets the new color to draw in the matrix
void (get_color)(uint32_t* color, uint32_t first, uint16_t row, uint16_t col, uint8_t no_rectangles, uint8_t step) {
    //Indexed color mode
    if(mode_conf.MemoryModel == INDEXED_COLOR_MODE) 
        *color = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
    //Direct color mode
    else if(mode_conf.MemoryModel == DIRECT_COLOR_MODE){
        uint32_t red=(((first>>mode_conf.RedFieldPosition) & COLOR_BIT_MASK)+ col * step) % (1 << mode_conf.RedMaskSize);
	    uint32_t green = (((first>>mode_conf.GreenFieldPosition ) & COLOR_BIT_MASK)+ row * step) % (1 << mode_conf.GreenMaskSize);
	    uint32_t blue = (((first<<mode_conf.BlueFieldPosition) & COLOR_BIT_MASK)+ (col + row) * step) % (1 << mode_conf.BlueMaskSize);	
        *color =((red << mode_conf.RedFieldPosition )| (green << mode_conf.GreenFieldPosition)|blue);
    }
}

//Gets the possible size to each rectangle according to the mode resolution
void (get_rectangles_size)(uint8_t no_rectangles, uint16_t* width, uint16_t* height) {
    *width = h_res/no_rectangles;
    *height = v_res/no_rectangles;
}

int (sprite)(uint16_t* x, uint16_t* y, uint16_t xf, uint16_t yf, int16_t speed, int32_t* length) {
    /*if(*y == yf){ // horizontal movement - along x
        //While x doesn't reach the final position
        if(xf > *x) *x += speed;
        //If x has already reached the final position or it's greater 
        else *x -= speed;
        //Length decreases at the same time that x increases
        *length -= speed;
        //In case it has already passed the final position
        if(*length < 0) *x = xf;
    }
    else if(*x == xf){ //Vertical movement - along y
        //While y doesn't reach the final position
        if(yf > *y) *y += speed;
        //If y has already reached the final position or it's greater
        else *y -= speed;
        //Length decreases at the same time that y increases
        *length -= speed;
        //In case it has already passed the final position
        if(*length < 0) *y = yf;
    }*/
    if(*y == yf) // horizontal movement - along x
        movement_sprite(x, xf, speed, length);
    else if(*x == xf) //Vertical movement - along y
        movement_sprite(y, yf, speed, length);

    vg_draw_rectangle(0, 0, h_res, v_res, 0);
    if(vg_draw_pixmap(*x, *y) != OK) return 1;
    return 0;
}

void (movement_sprite)(uint16_t *pos, uint16_t posf, int16_t speed, int32_t* length) {
    //While pos doesn't reach the final position
    if(posf > *pos) *pos += speed;
    //If pos has already reached the final position or it's greater 
    else *pos -= speed;
    //Length decreases at the same time that pos increases
    *length -= speed;
    //In case it has already passed the final position
    if(*length < 0) *pos = posf;
}
