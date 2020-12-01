#ifndef _LCOM_BIOS_VBE_H
#define _LCOM_BIOS_VBE_H

//BIOS services
#define BIOS_SERVICE_VIDEO 0x10
#define BIOS_SER_PC_CON 0x11
#define BIOS_SER_MEM_CONF 0x12
#define BIOS_SER_KEYBOARD 0x16

#define VBE_SET_MODE 0x4f02
#define VBE_GET_MODE_INFO 0x4f01
#define VBE_GET_CONTROLLER_INFO 0x4f00

#define BYTE_SIZE 8

#define COLOR_BIT_MASK 0xff

#define INDEXED_COLOR_MODE 0x04
#define DIRECT_COLOR_MODE 0x06

#endif /* _LCOM_BIOS_VBE_H */
