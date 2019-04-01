#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__
#include "elev.h"


/**
 * Updates the queue following the priority algorithm
 * NOT FINISHED
*/
void q_set_queue(elev_button_type_t button, int floor);



/**
 * Returns the nr.1 priority (?)
*/
int q_get_queue();



/**
 * Resets the queue, all slots to zero
*/
void q_reset_queue(); //Empty all orders



#endif