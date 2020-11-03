#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define WAIT_KBC 20000

#define MOUSE_IRQ 12 /**< @brief Mouse 12 IRQ line */


//Registers
#define OUT_BUF_REG 0x60
#define IN_BUF_REG 0x60
#define KBC_ST_REG 0x64
#define KBC_CMD_REG 0X64

#define MOUSE_WRITE_B 0XD4 /*To pass commands and arguments*/
#define MOUSE_READ_B 0X60
#define ENABLE_DR 0XF4 /*Enable data reporting*/
#define DISABLE_DR 0XF5
#define ACK 0XFA    /*If everything is ok*/
#define NACK 0XFE   /*If an invalid byte*/ 
#define ERROR 0xFC  /*Second consecutive invalid byte*/


//Mouse bytes
#define MOUSE_LB BIT(0)
#define MOUSE_RB BIT(1)
#define MOUSE_MB BIT(2)
#define MOUSE_BIT_3 BIT(3)
#define MOUSE_MSB_X BIT(4)
#define MOUSE_MSB_Y BIT(5)
#define MOUSE_X_OV BIT(6)
#define MOUSE_Y_OV BIT(7)

//Satus register
#define KBC_PAR_ERR BIT(7) /*Parity error - invalid data*/
#define KBC_TO_ERR BIT(6) /*Timeout error - invalid data*/
#define KBC_AUX BIT(5) /*Mouse data*/
#define KBC_INH BIT(4) /*Inhibit flag: 0 if keyboard is inhibited*/
#define KBC_A2 BIT(3) 
#define KBC_SYS BIT(2)
#define KBC_IBF BIT(1) /*Input buffer full don't wirte commands or arguments*/
#define KBC_OBF BIT(0) /*Output buffer full - data available for reading*/


//Mouse commands
#define MOUSE_RESET 0XFF
#define MOUSE_RESEND 0XFE
#define MOUSE_SET_DFT 0XF6
#define MOUSE_DIS 0XF5
#define MOUSE_ENB 0XF4
#define MOUSE_SET_SMP_RATE 0XF3
#define MOUSE_SET_STREAM 0XEA
#define MOUSE_ST_REQT 0XE9


#define WRITE_CMD_BYTE 0x60 /*Takes A: Command Byte*/



#endif /*_LCOM_I8042_H */
