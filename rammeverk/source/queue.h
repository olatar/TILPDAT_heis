#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__
#include "elev.h"


elev_motor_direction_t direction_space;

/**
 * Updates the queue following the priority algorithm
 * NOT FINISHED
*/
void q_set_orders(elev_button_type_t button, int floor);


/**
 * Serves all orders at a given floor
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
 * Returns the nr.1 priority (?)
*/
int q_get_orders();



/**
 * Resets the queue, all slots to zero
*/
void q_reset_orders(); //Empty all orders



/**
 * Testing
*/
void print_q();


#endif