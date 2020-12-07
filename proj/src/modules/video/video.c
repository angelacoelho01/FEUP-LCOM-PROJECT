#include "video.h"

vbe_mode_info_t mode_conf;
static void *video_mem;
static unsigned h_res;
static unsigned v_res;
unsigned bits_per_pixel;
unsigned bytes_per_pixel;

enum xpm_image_type xpm_type;
xpm_image_t xpm_image;

int(video_get_mode_info)(uint16_t mode, vbe_mode_info_t *vmi_p) {
  uint32_t size = sizeof(vbe_mode_info_t);

  mmap_t address;
  lm_alloc(size, &address);

  struct reg86 r;
  memset(&r, 0, sizeof(r));

  r.es = PB2BASE(address.phys);
  r.di = PB2OFF(address.phys);
  r.ax = VBE_GET_MODE_INFO;
  r.cx = mode;
  r.intno = BIOS_SERVICE_VIDEO;

  memcpy(vmi_p, address.virt, sizeof(vbe_mode_info_t));
  lm_free(&address);

  h_res = mode_conf.XResolution;
  v_res = mode_conf.YResolution;
  bits_per_pixel = mode_conf.BitsPerPixel;
  xpm_type = get_xpm_image_type(mode);
  bytes_per_pixel = get_bytes_size(bits_per_pixel);

  return 0;
}

int(map_memory)() {
  int r;
  struct minix_mem_range mr;
  unsigned int vram_base = mode_conf.PhysBasePtr;
  unsigned int vram_size = (h_res * v_res * bits_per_pixel) / 8;

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if ((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK) {
    printf("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    printf("couldn't map video memory.\n");
    return 1;
  }

  return 0;
}

int(video_set_graphic_mode)(uint16_t mode) {
  reg86_t r;
  memset(&r, 0, sizeof(r));

  r.ax = VBE_SET_MODE;
  r.bx = 1 << 14 | mode;
  r.intno = BIOS_SERVICE_VIDEO;

  if (sys_int86(&r) != OK) {
    printf("set_graph_mode: sys_int86() failed\n");
    return 1;
  }

  return 0;
}

uint8_t(get_bytes_size)(uint8_t bits) {
  return (uint8_t)(bits / BYTE_SIZE) + (bits % BYTE_SIZE ? 1 : 0);
}

int (get_xpm_image_type)(uint16_t mode){
    if(mode == MODE_0) return XPM_INDEXED;
    else if(mode == MODE_1) return XPM_1_5_5_5;
    else if(mode == MODE_2) return XPM_8_8_8;
    else if(mode == MODE_3) return XPM_5_6_5;
    else if(mode == MODE_4) return XPM_8_8_8_8;
    else return INVALID_XPM;
}


void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  char *ptr = video_mem;
  uint8_t pixel_size = get_bytes_size(bits_per_pixel);
  uint32_t y_coord = y * h_res * pixel_size;
  uint32_t x_coord = x * pixel_size;
  memcpy(ptr + y_coord + x_coord, &color, pixel_size);
}

void (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (uint32_t i = 0; i < len; i++) 
    video_draw_pixel(x + i, y, color);
}

void (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for (uint32_t line = 0; line != height; line++)
    video_draw_hline(x, y + line, width, color);
}

int(video_load_xpm)(xpm_map_t xpm) {
  uint8_t *address;
  if ((address = xpm_load(xpm, xpm_type, &xpm_image)) == NULL) {
    printf("Error loading xpm.\n");
    return 1;
  }
  return 0;
}

void (video_draw_pixmap)(uint16_t xi, uint16_t yi) {
  uint32_t color;
  uint8_t red, green, blue;
  uint16_t y = yi, x = xi, counter = 0;
  for (size_t i = 0; i < xpm_image.size / bytes_per_pixel; i++) {
    if ((x - xi) == xpm_image.width) {
      x = xi;
      y++;
    }
    blue = xpm_image.bytes[counter];
    green = xpm_image.bytes[++counter];
    red = xpm_image.bytes[++counter];
    color = (red << mode_conf.RedFieldPosition) | (green << mode_conf.GreenFieldPosition) | blue;
    counter++;
    video_draw_pixel(x, y, color);
    x++;
  }
}

int(sprite)(uint16_t *x, uint16_t *y, uint16_t xf, uint16_t yf, int16_t speed, int32_t *length) {
  if (*y == yf) // horizontal movement - along x
    movement_sprite(x, xf, speed, length);
  else if (*x == xf) //Vertical movement - along y
    movement_sprite(y, yf, speed, length);

  video_draw_rectangle(0, 0, h_res, v_res, 0);
  video_draw_pixmap(*x, *y);
  return 0;
}

void(movement_sprite)(uint16_t *pos, uint16_t posf, int16_t speed, int32_t *length) {
  //While pos doesn't reach the final position
  if (posf > *pos)
    *pos += speed;
  //If pos has already reached the final position or it's greater
  else
    *pos -= speed;
  //Length decreases at the same time that pos increases
  *length -= speed;
  //In case it has already passed the final position
  if (*length < 0)
    *pos = posf;
}
