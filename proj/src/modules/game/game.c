#include "game.h"

#include <stdlib.h>
#include <time.h>

bool lost, game_started = false, is_move_ball = false, pause_game = false;

// TIMER VARIABLES
extern int timer_hook_id;
extern unsigned long timer_counter;

// KEYBOARD VARIABLES
extern char kbc_ih_error;
extern uint8_t kbc_scancode;

// MOUSE VARIABLES
extern char mouse_ih_error;
extern uint8_t mouse_byte;

// VIDEO VARIABLES
extern vbe_mode_info_t mode_conf;
extern enum xpm_image_type xpm_type;
extern xpm_image_t xpm_image;

// of player 1
extern uint16_t plataform_x;
extern uint8_t no_lives;

// add for player 2
//...

// cronometro do jogo
extern uint8_t minutes, seconds;

// to be updated with a interval of 30 seconds
extern size_t plataform_to_draw;
uint16_t ball_speed = BALL_SPEED;
uint16_t plataform_speed = PLATAFORM_SPEED;

#include "../../modules/video/video.h"

extern state_menus_t menus_st;

// resolution of the mode
extern unsigned h_res, v_res;
//extern struct Mouse_cursor cursor;

int (game_start)(uint16_t mode){

  // load all the xpms to be used 
  load_all_xpms();
  cursor_initializer();
  menu_initializer();

  uint16_t scenario_limit_left, scenario_limit_right, ball_x, ball_y; bool up, left;
  game_solo_inicializer(&scenario_limit_left, &scenario_limit_right, &ball_x, &ball_y, &up, &left);

  // define the limits os the 2 screens of the 1v1 mode game
  //...

  // the player - passed by argument when running the app
  struct Player p1 = add_player("Joao", 0);
  write_players("/home/lcom/labs/g08/proj/src/data/players_scores.txt");
 
  // subscribe all the necessary services
  if (start_video_mode(mode) != OK){
    return_to_text_mode();
    return 1;
  }

  // to subscribe the Timer interrupts
  uint8_t timer_bit_no;
  if (timer_subscribe_int(&timer_bit_no) != OK) return 1;

  // to subscribe the KBC interrupts
  uint8_t kbc_bit_no;
  if (keyboard_subscribe_int(&kbc_bit_no) != OK) return 1;

  // Mouse: Enable data reporting 
	if (mouse_enable_data_reporting() != OK) return 1;

	//Subscribes mouse's interrupts
	uint8_t mouse_bit_no;
	if (mouse_subscribe_int(&mouse_bit_no) != OK) return 1;

  int ipc_status;
  message msg;

  unsigned long global_counter = 0;

  uint32_t timer_irq_set = BIT(timer_bit_no);
  uint32_t kbc_irq_set = BIT(kbc_bit_no);
  uint32_t mouse_irq_set = BIT(mouse_bit_no);

  // necessary varibles for mouse
  uint8_t mouse_num_bytes = 0;
  struct packet mouse_pp;
  struct mouse_ev* mouse_evt;
  bool mouse_flag = false;
  bool mouse_on_over = false;
  
  enum menu_ev_t evt_mouse = NO_OPT;
  
  bool flag_first = true;

  // not exit the aplication
  while (menus_st != EXIT_GAME) {
    if (flag_first) { // the next state is to be draw
      clean_screen(h_res, v_res, MENUS_BACKGROUND_COLOR);
      mouse_on_over = false;
      switch (menus_st) {
        case MAIN_MENU:
          game_started = false; is_move_ball = false; pause_game = false;
          draw_start_menu();
          draw_cursor(mouse_cursor_normal_xpm);
          break;
        case GAME_SOLO:
          game_started = false; is_move_ball = false; pause_game = false;
          game_solo_inicializer(&scenario_limit_left, &scenario_limit_right, &ball_x, &ball_y, &up, &left);
          draw_scenario(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
          break;
        case GAME_SOLO_CONTINUE:
          game_started = true; is_move_ball = true; pause_game = false;
          // draw_scenario em modo continuar
          break;
        case GAME_1V1:
          break;
        case GAME_1V1_CONTINUE:
          game_started = true; is_move_ball = true; pause_game = false;
          // draw_scenario em modo continuar
          break;
        case PAUSE_SOLO_MENU: case PAUSE_1V1_MENU:
          game_started = true; is_move_ball = false; pause_game = true;
          draw_pause_menu();
          pause_game = true;
          break;
        case LEADERBOARD:
          game_started = false; is_move_ball = false; pause_game = false;
          break;
        default:
          break;
      }
      flag_first = false;
    } 

    int r;
    // get a request message
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    // received notification
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
      // hardware interrupt notification
      case HARDWARE:
        if (msg.m_notify.interrupts & kbc_irq_set) { // KBC interruption
          // reads ONE BYTE from the KBC’s OUT_BUF PER INTERRUPT
          kbc_ih();
          if (kbc_ih_error == 0) { // if there was no error
            if (!(kbc_scancode & BYTE_MSB)) { // if MSB = 0 -> make code
              if (menus_st == GAME_SOLO || menus_st == GAME_SOLO_CONTINUE) { // estado da maquina de estados
                play_solo_game_kbc(scenario_limit_right, scenario_limit_left);
              } else if (menus_st == GAME_1V1 || menus_st == GAME_1V1_CONTINUE) {
                // play_1v1_game_kbc(); // verifica se é para mover e qual dos players plataforma é para alterar
              } 
            }

            if ((kbc_scancode == ESC_BREAKCODE_KEY) && (menus_st == GAME_SOLO || menus_st == GAME_SOLO_CONTINUE || menus_st == GAME_1V1 || menus_st == GAME_1V1_CONTINUE)) { // open pause_menu
              evt_mouse = OPT_PAUSE;
              menus_st = navigate_between_menus(evt_mouse);
              pause_game = true; 
              continue;
            }
          }
        }

        if (msg.m_notify.interrupts & mouse_irq_set) {
          mouse_ih();
          if (mouse_ih_error == 0){ //If there was no error
            if (get_packet(mouse_byte, &mouse_num_bytes, &mouse_pp) == 0){ // indicates that a packet is complete            
              mouse_flag = true;
            }
          } else continue;
        }

        // packet complete - move plataform with the mouse
        if (mouse_flag) { 
          mouse_evt = mouse_event_detect(&mouse_pp); 
          if (global_counter >= 20) { // draw the mouse cursor
            if (change_cursor_position(&mouse_pp)) {
              if (menus_st == MAIN_MENU) {
                evt_mouse = check_options_on_over(main_menu, 4, &mouse_on_over);
              } else if (menus_st == PAUSE_SOLO_MENU || menus_st == PAUSE_1V1_MENU) {
                evt_mouse = check_options_on_over(pause_menu, 3, &mouse_on_over);
              } else if (menus_st == LEADERBOARD) {
                evt_mouse = check_options_on_over(leaderboard_menu, 2, &mouse_on_over);
              } else {
                evt_mouse = check_options_on_over(leaderboard_menu, 0, &mouse_on_over); // no option to detect - only draw here
              }
            }

            global_counter = 0;
          }

          if (menus_st == MAIN_MENU || menus_st == PAUSE_SOLO_MENU || menus_st == PAUSE_1V1_MENU || menus_st == LEADERBOARD) {
              if ((evt_mouse != NO_OPT) && (menu_select_option_detect(mouse_evt))) {
                menus_st = navigate_between_menus(evt_mouse);
                flag_first = true;
                continue;
              }
            }

          if (menus_st == GAME_SOLO || menus_st == GAME_SOLO_CONTINUE) {
            play_solo_game_mouse(mouse_evt, scenario_limit_right, scenario_limit_left, mouse_pp);
          } else if (menus_st == GAME_1V1 || menus_st == GAME_1V1_CONTINUE) {
            // move plataform in mode 1v1
          }

          mouse_flag = false;
        }  

        tickdelay(micros_to_ticks(WAIT_KBC));

        if (msg.m_notify.interrupts & timer_irq_set) { // timer interruption
          timer_int_handler();
          global_counter++;
          // copy_from_double_buffer();
          // if(game_started) copy_from_double_buffer();
          if (menus_st == GAME_SOLO || menus_st == GAME_SOLO_CONTINUE) {
            play_solo_game_timer(&ball_x, &ball_y, &up, &left, p1, &flag_first, &evt_mouse);
          }
        }
        break;
      default:
        break;
      }
    } 

  } 

  // unsubscribe to the services used

  // To unsubscribe the Timer interrupts
  if (timer_unsubscribe_int() != OK) return 1;

  // To unsubscribe the KBC interrupts
  if (keyboard_unsubscribe_int() != OK) return 1;

  // To unsubscribe the Mouse interrupts
  if (mouse_unsubscribe_int() != OK) return 1;

  // Mouse: Disable data reporting 
	// if (mouse_disable_data_reporting() != OK) return 1;

  if (return_to_text_mode() != OK) return 1;

  return 0;
}

