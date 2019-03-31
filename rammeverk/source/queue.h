#include "elev.h"
#include "fsm.h"

void q_set_queue(elev_button_type_t button); //Add the order to the queue folling an algorithm to decide its priority
int q_get_queue(); //Returns the first order in the queue
void q_reset_queue(); //Empty all orders