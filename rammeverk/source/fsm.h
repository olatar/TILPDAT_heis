#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "elev.h"


/**
  States for the FSM
*/
typedef enum {st_init, st_idle, st_running, st_door, st_EStop} state;

state FSM_current_state; 



//Boolean variables
int FSM_between_floors; 
int FSM_q_empty;
int FSM_stop_pressed;
int FSM_current_floor;
int FSM_desired_floor;


/**
 * Switch to state s.
*/
void FSM_set_state(state s);



/**
 * Initializing the FSM: Emptying queue, setting initial direction, resetting the direction space.
*/
void FSM_init();



/**
 * Event triggered by button press. Adds order to the queue, action depends on current state.
*/
void FSM_event_button(elev_button_type_t button, int floor);



/**
 * Event triggered by arriving at a floor.
*/
void FSM_event_floor(int floor);



/**
 * Returns the direction of the motor depending on current floor, wanted floor and direction space.
*/
elev_motor_direction_t FSM_decide_direction();




/**
 * Decicion making when stop button is pressed
*/
void FSM_stop_pressed_logic();




/**
 * Decicion making when stop button is depressed
*/
void FSM_stop_depressed_logic();



#endif
