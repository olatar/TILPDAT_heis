#include "fsm.h"
#include "elev.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>




static state current_state = st_init; //Initial state





void FSM_init(){
    elev_set_motor_direction(DIRN_UP);
    q_reset_orders();
    direction_space = DIRN_STOP;
}




void event_button(elev_button_type_t button, int floor) {

    printf("Desired floor = %d\n", FSM_desired_floor);
    printf("Space = %d\n", direction_space);
    printf("State = %d\n", (state)current_state);
    
    switch (current_state)
    {
        case st_init: //Do nothing, let it initialize
            break;
        case st_idle: //Add to queue, change state
            q_set_orders(button,floor);
            FSM_set_state(st_running);
            break;

        case st_running: //Add to queue
            q_set_orders(button,floor);
            q_set_desired_floor();
            break;

        case st_door: //Add to queue
            q_set_orders(button,floor);
            break;

        case st_EStop:
            /* code */
            break;

        default:
            break;
    }

}




void event_floor(int floor){
    FSM_current_floor = floor;
    elev_set_floor_indicator(floor);
    switch (current_state)
    {
        case st_init:
            FSM_desired_floor = FSM_current_floor;
            FSM_set_state(st_idle);
            break;

        case st_idle: //Stay idle if no orders
            break;

        case st_running:
            if (FSM_current_floor == FSM_desired_floor) {
                FSM_set_state(st_door);
            }
            break;

        case st_door:
            if (timer_isTimeOut()) {
                elev_set_door_open_lamp(0);
                FSM_set_state(st_idle);
            }
            
            break;

        case st_EStop:
            /* code */
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
    
    current_state = s;

    switch (current_state)
    {
        case st_idle:       
            elev_set_motor_direction(DIRN_STOP);
            break;

        case st_running:
            elev_set_motor_direction(FSM_decide_direction());
            break;

        case st_door:
            timer_start();
            elev_set_motor_direction(DIRN_STOP);
            q_remove_order(FSM_current_floor); //Order in this floor is served
            elev_set_door_open_lamp(1);
            break;

        case st_EStop:
            /* code */
            break;

        default:
            break;
    }
}