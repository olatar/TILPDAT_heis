/**
 * @file
 * @brief Library for the queue of the elevator.
 */

#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__
#include "elev.h"

/**
 * @brief The overall direction of the carriage
 * @details The direction will remain the same until all orders on all floors in one direction are handled.
*/
elev_motor_direction_t q_direction_space;

/**
 * @brief Updates the order matrix, direction space and order lights
 * @param[in] button The type of button that is pressed
 * @param[in] floor The floor which the button is pressed
 * @see References elev_set_button_lamp(elev_button_type_t button, int floor, int value)<br>
 * Referenced by FSM_event_button(elev_button_type_t button, int floor)
*/
void q_set_orders(elev_button_type_t button, int floor);


/**
 * Serve all orders at a given floor, updates lights.
 * @param[in] floor Floor where the orders are removed from
 * @see Referenced by FSM_set_state(state s)
*/
void q_remove_order(int floor);



/**
 * @brief Iterate through the order matrix and decide where to go next based on 
 * the current q_direction_space and the orders.
 * @see Referenced by FSM_event_button(elev_button_type_t button, int floor) and FSM_decide_direction()
*/
void q_set_desired_floor();



/**
 * @brief Determine the overall direction of the carriage, that is, updating \link q_direction_space q_direction_space\endlink
 * @see Referenced by FSM_set_state(state s) and FSM_event_button(elev_button_type_t button, int floor)
*/
void q_set_direction_space();



/**
 * @brief Resets the queue, sets all slots to zero and updates lights.
 * @see References elev_set_button_lamp(elev_button_type_t button, int floor, int value)<br>
 * Referenced by FSM_init() and FSM_set_state(state s)
*/
void q_reset_orders(); //Empty all orders


#endif