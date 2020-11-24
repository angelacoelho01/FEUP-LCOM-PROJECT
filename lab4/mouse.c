#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"

//Initialize with a value between 0 and 7
//Distinguish instructions by using different bit masks for the hook_id
int timer_hook_id = 0; 
int mouse_hook_id = 1; 

char ih_error = 0;
uint8_t byte = 0;

int (kbc_read_status_reg)(uint8_t *status){
  if (util_sys_inb(KBC_ST_REG, status) != OK){
    printf("Error when reading status register");
    return 1;
  }

  return 0;
}

int (mouse_subscribe_int)(uint8_t *bit_no) {

  *bit_no = mouse_hook_id; 
  // Mouse interrupt subscription in exclusive mode
  if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK){
    printf("ERROR in subcribe_int: sys_irqsetpolicy!!\n");
    return 1;
  }

  return 0;
}

int (mouse_unsubscribe_int)() {

  if (sys_irqrmpolicy(&mouse_hook_id) != OK){
    printf("ERROR in unsubcribe_int: iqrmpolicy!\n");
    return 1;
  }

  return 0;
}

void(mouse_ih)(){
	uint8_t stat;
  //Reads the status register 
  if(util_sys_inb(KBC_ST_REG, &stat) != OK){ 
    printf("Error.\n");
    ih_error = 1;
  }else{
    //Reads the output buffer, if possible
    if(util_sys_inb(OUT_BUF_REG, &byte) != OK){ 
      printf("Error.\n");
      ih_error = 1;
    }
    //Checks if there was som parity or timeout errors
    if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0){ 
      printf("Error - invalid data\n");
      ih_error = 1;
    }else{
      //If it reachs this, byte read valid
      ih_error = 0; 
    }  
  }
}

int (kbc_issue_cmd)(uint8_t cmd){
  uint8_t status;
  while( 1 ) {
    //First reads the status register
    if (kbc_read_status_reg(&status) == OK){
      //Checks if the input buffer is empty so that we can write
      if( (status & KBC_IBF) == 0 ) { 
        //Sends a command to register 0x64
        if(sys_outb(KBC_CMD_REG, cmd) == OK){ 
          return 0;
        }else{
          printf("Error in writing a command");
        }
      }else{
        printf("INPUT BUFFER IS FULL, WE CANNOT WRITE");
      }
      //If we ca't send commands, it will try again after 20 seconds
      tickdelay(micros_to_ticks(WAIT_KBC));
    }
  }
  return 1;
}

int (kbc_read_reg)(uint8_t *data){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    //If the output buffer is full (==1) - data available for reading
    if((status & KBC_OBF) == 1){ 
      //Reads from register 0x60 the return value
      if(util_sys_inb(OUT_BUF_REG, data) == OK){ 
        return 0;
      }
    }else{
      printf("Data not available for reading");
    }
  }

  return 1;
}

int (kbc_write_reg)(uint8_t data){
  uint8_t status;
  if (kbc_read_status_reg(&status) == OK){
    //If the input buffer is empty (==0) - we can write
    if((status & KBC_IBF) == 0){ 
      //Writes data into register 0x60 the new value - passes the argument
      if(sys_outb(IN_BUF_REG, data) == OK){
        return 0;
      }
    }else {
      printf("We cannot write - input buffer full");
    }
  }
  
  return 1;
}

int (mouse_enable_data_report)(){
	uint8_t response;

  // enable data reporting
	do{
    // write mouse byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
    // Pass the argument of 0xD4 to the output buffer - enable data reporting
		if (kbc_write_reg(MOUSE_ENB_DR) != OK) continue; 
    // Reads the reponse value (acknoledgement byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;
	}while(response != ACK); // Does until 'OK'
	
	return 0;
}

int (mouse_disable_data_reporting)(){
	uint8_t response;
	
	do{
    // write mouse byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue;
    // Pass the argument of 0xD4 to the output buffer - disable data reporting
		if (kbc_write_reg(MOUSE_DIS_DR) != OK) continue; 
    // Reads the reponse value (acknoledgement byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;;
	}while(response != ACK); // Does until 'OK'
	
	return 0;
}

int (reset_kbc_status)(){
	  uint8_t cmd_byte;
    // get minix default cmd byte
    cmd_byte = minix_get_dflt_kbc_cmd_byte();
    // cmd to write the new byte to the kbc
    if (kbc_issue_cmd(WRITE_CMD_BYTE) != OK){
      printf("error in write_cmd_byte");
      return 1;
    }
    // pass the cmd argument to the output buffer - new cmd byte value
    if (kbc_write_reg(cmd_byte) != OK){
      printf("error in passing the new cmd byte value as argument");
      return 1;
    }

    return 0;
}

