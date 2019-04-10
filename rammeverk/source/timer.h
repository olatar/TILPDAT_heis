#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

/**
 * Sets start_time to the current time when the function is called.
**/
void timer_start();



/**
 * Sets current_time to the time current time when the function is called. 
 * Returns 1 if the difference between current time and start time is
 * greater than 3. Returns 0 otherwise.
**/
int timer_isTimeOut(); //Boolean

#endif
