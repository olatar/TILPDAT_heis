#include "queue.h"
#include "fsm.h"
#include <stdio.h>

static int orders[N_FLOORS][3]; //Matrix with orders


void q_set_orders(elev_button_type_t button, int floor){
    orders[floor][button] = 1;
    elev_set_button_lamp(button,floor,1);
    //q_set_direction_space();
    FSM_q_empty = 0;

}



void q_remove_order(floor){
    for(int button = 0; button < 3; button++){
        orders[floor][button] = 0;
        if ((floor == 0 && (button == BUTTON_CALL_DOWN)) || (floor == N_FLOORS-1 && (button == BUTTON_CALL_UP))) {
            continue;
        }
        elev_set_button_lamp(button,floor,0);
    }

    //Checking if the order table is empty
    FSM_q_empty = 1;    
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int button = 0; button < 3; button++){
            if (orders[floor][button]) {
                FSM_q_empty = 0;
            }
        }
    }
}




void q_set_direction_space(){

    int order = FSM_current_floor;
    
    switch (q_direction_space){

        case DIRN_STOP: //Find the direction to any order. If no orders, remain in DIRN_STOP
            for(int floor = 0; floor < N_FLOORS; floor++){
                for(int button = 0; button < 3; button++){
                    if (orders[floor][button]) {
                        order = floor;
                    }
                }
            }
            if (order > FSM_current_floor) {
                q_direction_space = DIRN_UP;
            }
            else if (order < FSM_current_floor){
                q_direction_space = DIRN_DOWN;
            }
            break;
        
        case DIRN_UP: //Finds the highest ordered floor in the up direction space. Update direction space only when reached.
            order = N_FLOORS-1;
            for(int floor = FSM_current_floor; floor < N_FLOORS; floor++){
                for(int button = 0; button < 3; button++){
                    if (orders[floor][button]) {
                        order = floor; 
                    }
                }
            }
            if (FSM_current_floor == order) {
                q_direction_space = DIRN_STOP;
            }

            
            
            break;
        
        case DIRN_DOWN: //Finds the lowest ordered floor in the down direction space. Update direction space only when reached.
            order = 0;
            for(int floor = FSM_current_floor; floor >= 0; floor--){
                for(int button = 0; button < 3; button++){
                    if (orders[floor][button]) {
                        order = floor;
                    }
                }
            }
            if (FSM_current_floor == order) {
                    q_direction_space = DIRN_STOP;
            }
            break;
    
        default:
            break;
    }
}



void q_set_desired_floor(){ //Iterates through orders in the current elevator space to determine where to go next

    if (q_direction_space == DIRN_UP) { //Only check orders that go up

        for(int i = FSM_current_floor+1; i <= N_FLOORS-1; i++){
            //Update desired floor to the lowest ordered floor in DIRN_UP
            if (orders[i][BUTTON_CALL_DOWN]) { 
                FSM_desired_floor = i;
            }
        }
        for(int i = N_FLOORS-1; i >= FSM_current_floor+1; i--){
            //Update desired floor to the lowest ordered floor in DIRN_UP
            if (orders[i][BUTTON_COMMAND] || orders[i][BUTTON_CALL_UP]) { 
                FSM_desired_floor = i;
            }
        }
    }

    else if (q_direction_space == DIRN_DOWN) { //Only check orders that go down

        for(int i = FSM_current_floor-1; i >= 0; i--){
            //Update desired floor to the lowest ordered floor in DIRN_UP
            if (orders[i][BUTTON_CALL_UP]) { 
                FSM_desired_floor = i;
            }
        }

        for(int i = 0; i <= FSM_current_floor-1; i++){
            //Update desired floor to the lowest ordered floor in DIRN_UP
            if (orders[i][BUTTON_COMMAND] || orders[i][BUTTON_CALL_DOWN]) { 
                FSM_desired_floor = i;
            }
        }
    }
}




void q_reset_orders(){
    for(int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < 3; j++){
            orders[i][j] = 0;
            if ((i == 0 && (j == BUTTON_CALL_DOWN)) || (i == N_FLOORS-1 && (j == BUTTON_CALL_UP))) {
                continue;
            }
            elev_set_button_lamp(j,i,0);
        }
    }
    FSM_q_empty = 1;
}

