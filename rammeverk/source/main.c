#include "elev.h"
#include "fsm.h"
#include <stdio.h>


int main(){

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    FSM_init();

    while(1){
        
        
        // Get stop signal
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
        

        //Get floor signal
        int floor = elev_get_floor_sensor_signal();
        if (floor != -1) {
            event_floor(floor);
        }
        
        
        //Get button signals
        for(int button = 0; button < 3; button++){
            for(int floor = 0; floor < N_FLOORS; floor++){
                
                //Avoid assert (fail for buttons that dont exist)
                if ( (floor == N_FLOORS - 1 && button == BUTTON_CALL_UP ) || (floor == 0 && button == BUTTON_CALL_DOWN)) {
                    continue;
                }
                
                if (elev_get_button_signal(button, floor)) {
                    event_button(button, floor);
                }
            }
        }   
    }

    
    
    return 0;
}








    /*
    EXAMPLE PROGRAM

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    elev_set_motor_direction(DIRN_STOP);

    while(1){

    if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
        elev_set_motor_direction(DIRN_DOWN);
    } else if (elev_get_floor_sensor_signal() == 0) {
        elev_set_motor_direction(DIRN_UP);
    }

    
    if (elev_get_button_signal(BUTTON_CALL_UP,2)) {
        elev_set_motor_direction(DIRN_UP);
    }
    else if(elev_get_button_signal(BUTTON_CALL_DOWN,2))
    {
        elev_set_motor_direction(DIRN_DOWN);
    }
    
    if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
    
    */