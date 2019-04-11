#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__
#include "elev.h"


elev_motor_direction_t q_direction_space;

/**
 * Updates the order matrix, direction space and order lights
*/
void q_set_orders(elev_button_type_t button, int floor);


/**
 * Serves all orders at a given floor, updates lights.
*/
void q_remove_order(int floor);



/**
 * Determines the desired floor based on the current direction/elevator space nad the order matrix
*/
void q_set_desired_floor();



/**
 * Determines the overall direction of the carriage
*/
void q_set_direction_space();



/**
 * Resets the queue, sets all slots to zero, updates lights.
*/
void q_reset_orders(); //Empty all orders


#endif