void (game_solo_inicializer)(uint16_t *scenario_limit_left, uint16_t *scenario_limit_right, uint16_t *ball_x, uint16_t *ball_y, bool *up, bool *left) {
  // define the limits of solo game
  *scenario_limit_left = SOLO_SCENARIO_CORNER_X + BORDER_WIDTH;
  *scenario_limit_right = SOLO_SCENARIO_CORNER_X + SCENARIO_WIDTH - BORDER_WIDTH;
  // define the inicital x of the plataform of the player 1
  plataform_x = SOLO_SCENARIO_CORNER_X + PLATAFORM_TO_LEFT_X_INIT;
  // initial informations relative to the ball - player 1
  *ball_x = (uint16_t) SOLO_SCENARIO_CORNER_X + BALL_TO_LEFT_X;
  *ball_y = (uint16_t) SOLO_SCENARIO_CORNER_Y + BALL_TO_TOP_Y;
  *up = true; *left = rand() & 1;
}

void (play_solo_game_kbc)(uint16_t scenario_limit_right, uint16_t scenario_limit_left) {
  if (move_plataform(scenario_limit_right, scenario_limit_left)) {
    draw_plataform(plataform_x, SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y, SOLO_SCENARIO_CORNER_X, plataforms_xpms[plataform_to_draw]);
    // just  only if there was a movement from the player
    game_started = true; // timer starts to count  
    is_move_ball = true; // the ball start moving 
  }
}

