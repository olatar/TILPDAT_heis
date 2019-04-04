#include "timer.h"
#include "time.h"

time_t start_time;
time_t current_time;


void timer_start(){
    start_time = time(NULL);
}

int timer_isTimeOut(){
    current_time = time(NULL);

    double seconds_elapsed = difftime(current_time,start_time);
    if (seconds_elapsed >= 3) {
        return 1;
    }
    
    return 0;
}
