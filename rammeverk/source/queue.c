#include "queue.h"
#include "fsm.h"

static int q_queue[10]; 


void q_set_queue(elev_button_type_t button, int floor){
    q_queue[0] = floor;
    FSM_q_empty = 0;

}


void q_reset_queue(){
    for(int i = 0; i < 10; i++)
    {
        q_queue[i] = 0;
    }
}