void (play_solo_game_mouse)(struct mouse_ev* mouse_evt, uint16_t scenario_limit_right, uint16_t scenario_limit_left, struct packet mouse_pp){
  // verifica o estado de todos os botoes do rato
  if (check_horizontal_line(mouse_evt, H_LINE_TOLERANCE)) {
    if (move_plataform_mouse(scenario_limit_right, scenario_limit_left, mouse_pp.delta_x)) {
      draw_plataform(plataform_x, SOLO_SCENARIO_CORNER_Y + PLATAFORM_TO_TOP_Y, 
                    SOLO_SCENARIO_CORNER_X,  plataforms_xpms[plataform_to_draw]);
      // just  only if there was a movement from the player
      game_started = true; // timer starts to count  - if the first move is with the timer
      is_move_ball = true; // the ball start moving 
    } // se x da plaetaforma + esse deslocamento nao passa os limites
  }
}

void (play_solo_game_timer)(uint16_t *ball_x, uint16_t *ball_y, bool *up, bool *left, struct Player p1, bool *flag_first, enum menu_ev_t *evt_mouse) {
  if (timer_counter % 60 == 0) { // true every 1 second (freq = 60Hz)
    start_clock(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y); // the player moved the plataform for the first time (3 lives) - start the clock
  }

  if (is_move_ball) {
    move_ball(ball_x, ball_y, up, left, SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
    
    // check if game is over
    if ((0 == no_lives) || (0 == get_list_size())) {
      clean_ball(*ball_x, *ball_y);
      if (0 == no_lives) game_over_display(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y);
      else game_win_display(SOLO_SCENARIO_CORNER_X, SOLO_SCENARIO_CORNER_Y, p1);
      sleep(5);
      *evt_mouse = OPT_EXIT;
      menus_st = MAIN_MENU;
      *flag_first = true;
    }
  }
}

void (start_clock)(uint16_t xi, uint16_t yi){
  if (game_started){
    seconds = timer_counter / 60;
    minutes = seconds / 60;
    seconds = (seconds < 60 ? seconds : seconds % 60);

    draw_clock(minutes, (uint8_t)seconds, xi + FIRST_NUMBER_TO_LEFT_X, yi + FIRST_NUMBER_TO_TOP_Y);

    if (seconds % 30 == 0) { // every 30 seconds
      if (plataform_to_draw != 4) { // if not in it's final form
        ++plataform_to_draw; // decreases plataform width
        ++ball_speed; // increases ball speed
        plataform_speed += 10;
        draw_plataform(plataform_x, yi + PLATAFORM_TO_TOP_Y, xi, plataforms_xpms[plataform_to_draw]);
      }
    }
  } 
  else timer_counter = 0;
}

bool (move_plataform)(uint16_t right_limit, uint16_t left_limit){
  uint16_t width = plataform_width[plataform_to_draw];

  if ((kbc_scancode == RIGHT_ARROW_MAKECODE) || (kbc_scancode == D_MAKECODE)){
    uint16_t plataform_end = plataform_x + width;
    
    if (plataform_end < right_limit){ // right Arrow or D => shift to the right
      if((plataform_end + plataform_speed) < right_limit)
        plataform_x += plataform_speed;
      else
        plataform_x = right_limit - width;
      
      return true;
    }
  }
  else if((kbc_scancode == LEFT_ARROW_MAKECODE) || (kbc_scancode == A_MAKECODE)){
    if (plataform_x > left_limit){ // left Arrow or A=> shift to the left
      if((plataform_x - plataform_speed) > left_limit)
        plataform_x -= plataform_speed;
      else
        plataform_x = left_limit;
      
      return true;
    }
  }

  return false; 
}

bool (move_plataform_mouse)(uint16_t right_limit, uint16_t left_limit, int16_t displacement){
  uint16_t width = plataform_width[plataform_to_draw];

  if (displacement > 0){ // to the right
    uint16_t plataform_end = plataform_x + width;
    
    if (plataform_end < right_limit){ 
      if((plataform_end + displacement) < right_limit)
        plataform_x += displacement;
      else
        plataform_x = right_limit - width;
      
      return true;
    }
  }
  else if (displacement < 0){ // deslocamento menor que 0 - para a esquerda
    if (plataform_x > left_limit){
      if((plataform_x + displacement) > left_limit)
        plataform_x += displacement;
      else
        plataform_x = left_limit;
      
      return true;
    }
  }

  return false; 
}

void (next_life)(uint16_t* ball_x, uint16_t* ball_y, bool* up, bool* left, uint16_t xi, uint16_t yi){
  no_lives--;
  // we most keep the info of the blocks in the scenario - this are the ones that will be draw
  draw_scenario (xi, yi);
  
  *ball_x = (uint16_t) xi + BALL_TO_LEFT_X;
  *ball_y = (uint16_t) yi + BALL_TO_TOP_Y;
  *up = true; *left = rand() & 1;
  is_move_ball = false; // do not move the ball till the player move the plataform again
  lost = false; // to keep track of the next try
  
  plataform_x = xi + PLATAFORM_TO_LEFT_X_INIT + (6*plataform_to_draw);
}

void (move_ball)(uint16_t* x, uint16_t* y, bool* up, bool* left, uint16_t scenario_xi, uint16_t scenario_yi){
 
  uint16_t xi = *x, yi = *y;
  // arranjar forma de nao calcular isto tantas vezes - mas ainda depender do canto do nivel - talvez por parametro ou ser global mas apenas inicializada dentro do play_solo
  //uint16_t ball_top_limit = scenario_yi + BLOCKS_TO_TOP_Y + (BLOCKS_HEIGHT*NUMBER_BLOCKS_Y);
  uint16_t ball_top_limit = get_ball_top_limit(*x, *y, SOLO_SCENARIO_CORNER_Y);
  uint16_t ball_down_limit = scenario_yi + PLATAFORM_TO_TOP_Y - BALL_HEIGHT;
  uint16_t ball_left_limit = scenario_xi + BORDER_WIDTH;
  uint16_t ball_right_limit = scenario_xi + SCENARIO_WIDTH - BORDER_WIDTH - BALL_WIDTH;
  unsigned int frame_down_limit = scenario_yi + PLATAFORM_TO_TOP_Y + PLATAFORM_HEIGHT + 20;
  struct ball_position ball_pos = get_ball_position(*x,(unsigned int)*y);
  handle_collision(ball_pos, left);
  if(*up){
    if((*y - ball_speed) > ball_top_limit) *y -= ball_speed;
    else{
      *y = ball_top_limit;
      *up = false;
    }
  }
  else{
    if((*y + ball_speed + BALL_HEIGHT) <= ball_down_limit) *y += ball_speed;
    else{
      uint32_t pixel_color = get_pixel_color(xi, yi+ ball_speed + BALL_HEIGHT);
      if(pixel_color == SCENARIO_BACKGROUND_COLOR){
        lost = true;
        *y += ball_speed;
      }
      else{
        *y = ball_down_limit;
        *up = true;
        lost = false; // to see the red borders too
      }
    }
  }

  if(*left){
    if((*x - ball_speed) > ball_left_limit) *x -= ball_speed;
    else{
      *x = ball_left_limit;
      *left = false;
    }
  }
  else{
    if((*x + ball_speed) < ball_right_limit) *x += ball_speed;
    else{
      *x = ball_right_limit;
      *left = true;
    }
  }
  
  if(lost && (*y + ball_speed + BALL_HEIGHT) >= frame_down_limit)
    next_life(x, y, up, left, scenario_xi, scenario_yi);
  else{
    clean_ball(xi, yi);
    draw_ball(*x, *y);
  }
}
