#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "../macros/i8042.h"
#include "../keyboard/keyboard.h"

int mouse_hook_id = 2; 
char mouse_ih_error = 0;
uint8_t mouse_byte = 0;

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

void(mouse_ih)() {
	uint8_t stat;
  //Reads the status register 
  if(util_sys_inb(KBC_ST_REG, &stat) != OK){ 
    printf("Error.\n");
    mouse_ih_error = 1;
  }else{
    //Reads the output buffer, if possible
    if(util_sys_inb(OUT_BUF_REG, &mouse_byte) != OK){ 
      printf("Error.\n");
      mouse_ih_error = 1;
    }
    //Checks if there was som parity or timeout errors
    if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0){ 
      printf("Error - invalid data\n");
      mouse_ih_error = 1;
    }else{
      //If it reachs this, mouse_byte read valid
      mouse_ih_error = 0; 
    }  
  }
}

int (mouse_enable_data_report)() {
	uint8_t response;

  // enable data reporting
	do{
    // write mouse mouse_byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
    // Pass the argument of 0xD4 to the output buffer - enable data reporting
		if (kbc_write_reg(MOUSE_ENB_DR) != OK) continue; 
    // Reads the reponse value (acknoledgement mouse_byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;
	}while(response != ACK); // Does until 'OK'
	
	return 0;
}

int (mouse_disable_data_reporting)() {
	uint8_t response;
	
	do{
    // write mouse mouse_byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue;
    // Pass the argument of 0xD4 to the output buffer - disable data reporting
		if (kbc_write_reg(MOUSE_DIS_DR) != OK) continue; 
    // Reads the reponse value (acknoledgement mouse_byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;;
	}while(response != ACK); // Does until 'OK'
	
	return 0;
}

int (get_packet)(uint8_t mouse_byte, uint8_t *num_mouse_bytes, struct packet *pp) {
  if (0 == *num_mouse_bytes){ // we expect the first mouse_byte -> the bit 3 of mouse_byte is equal to 1
    if((mouse_byte & MOUSE_BIT_3) == 0x00){ // invalid first mouse_byte -> discard
      return 1;
    }else{
      pp->rb = (mouse_byte & MOUSE_RB);
      pp->mb = (mouse_byte & MOUSE_MB);
      pp->lb = (mouse_byte & MOUSE_LB);
      pp->x_ov = (mouse_byte & MOUSE_X_OV);
      pp->y_ov = (mouse_byte & MOUSE_Y_OV);
    }
  }

  // in every other situation accept the mouse_byte
  pp->bytes[*num_mouse_bytes] = mouse_byte;

  if(1 == *num_mouse_bytes){
    if((pp->bytes[0] & MOUSE_MSB_X) == 0){
      pp->delta_x = mouse_byte;
    }
    else{
      pp->delta_x = mouse_byte - 256;
    }
  }

  if (2 == *num_mouse_bytes){ // represents y_delta
    if((pp->bytes[0] & MOUSE_MSB_Y) == 0){
      pp->delta_y = mouse_byte;
    }
    else{
      pp->delta_y = mouse_byte - 256;
    }
    *num_mouse_bytes = 0; // packet complete
    return 0;
  }

  *num_mouse_bytes += 1;
	return 1;
}

int (mouse_set_remote)() {
  uint8_t response;

  // Set remote mode
	do{
    // write mouse mouse_byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
    // Pass the argument of 0xD4 to the output buffer - set remote
		if (kbc_write_reg(MOUSE_SET_REMOTE) != OK) continue; 
    // Reads the reponse value (acknoledgement mouse_byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;
	}while(response != ACK);

  return 0;
}

int (mouse_set_stream)() {
  uint8_t response;

  // Set stream
	do{
    // write mouse mouse_byte (cmd 0xD4) in kbc_cmd_reg (0x64)
		if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
    // Pass the argument of 0xD4 to the output buffer - set stream
		if (kbc_write_reg(MOUSE_SET_STREAM) != OK) continue; 
    // Reads the reponse value (acknoledgement mouse_byte) from the input buffer
		if (kbc_read_reg(&response) != OK) continue;
	}while(response != ACK); //

  return 0;

}

