#ifndef _CONST_H
#define _CONST_H


//Keyboard macros
#define IRQ_KEYBOARD 1

#define OUT_BUF_REG 0x60
#define IN_BUF_REG 0x60
#define KBC_CMD_REG 0x64
#define KBC_ST_REG 0x64
#define ESC_BREAKCODE_KEY 0x81

#define KBC_PAR_ERR BIT(7) /*Parity error - invalid data*/
#define KBC_TO_ERR BIT(6) /*Timeout error - invalid data*/
#define KBC_AUX BIT(5) /*Mouse data*/
#define KBC_INH BIT(4) /*Inhibit flag: 0 if keyboard is inhibited*/
#define KBC_A2 BIT(3) 
#define KBC_SYS BIT(2)
#define KBC_IBF BIT(1) /*Input buffer full don't wirte commands or arguments*/
#define KBC_OBF BIT(0) /*Output buffer full - data available for reading*/

//BIOS services
#define BIOS_SERVICE_VIDEO 0x10
#define BIOS_SER_PC_CON 0x11
#define BIOS_SER_MEM_CONF 0x12
#define BIOS_SER_KEYBOARD 0x16

#define VBE_SET_MODE 0x4f02
#define VBE_GET_MODE_INFO 0x4f01

#define BYTE_SIZE 8

//Get color components
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

#define INDEXED_COLOR_MODE 0x04
#define DIRECT_COLOR_MODE 0x06

#endif
