#include "elev.h"
#include <stdio.h>

typedef enum {st_init, st_idle, st_running, st_door, st_EStop} state;

void FSM_set_state(state s);


void event_button(elev_button_type_t button);
void event_floor(int floor);
void event_time_is_out();


