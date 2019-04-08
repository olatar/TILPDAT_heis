#include "queue.h"
#include "fsm.h"
#include <stdio.h>

static int orders[N_FLOORS][3]; //Matrix with orders


void q_set_orders(elev_button_type_t button, int floor){
    print_q();
    orders[floor][button] = 1; //Buttons: [0,1,2]
    q_set_direction_space();
    FSM_q_empty = 0;

}



void q_remove_order(floor){
    for(int i = 0; i < 3; i++){
        orders[floor][i] = 0;
    }
    FSM_q_empty = 1;    //Checking if the order table is empty
    for(int floor = 0; floor < N_FLOORS; floor++){
        for(int button = 0; button < 3; button++){
            if (orders[floor][button]) {
                FSM_q_empty = 0;
            }
        }
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
            thresh_floor = N_FLOORS-1;
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
            thresh_floor = 0;
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
            if (orders[i][BUTTON_COMMAND] || (orders[i][BUTTON_CALL_UP] && (FSM_desired_floor > i))) { //Update desired floor to the lowest in DIRN_UP
                FSM_desired_floor = i;
            }
            
        }
        
    }

    else if (direction_space == DIRN_DOWN) { //Only check orders that go down
        FSM_desired_floor = 0;
        for(int i = 0; i <= FSM_current_floor; i++) //No need to check lowest floor
        {
            if (orders[i][BUTTON_COMMAND] || (orders[i][BUTTON_CALL_DOWN] && (FSM_desired_floor < i))) { //Update desired floor to the highest in DIRN_DOWN
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



void print_q(){
    printf("\n\t0.\t1.\t2.\t3.\n");
    for(int i = 0; i < N_BUTTONS; i++){
        printf("%d\t", i);   
        for(int j = 0; j < N_FLOORS; j++)
        {
            printf("%d\t",orders[j][i]);
        }
        printf("\n\n");
    }
    
}

