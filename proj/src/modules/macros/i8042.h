#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define WAIT_KBC 20000

#define KBC_IRQ 1 /**< @brief Keyboad 1 IRQ line */
#define MOUSE_IRQ 12 /**< @brief Mouse 12 IRQ line */

//Registers
#define OUT_BUF_REG 0x60
#define IN_BUF_REG 0x60
#define KBC_CMD_REG 0x64
#define KBC_ST_REG 0x64
#define ESC_BREAKCODE_KEY 0x81
#define RIGHT_ARROW_MAKECODE 0x4D
#define LEFT_ARROW_MAKECODE 0x4B

//Keyboard-Related KBC Commands for PC-AT/PS2
#define READ_COMD_BYTE 0x20 /*Returns Command Byte*/
#define WRITE_CMD_BYTE 0x60 /*Takes A: Command Byte*/
#define CHECK_KBC_CMD 0xAA /*Returns 0x55, if OK; returns 0xFC, if error*/
#define CHECK_KBD_INTER_CMD 0XAB /*Returns 0, if OK*/
#define DISABLE_KBD_INTER_CMD 0XAD
#define ENABLE_KBD_INTER_CMD 0XAE

#define MOUSE_DIS 0xA7 /*Disable Mouse*/
#define MOUSE_ENABLE 0xA8 /*Enable Mouse*/
#define CHECK_MOUSE_IF 0xA9 /*Check Mouse Interface Returns 0, if OK*/
#define MOUSE_WRITE_B 0xD4 /*Write Byte to Mouse*/

//Status register
#define KBC_PAR_ERR BIT(7) /*Parity error - invalid data*/
#define KBC_TO_ERR BIT(6) /*Timeout error - invalid data*/
#define KBC_AUX BIT(5) /*Mouse data*/
#define KBC_INH BIT(4) /*Inhibit flag: 0 if keyboard is inhibited*/
#define KBC_A2 BIT(3) 
#define KBC_SYS BIT(2)
#define KBC_IBF BIT(1) /*Input buffer full don't wirte commands or arguments*/
#define KBC_OBF BIT(0) /*Output buffer full - data available for reading*/

#define BYTE_MSB 0x80

#define KBC_ENABLE_INT BIT(0)
#define MOUSE_ENABLE_INT2 BIT(1)

// Commands passed as arguments of command 0xD4
#define MOUSE_RESET 0xFF /*Reset*/
#define MOUSE_RESEND 0xFE /*Resend*/
#define MOUSE_SET_DFT 0xF6 /*Set Defaults*/
#define MOUSE_DIS_DR 0xF5 /*Disable (data reporting)*/
#define MOUSE_ENB_DR 0xF4 /*Enable (data reporting)*/
#define MOUSE_SET_SMP_RATE 0xF3 /*Set sample rate*/
#define MOUSE_SET_REMOTE 0xF0 /*Set remote mode*/
#define MOUSE_READ_DT 0xEB /*Read Data*/
#define MOUSE_SET_STREAM 0xEA /*Set stream mode*/
#define MOUSE_ST_REQT 0xE9 /*Status request*/
#define MOUSE_SET_RES 0xE8 /*Set resolution*/
#define MOUSE_SCALING_21 0xE7 /*Set scaling 2:1*/
#define MOUSE_SCALING_11 0xE6 /*Set scaling 1:1*/

// Mouse acknowledgment bytes
#define ACK 0xFA  /*If everything is ok*/
#define NACK 0xFE  /*If an invalid byte*/ 
#define ERROR 0xFC  /*Second consecutive invalid byte*/

// PS/2 Mouse packet (1 packet = 3 bytes)
// BYTE 1
#define MOUSE_LB BIT(0)
#define MOUSE_RB BIT(1)
#define MOUSE_MB BIT(2)
#define MOUSE_BIT_3 BIT(3)
#define MOUSE_MSB_X BIT(4)
#define MOUSE_MSB_Y BIT(5)
#define MOUSE_X_OV BIT(6)
#define MOUSE_Y_OV BIT(7)
//BYTE 2
#define MOUSE_X_DELTA 0xFF
//BYTE 2
#define MOUSE_Y_DELTA 0xFF

#endif /* _LCOM_I8042_H */
