#include "functions.h"

int orders[N_FLOORS][2] = {0};
int direction = 0;

void initialize() {
    int floor = elevio_floorSensor();

    if (floor == -1) { //hvis den ikke er i en definert etasje
        elevio_motorDirection(DIRN_DOWN);
        while (elevio_floorSensor() == -1) {
           //nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }
        elevio_motorDirection(DIRN_STOP);
    }
}

void addOrder(int floor, int button) {
    //int btnPressed = elevio_callButton(floor, button);
    if (button == 2 && floor > elevio_floorSensor()) {
        orders[floor][0] = 1;
    }
    else if (button == 2 && floor < elevio_floorSensor()) {
        orders[floor][1] = 1;
    }
    else {
        orders[floor][button] = 1;
    }  
}

void removeOrder(int floor, int direction) {
    orders[floor][direction] = 0;
}

void stop() {
    MotorDirection(DIRN_STOP);
    // int floor = elevio_floorSensor();
    // if (orders[floor][dir] == 1)
    //     elevio_motorDirection(DIRN_STOP);
    //if (floor != -1 && )
}

void buttonLamp() {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1) {
                orders[f][b] = 1;
                }
                elevio_buttonLamp(f, b, orders[f][b]);   
            }
        }
}