#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "functions.h"



int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    initialize();
        
    while(1){
        int floor = elevio_floorSensor();

        // if(floor == 0){
        //     elevio_motorDirection(DIRN_UP);
        // }

        // if(floor == N_FLOORS-1){
        //     elevio_motorDirection(DIRN_DOWN);
        // }
        //buttonLamp();

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if (elevio_callButton(f,b)) {
                    addOrder(f,b);
                }
            }
        }
        
        // for(int f = 0; f < N_FLOORS; f++){
        //     for(int b = 0; b < N_BUTTONS; b++){
        //         if ((orders[f][b] == 1) && (f < floor)) {
        //             elevio_motorDirection(DIRN_DOWN);
        //         }
        //         else if ((orders[f][b] == 1) && (f > floor)) {
        //             elevio_motorDirection(DIRN_UP);
        //         }
        //         else if ((orders[f][b] == 1) && (f == floor)){
        //             elevio_motorDirection(DIRN_STOP);
        //         }//int orders[N_FLOORS][N_BUTTONS] = {0};
            
        //     }
        // }
        moveElevator(floor);
        checkStop(floor);


        // if (floor != -1 && (orders[floor][0] || orders[floor][1])) {
        //     elevio_motorDirection(DIRN_STOP);
        // }

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
