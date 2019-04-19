/**
 * @file
 * @brief Library of functions creating a timer for the elevator.
 */

#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__

/**
 * @brief Set start_time to the current time.
 * @see Referenced by FSM_set_state(state s)
**/
void timer_start();



/**
 * @brief Check if timer is finished.
 * @return 1 if the difference between current time and start time is
 * greater than 3, 0 otherwise.
 * @see Referenced by FSM_event_floor(int floor)
**/
int timer_isTimeOut();

#endif
