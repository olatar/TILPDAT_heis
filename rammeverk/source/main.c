/**
 * @file
 * @brief Main function of the project, which contains the logic of the event manager module.
 */

#include "elev.h"
#include "fsm.h"
#include "queue.h"
#include "timer.h"
#include <stdio.h>

/**
 * @brief Main function of the project: an initialization, then an infinite loop polling floor and button events.
 * @warning If elev_get_stop_signal() return @c 0, then main() will end, returning @c 1.
 * @see References elev_init(), elev_get_stop_signal(), elev_get_floor_sensor_signal(), elev_get_button_signal(elev_button_type_t button, int floor) (Hardware), 
 * FSM_stop_pressed_logic(), FSM_stop_depressed_logic(), FSM_event_floor(int floor) and FSM_event_button(elev_button_type_t button, int floor) (FSM)
*/
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