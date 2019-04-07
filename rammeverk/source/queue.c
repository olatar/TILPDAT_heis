#include "queue.h"
#include "fsm.h"

static int orders[N_FLOORS][3]; //Matrix with orders


void q_set_orders(elev_button_type_t button, int floor){
    orders[floor][button+1] = 1; //Buttons: [-1,0,1]
    q_set_direction_space();
    FSM_q_empty = 0;

}



void q_remove_order(floor){
    for(int i = 0; i < 3; i++)
    {
        orders[floor][i] = 0;
    }
}




void q_set_direction_space(){ //Kan spare noen linjer på å lage if() i stedet..
    int order = FSM_current_floor; //Initializing the variable to avoid trouble
    int thresh_floor = -1; //To avoid trouble

    switch (direction_space)
    {
        case DIRN_STOP: //Find the direction to any order
            for(int floor = 0; floor < N_FLOORS; floor++){
                for(int button = 0; button < 3; button++){
                    if (orders[floor][button]) {
                        order = floor;
                    }
                }
            }
            if (order > FSM_current_floor) {
                direction_space = DIRN_UP;
            }
            else if (order < FSM_current_floor){
                direction_space = DIRN_DOWN;
            }
            break;
        
        case DIRN_UP:
            for(int floor = FSM_current_floor; floor < N_FLOORS; floor++){
                for(int button = 0; button < 3; button++){
                    if (orders[floor][button]) {
                        thresh_floor = floor; //Finds the highest ordered floor in the up direction space
                    }
                }
            }
            if (FSM_current_floor == thresh_floor) {
                direction_space = DIRN_STOP;
            }
            
            break;
        
        case DIRN_DOWN:
            for(int floor = FSM_current_floor; floor >= 0; floor--){
                for(int button = 0; button < 3; button++){
                    if (orders[floor][button]) {
                        thresh_floor = floor; //Finds the lowest ordered floor in the down direction space
                    }
                }
            }
            if (FSM_current_floor == thresh_floor) {
                direction_space = DIRN_STOP;
            }
            break;
    
        default:
            break;
    }
}



void q_set_desired_floor(){ //Iterates through orders in the elevator space to determine where to go next

    if (direction_space == DIRN_UP) { //Only check orders that go up
        FSM_desired_floor = N_FLOORS-1;
        for(int i = FSM_current_floor; i < N_FLOORS-1; i++) //No need to check highest floor
        {
            if (orders[i][DIRN_UP+1] && (FSM_desired_floor > i)) { //Update desired floor to the lowest in DIRN_UP
                FSM_desired_floor = i;
            }
            
        }
        
    }

    else if (direction_space == DIRN_DOWN) { //Only check orders that go down
        FSM_desired_floor = 0;
        for(int i = FSM_current_floor; i > 0; i--) //No need to check lowest floor
        {
            if (orders[i][DIRN_DOWN+1] && (FSM_desired_floor < i)) { //Update desired floor to the highest in DIRN_DOWN
                FSM_desired_floor = i;
            }
            
        }
    }
}





void q_reset_orders(){
    for(int i = 0; i < N_FLOORS; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            orders[i][j] = 0;
        }
    }
    FSM_q_empty = 1;
}




