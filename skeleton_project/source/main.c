#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include <functions.h>



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    int floor = elevio_floorSensor();

    if (floor == -1) { //hvis den ikke er i en definert etasje
        elevio_motorDirection(DIRN_DOWN);
        while (elevio_floorSensor() == -1) {
           //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        elevio_motorDirection(DIRN_STOP);
    }

    int orders[N_FLOORS][N_BUTTONS] = {0};

    //elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();

        // if(floor == 0){
        //     elevio_motorDirection(DIRN_UP);
        // }

        // if(floor == N_FLOORS-1){
        //     elevio_motorDirection(DIRN_DOWN);
        // }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1) {
                orders[f][b] = 1;
                }
                elevio_buttonLamp(f, b, orders[f][b]);   
            }
        }

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if ((orders[f][b] == 1) && (f < floor)) {
                    elevio_motorDirection(DIRN_DOWN);
                }
                else if ((orders[f][b] == 1) && (f > floor)) {
                    elevio_motorDirection(DIRN_UP);
                }
                else if ((orders[f][b] == 1) && (f == floor)){
                    elevio_motorDirection(DIRN_STOP);
                }
            
            }
        }

        int stop = 0;
        // for (int b = 0: b < N_BUTTONS )
        // if (floor != -1 && orders[floor][b == 1])

        
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
    
}