int (get_packet)(uint8_t byte, uint8_t *num_bytes, struct packet *pp){
  if (0 == *num_bytes){ // we expect the first byte -> the bit 3 of byte is equal to 1
    if((byte & MOUSE_BIT_3) == 0x00){ // invalid first byte -> discard
      return 1;
    }else{
      pp->rb = (byte & MOUSE_RB);
      pp->mb = (byte & MOUSE_MB);
      pp->lb = (byte & MOUSE_LB);
      pp->x_ov = (byte & MOUSE_X_OV);
      pp->y_ov = (byte & MOUSE_Y_OV);
    }
  }

  // in every other situation accept the byte
  pp->bytes[*num_bytes] = byte;

  if(1 == *num_bytes){
    if((pp->bytes[0] & MOUSE_MSB_X) == 0){
      pp->delta_x = byte;
    }
    else{
      pp->delta_x = byte - 256;
    }
  }

  if (2 == *num_bytes){ // represents y_delta
    if((pp->bytes[0] & MOUSE_MSB_Y) == 0){
      pp->delta_y = byte;
    }
    else{
      pp->delta_y = byte - 256;
    }
    *num_bytes = 0; // packet complete
    return 0;
  }

  *num_bytes += 1;
	return 1;
}

int (mouse_set_remote)(){
  uint8_t response;

  // Set remote mode
	do{
    // write mouse byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
    // Pass the argument of 0xD4 to the output buffer - set remote
		if (kbc_write_reg(MOUSE_SET_REMOTE) != OK) continue; 
    // Reads the reponse value (acknoledgement byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;
	}while(response != ACK);

  return 0;
}

int (mouse_set_stream)(){
  uint8_t response;

  // Set stream
	do{
    // write mouse byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
    // Pass the argument of 0xD4 to the output buffer - set stream
		if (kbc_write_reg(MOUSE_SET_STREAM) != OK) continue; 
    // Reads the reponse value (acknoledgement byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;
	}while(response != ACK); //

  return 0;

}

int(mouse_poll_handler)(){
  uint8_t stat;

  if(util_sys_inb(KBC_ST_REG, &stat) != OK){ // Reads the status register 
    return 1;
  }else{
    if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0){ // check if there was some error 
      printf("Error - invalid data\n");
      return 1;
    }else{
      uint8_t response;

      // READ DATA (0xEB)
      do {
        // write mouse byte (cmd 0xD4) in kbc_cmd_reg (0x64)
        if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
        // Pass the argument of 0xD4 to the output buffer - set stream
        if (kbc_write_reg(MOUSE_READ_DT) != OK) continue; 
        // Reads the reponse value (acknoledgement byte) from the input buffer
        if (kbc_read_reg(&response) != OK) continue;
      } while (response != ACK);

      if (kbc_issue_cmd(READ_COMD_BYTE) != OK) return 1;
      if (kbc_read_reg(&byte) != OK) return 1;
      
      return 0; // byte read valid
    }
  }
}

typedef enum {INIT, DRAWL1, VERTIX, DRAWL2, COMP} state_t;

bool(check_draw)(struct mouse_ev *evt, uint8_t x_len, uint8_t tolerance){ 
  bool res = false;
  // ->> byte é global nao precisa de ser passado por parametros
  // funcao que representa o automato: estados e transições
  static state_t st = INIT; // initial state; keep state
  switch (st) {
    case INIT:
      if(evt->type == LB_PRESSED)
        st = DRAWL1;
      break;
    case DRAWL1:
      if (evt->type == LB_RELEASED) { // realease left button
        // acabou de desenhar a 1 parte - verificar slope e x_len
        int16_t slope = evt->delta_y / evt->delta_x;
        if ((evt->delta_x < x_len) || (abs(slope) < 1))
          st = INIT;
        else {
          st = VERTIX;
        }
      }
      if (evt->type == BUTTON_EV){ 
        st = INIT;
      }
      if( evt->type == MOUSE_MOV ) {
        // linha para cima - should have displacement in x and y positive
        if (evt->delta_x < 0) { // check tolerance
          if (abs(evt->delta_x) > tolerance)
            st = INIT;
        }
        if (evt->delta_y < 0) { // check tolerance
          if (abs(evt->delta_y) > tolerance)
            st = INIT;
        }
      }
      break;
    case VERTIX:
      if (evt->type == RB_PRESSED){ // right primido
        st = DRAWL2;
      }
      if (evt->type == BUTTON_EV){ 
        st = INIT;
      }
      if (evt->type == MOUSE_MOV){
        // tolerancia entre a troca de botoes
        if ((abs(evt->delta_x) > tolerance) || (abs(evt->delta_y) > tolerance))
            st = INIT;
      }
      break;
    case DRAWL2:
      if (evt->type == RB_RELEASED) { // realease right button
        // acabou de desenhar a 2 parte - verificar slope e x_len
        int16_t slope = evt->delta_y / evt->delta_x;
        if ((evt->delta_x < x_len) || (abs(slope) < 1))
          st = INIT;
        else {
          st = COMP;
          res = true;
        }
      }
      if (evt->type == BUTTON_EV){
        st = INIT;
      }
      if(evt->type == MOUSE_MOV ) {
         // linha para baixo - should have displacement in x positive and y negative
        if (evt->delta_x < 0) { // check tolerance
          if (abs(evt->delta_x) > tolerance)
            st = INIT;
        }
        if (evt->delta_y > 0) { // check tolerance
          if (abs(evt->delta_y) > tolerance)
            st = INIT;
        }
      }
      break;
    default:
      break;
  }

  return (res);
}