int (mouse_poll_handler)() {
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
        // write mouse mouse_byte (cmd 0xD4) in kbc_cmd_reg (0x64)
        if (kbc_issue_cmd(MOUSE_WRITE_B) != OK) continue; 
        // Pass the argument of 0xD4 to the output buffer - set stream
        if (kbc_write_reg(MOUSE_READ_DT) != OK) continue; 
        // Reads the reponse value (acknoledgement mouse_byte) from the input buffer
        if (kbc_read_reg(&response) != OK) continue;
      } while (response != ACK);

      if (kbc_issue_cmd(READ_COMD_BYTE) != OK) return 1;
      if (kbc_read_reg(&mouse_byte) != OK) return 1;
      
      return 0; // mouse_byte read valid
    }
  }
}

// ------ funcao da que deteta o evento originado por aquele packet do mouse ----- //
struct mouse_ev evt = {BUTTON_EV, 0, 0};

struct mouse_ev* (mouse_event_detect)(struct packet *p) {
  enum  mouse_ev_t event;
	
  // printf("AQUI_EVENT_DETECT\n");
	// deltas so definidos quando o evento é de movimento
	if (p->lb == 1 && p->rb == 0 && p->mb == 0) { // apenas esquerdo
		event = LB_PRESSED;
		// verifica se houve deslocamento neste cenario
		if (p->delta_x != 0 || p->delta_y != 0) {
			event = MOUSE_MOV;
			evt.delta_x = p->delta_x;
			evt.delta_y = p->delta_y;
		}
	} else if (p->lb == 0 && p->rb == 0 && p->mb == 0) { // todos levantados -> ou ja estava ou porque acabou de lenvantar o esquerdo
    // printf("AQUI_EVENT_DETECT_RELEASE\n");
		event = LB_RELEASED;
    // printf("AQUI_EVENT_DETECT_RELEASE_end\n");
	} else {
		event = BUTTON_EV; // qualquer outro botao
	}

  evt.type = event;
	
  // printf("AQUI_EVENT_DETECT_end\n");
	return (&evt);
}

// ------ funcao da maquina de estados da linha horizontal ----- //

typedef enum {INIT, DRAW, COMP} state_t;

// retorna true apenas no caso de existir deslocamento do rato
// interrupção do rato - o deslocamento do rato (e indicação para esquerda ou direita no caso de ser negativo [esquerda] ou positivo [direita])
bool (check_horizontal_line)(struct mouse_ev *evt, uint8_t tolerance) { 
  
  bool update = false;
  static state_t st = INIT; // initial state; keep state
  
  switch (st) {
    case INIT:
      if(evt->type == LB_PRESSED) // apenas botao esquerdo premido - mantem onde está
        st = DRAW;
      break;
    case DRAW: // existe deslocamento do rato
      if (evt->type == LB_RELEASED) { // realease left button
        // acaba este movimento da plataforma - complete
        st = COMP;
      }
      if (evt->type == BUTTON_EV){ // outro qualquer buttao primido
        st = INIT;
      }
      if( evt->type == MOUSE_MOV ) { // deslocamento do mouse sem alteração do botao
        // linha na horizontal - para direita ou esquerda, nao tem direção obrigatoria, apenas tem de estar dentro da tolerancia pretendida
		if (abs(evt->delta_y) > tolerance)
			st = INIT;
		else 
			// keep in this state
			update = true; // valid tolerance - update plataform position
      }
      break;
	case COMP: // there was a all move completed, but more can be done
      if (evt->type == LB_PRESSED) { 
		st = DRAW;
      }
	  // qualquer outro evento é ignorado, desde movimento e pressionar outro qualquer butao
      break;
    default:
      break;
  }

  return (update);
}
