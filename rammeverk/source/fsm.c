#include "fsm.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>



void FSM_init(){
    elev_set_motor_direction(DIRN_UP);
    q_reset_orders();
    q_direction_space = DIRN_STOP;
    FSM_current_state = st_init;
}




void FSM_event_button(elev_button_type_t button, int floor) {
    switch (FSM_current_state)
    {
        case st_init: //Do nothing, let it initialize
            break;

        case st_idle: //Add to queue, change state
            q_set_orders(button,floor);
            if (floor == FSM_current_floor && !FSM_between_floors) {
                FSM_set_state(st_door);
            }
            else
            {
                FSM_set_state(st_running);
            }
            break;

        case st_running: //Add to queue
            q_set_orders(button,floor);
            q_set_desired_floor();
            break;

        case st_door: //Add to queue
            if (floor != FSM_current_floor) {
                q_set_orders(button,floor);
            }
            break;

        case st_stop_pressed: //Ingnore any orders while emergency stopped
            break;

        case st_stop_depressed: 
            q_set_orders(button,floor);

            //Special case if carriage is called to the just passed floor
            if (floor == FSM_current_floor) {
                if (q_direction_space == DIRN_UP) { //Pretends to have reached the next floor to avoid trouble
                    q_direction_space = DIRN_DOWN;
                    FSM_current_floor = N_FLOORS;
                }
                else if (q_direction_space == DIRN_DOWN) { //Pretends to have reached the next floor to avoid trouble
                    q_direction_space = DIRN_UP;
                    FSM_current_floor = -1;
                }              
            }  
            //Any other case
            else{
                q_direction_space = DIRN_STOP;
                q_set_direction_space();
            }
            FSM_set_state(st_running);
            break;

        default:
            break;
    }
}




void FSM_event_floor(int floor){

    //Update current floor and floor lights.
    FSM_current_floor = floor; 
    elev_set_floor_indicator(floor);

    switch (FSM_current_state)
    {
        case st_init: //Done initializing, set to idle.
            FSM_desired_floor = FSM_current_floor;
            FSM_set_state(st_idle);
            break;

        case st_idle: //Stay idle if no orders
            break;

        case st_running: //Stop only if reached desired floor.
            if ((floor == 0 && q_direction_space == DIRN_DOWN) || (floor == N_FLOORS -1 && q_direction_space == DIRN_UP)) {
                elev_set_motor_direction(DIRN_STOP);
            }
            if (FSM_current_floor == FSM_desired_floor) {
                FSM_set_state(st_door);
            }
            break;

        case st_door: //Wait for door to close, then move to idle or running
            if (timer_isTimeOut()) {
                elev_set_door_open_lamp(0);
                if (!FSM_q_empty) {
                    FSM_set_state(st_running);
                }
                else
                {
                    FSM_set_state(st_idle);
                }
            }
            
            break;

        case st_stop_pressed: //Do nothing while emergency stopped
            break;

        case st_stop_depressed: //Go to idle if at a floor
            FSM_set_state(st_idle);
            break;

        default:
            break;
    }

}




elev_motor_direction_t FSM_decide_direction(){
    
    q_set_desired_floor();

    

    if (FSM_desired_floor > FSM_current_floor) {
        return DIRN_UP;
    }
    else if(FSM_desired_floor < FSM_current_floor)
    {
        return DIRN_DOWN;
    }
    else
    {
        return DIRN_STOP;
    } 
}




void FSM_set_state(state s){

    //Update current state and direction space
    if (!(FSM_current_state == st_stop_pressed || FSM_current_state == st_stop_depressed)) {
        q_set_direction_space();
    }
    FSM_current_state = s;

    printf("Current state: %d\n", FSM_current_state);
    printf("Direction space: %d\n", q_direction_space);
    printf("Between floors: %d\n", FSM_between_floors);
    printf("Current floor: %d\n", FSM_current_floor);
    printf("Desired floor: %d\n\n", FSM_desired_floor);
    switch (FSM_current_state)
    {
        case st_idle:     
            elev_set_motor_direction(DIRN_STOP);
            q_direction_space = (DIRN_STOP);
            break;

        case st_running:
            elev_set_motor_direction(FSM_decide_direction());
            break;

        case st_door:
            timer_start();
            elev_set_motor_direction(DIRN_STOP);
            q_remove_order(FSM_current_floor); //All orders on this floor are served.
            elev_set_door_open_lamp(1);
            break;

        case st_stop_pressed: //Remove all orders, stop carriage, open door only if carriage is at a floor.
            elev_set_motor_direction(DIRN_STOP);
            q_reset_orders();
            elev_set_stop_lamp(1);
            if (!FSM_between_floors) {
                elev_set_door_open_lamp(1);
            }
            break;

        case st_stop_depressed: 
            if (!FSM_between_floors) {
                while(!timer_isTimeOut()){
                    //Busy wait
                }
                elev_set_door_open_lamp(0);
            }
            break;

        default:
            break;
    }
}




void FSM_stop_pressed_logic(){
    if (!FSM_stop_pressed) {
        elev_set_stop_lamp(1);
        FSM_stop_pressed = 1;
    }
    if (FSM_current_state != st_stop_pressed) { 
        FSM_set_state(st_stop_pressed);
    }  
}




void FSM_stop_depressed_logic(){
    //Make sure timer only starts once
    if (FSM_stop_pressed) {
        timer_start();
        elev_set_stop_lamp(0);
        FSM_stop_pressed = 0;
        FSM_set_state(st_stop_depressed);
    }
}