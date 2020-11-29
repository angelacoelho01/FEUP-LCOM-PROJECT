#include "keyboard.h"

int keyboard_hook_id = IRQ_KEYBOARD;
uint8_t scancode;

int (keyboard_check_obf)(uint8_t st){
    //Checks if the output buffer is empty
    if(!(st && KBC_OBF))return 1;
    return 0;
}

int (keyboard_read_obf)(uint8_t* st){
    if(util_sys_inb(OUT_BUF_REG, st) != OK) return 1;
    return 0;
}

int (keyboard_read_status)(uint8_t* st){
    if(util_sys_inb(KBC_ST_REG, st) != OK) return 1;
    return 0;
}

int (keyboard_read_scancode)(){
    uint8_t st;
    if(keyboard_read_status(&st) != OK) return 1;
    if(keyboard_check_obf(st) != OK) return 1;
    if(keyboard_read_obf(&scancode) != OK) return 1;
    return 0;
}

int (keyboard_subscribe_int)(uint8_t* bit_no){
    *bit_no = keyboard_hook_id;
    if(sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id) != OK){
        printf("keyboard_subscribe_int: error in sys_irqsetpolicy\n");
        return 1;
    }
    return 0;
}

int (keyboard_unsubscribe_int)(){
    if(sys_irqrmpolicy(&keyboard_hook_id) != OK) {
        printf("keyboard_unsubscribe_int: error in sys_irqrmpolicy\n");
        return 1;
    }
    return 0;
}
