#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "elev.h"


/**
  States for the FSM
*/
typedef enum {st_init, st_idle, st_running, st_door, st_EStop} state;

static state current_state; 



//Boolean variables
int FSM_between_floors; 
int FSM_q_empty;
int FSM_stop_pressed;
int FSM_door_open; 

int FSM_current_floor;
int FSM_desired_floor;

/**
 * Switch to state s
*/
void FSM_set_state(state s);



/**
 * Initializing the FSM: Emptying queue, setting initial direction
*/
void FSM_init();



/**
 * Event triggered by button press. Triggers a state change
*/
void event_button(elev_button_type_t button, int floor);



/**
 * Event triggered by arriving at a floor. Triggers a state change
*/
void event_floor(int floor);



/**
 * Event triggered by the timer
*/
void event_time_is_out();



/**
 * Decides the direction of the motor depending on current and wanted floor
*/
elev_motor_direction_t FSM_decide_direction();





#endif
