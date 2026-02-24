#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "functions.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");

    initialize();
        
    while(1){
        int floor = elevio_floorSensor();


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if (elevio_callButton(f,b)) {
                    addOrder(f,b);
                }
            }
        }
        
        checkStop(floor);
        moveElevator(floor);
        


        
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            stopButton(floor);
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
    
}
