/**
 * @file
 * @brief Library for the finite state machine of the elevator.
 * @details The module decide which action to take based on the current information every time a new event occur.
 */

#ifndef __INCLUDE_FSM_H__
#define __INCLUDE_FSM_H__

#include "elev.h"

/**
  @brief States for the FSM
*/
typedef enum {st_init, st_idle, st_running, st_door, st_stop_pressed, st_stop_depressed} state;

/**
  @brief Current state of the elevator.
*/
state FSM_current_state;

//Boolean variables
/**
  @brief Is the elevator between two floors.
*/
int FSM_between_floors; 
/**
  @brief Is the queue empty.
*/
int FSM_q_empty;
/**
  @brief Is the elevator between two floors.
*/
int FSM_between_floors; 
/**
  @brief Is the stop button pressed.
*/
int FSM_stop_pressed;
/**
  @brief Current floor.
*/
int FSM_current_floor;
/**
  @brief Desired floor.
*/
int FSM_desired_floor;

/**
 * @brief Change the state and update \link q_direction_space q_direction_space\endlink.
 * @details Set the necessary control values and execute the necessary functions such that the elevator changes state. 
 * Also, update \link FSM_current_state FSM_current_state\endlink and \link q_direction_space q_direction_space\endlink, however, \link q_direction_space q_direction_space\endlink is set manually when emergency stopped.
 * @param[in] s The state which will be changed to
 * @see References elev_set_motor_direction(elev_motor_direction_t dirn), elev_set_door_open_lamp(int value), elev_set_stop_lamp(int value) (Hardware),<br>
 * q_set_direction_space(), q_remove_order(int floor), q_remove_order(int floor) (Queue), timer_start(), timer_isTimeOut() (Timer)<br>
 * and FSM_decide_direction()<br>
 * Referenced by FSM_init(), FSM_event_button(elev_button_type_t button, int floor), FSM_event_floor(int floor), FSM_stop_pressed_logic() and FSM_stop_depressed_logic() 
*/
void FSM_set_state(state s);



/**
 * @brief Initialize the FSM.
 * @details Set \link FSM_current_state FSM_current_state\endlink to @c st_init, \link q_direction_space q_direction_space\endlink to @c DIRN_STOP, motor direction up and remove all orders.
 * \post The elevator will immediately observe if already at a floor, thus triggering further events. Therefore safe to set motor direction regardless of elevator positioning.
 * @see References elev_set_motor_direction(elev_motor_direction_t dirn) and q_reset_orders()<br>
 * Referenced by main()
*/
void FSM_init();



/**
 * @brief Trigger event because of button press: Add order to the queue and decide action to take based on current state.
 * @details As stated in \ref FSM_set_state(state s), \link q_direction_space q_direction_space\endlink is set manually when in emergency stopped condition.
 * @param[in] button The type of button that is pressed
 * @param[in] floor The floor which the button is pressed
 * @see References q_set_desired_floor(), q_set_orders(elev_button_type_t button, int floor) (Queue),
 * FSM_set_state(state s)<br>
 * Referenced by main()
*/
void FSM_event_button(elev_button_type_t button, int floor);



/**
 * @brief Trigger event when at a floor: Updates \link FSM_current_floor FSM_current_floor\endlink, set lights and decide action to take based on current state.
 * @param[in] floor The floor which the elevator has arrived on
 * @see References elev_set_floor_indicator(int floor), elev_set_motor_direction(elev_motor_direction_t dirn), elev_set_door_open_lamp(int value) (Hardware),
 * timer_isTimeOut() (Timer) and FSM_set_state(state s)<br>
 * Referenced by main()
*/
void FSM_event_floor(int floor);



/**
 * @brief Calculates the desired direction of the motor depending on \link FSM_current_floor FSM_current_floor\endlink, \link FSM_desired_floor FSM_desired_floor\endlink and \link q_direction_space q_direction_space\endlink.
 * @return The desired motor direction
 * @see References q_set_desired_floor()<br>
 * Referenced by FSM_set_state(state s)
*/
elev_motor_direction_t FSM_decide_direction();




/**
 * @brief Decision making when stop button is pressed.
 * @details Update lamp if not \link FSM_stop_pressed FSM_stop_pressed\endlink. Change the state if the current state is not @p st_stop_pressed.
 * @see References elev_set_stop_lamp(int value) and FSM_set_state(state s)<br>
 * Referenced by main()
*/
void FSM_stop_pressed_logic();




/**
 * @brief Decision making when stop button is depressed. Decision depends on if carriage is at a floor.
 * @details Change the state to \link st_stop_depressed st_stop_depressed\endlink, update \link FSM_stop_pressed FSM_stop_pressed\endlink and start the timer and turn of lamp if current state is \link st_stop_pressed st_stop_pressed\endlink.
 * @see References timer_start(), elev_set_stop_lamp(int value) and FSM_set_state(state s)<br>
 * Referenced by main()
*/
void FSM_stop_depressed_logic();



#endif
