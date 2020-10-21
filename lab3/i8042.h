#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define WAIT_KBC 20000

#define KBC_IRQ 1 /**< @brief Keyboad 1 IRQ line */

//Registers
#define OUT_BUF_REG 0x60
#define IN_BUF_REG 0x60
#define KBC_CMD_REG 0x64
#define KBC_ST_REG 0x64
#define ESC_BREAKCODE_REG 0x81

//Keyboard-Related KBC Commands for PC-AT/PS2
#define READ_COMD_BYTE 0x20 /*Returns Command Byte*/
#define WRITE_CMD_BYTE 0x60 /*Takes A: Command Byte*/
#define CHECK_KBC_CMD 0xAA /*Returns 0x55, if OK; returns 0xFC, if error*/
#define CHECK_KBD_INTER_CMD 0XAB /*Returns 0, if OK*/
#define DISABLE_KBD_INTER_CMD 0XAD
#define ENABLE_KBD_INTER_CMD 0XAE

//Satus register
#define KBC_PAR_ERR BIT(7) /*Parity error - invalid data*/
#define KBC_TO_ERR BIT(6) /*Timeout error - invalid data*/
#define KBC_AUX BIT(5) /*Mouse data*/
#define KBC_INH BIT(4) /*Inhibit flag: 0 if keyboard is inhibited*/
#define KBC_A2 BIT(3) 
#define KBC_SYS BIT(2)
#define KBC_IBF BIT(1) /*Input buffer full don't wirte commands or arguments*/
#define KBC_OBF BIT(0) /*Output buffer full - data available for reading*/

#endif /* _LCOM_I8042_H */
