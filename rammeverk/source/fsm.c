#include "fsm.h"
#include "elev.h"
#include "queue.h"




static state current_state = st_init; //Initial state



int FSM_current_floor;
int FSM_desired_floor; 



void FSM_init(){
    elev_set_motor_direction(DIRN_UP);
    FSM_q_empty = 1;
    q_reset_queue();
}




void event_button(elev_button_type_t button, int floor) {

    switch (current_state)
    {
        case st_init: //Do nothing, let it initialize
            break;
        case st_idle: //Add to queue, change state
            q_set_queue(button,floor);
            FSM_desired_floor = floor;
            FSM_set_state(st_running);
            break;

        case st_running: //Add to queue
            /* code */
            break;

        case st_door:
            /* code */
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
    switch (current_state)
    {
        case st_init:
            FSM_set_state(st_idle);
            break;

        case st_idle: //Stay idle if no orders
            break;

        case st_running:
            if (FSM_current_floor == FSM_desired_floor) {
                //Testing purpose only
                q_reset_queue(); 
                FSM_set_state(st_idle);
            }
            
            break;

        case st_door:
            /* code */
            break;

        case st_EStop:
            /* code */
            break;

        default:
            break;
    }

}




elev_motor_direction_t FSM_decide_direction(int this_floor, int desired_floor){
    if (desired_floor > this_floor) {
        return DIRN_UP;
    }
    else if(desired_floor < this_floor)
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
        case st_idle:       //Hvis noe i køen, hopp rett til st_running
            if (!FSM_q_empty) {
                FSM_set_state(st_running); 
            }
            elev_set_motor_direction(DIRN_STOP);
            break;

        case st_running:
            elev_set_motor_direction(FSM_decide_direction(FSM_current_floor, FSM_desired_floor));
            break;

        case st_door:
            /* code */
            break;

        case st_EStop:
            /* code */
            break;

        default:
            break;
    }
}