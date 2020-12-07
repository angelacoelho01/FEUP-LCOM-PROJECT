#ifndef _LCOM_BIOS_VBE_H
#define _LCOM_BIOS_VBE_H

//BIOS services
#define BIOS_SERVICE_VIDEO 0x10
#define BIOS_SER_PC_CON 0x11
#define BIOS_SER_MEM_CONF 0x12
#define BIOS_SER_KEYBOARD 0x16

#define VBE_SET_MODE 0x4f02
#define VBE_GET_MODE_INFO 0x4f01

#define BYTE_SIZE 8

#define INDEXED_COLOR_MODE 0x04
#define DIRECT_COLOR_MODE 0x06

#define MODE_0 0x105
#define MODE_1 0x110
#define MODE_2 0x115
#define MODE_3 0x11a
#define MODE_4 0x14c

#endif /* _LCOM_BIOS_VBE_H */
