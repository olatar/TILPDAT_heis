#include "elev.h"
#include "fsm.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>


int main(){

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    FSM_init();

    printf("Current state: %d\n\n", FSM_current_state);

    while(1){
        
        // Manage stop event
        if (elev_get_stop_signal()) {
            FSM_stop_pressed_logic();
            continue;
        }
        else{
            FSM_stop_depressed_logic();
        }
        
        

        //Manage floor event
        int floor = elev_get_floor_sensor_signal();
        if (floor != -1) {
            FSM_between_floors = 0;
            FSM_event_floor(floor);
        }
        else{
            FSM_between_floors = 1;
        }
        
        
        
        //Manage button event
        for(int button = 0; button < 3; button++){
            for(int floor = 0; floor < N_FLOORS; floor++){
                
                //Avoid assert (fail for buttons that dont exist)
                if ( (floor == N_FLOORS - 1 && button == BUTTON_CALL_UP ) || (floor == 0 && button == BUTTON_CALL_DOWN)) {
                    continue;
                }
                
                if (elev_get_button_signal(button, floor)) {
                    FSM_event_button(button, floor);
                }
            }
        }
    }

    return 0;
}