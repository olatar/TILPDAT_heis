#include "fsm.h"

state current_state = st_init;
int FSM_current_floor;
int FSM_desired_floor; 

//Boolean variables
int FSM_between_floors; 
int FSM_q_empty;
int FSM_stop_pressed;
int FSM_door_open; 
