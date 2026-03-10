#include "functions.h"
#include <time.h>



int orders[N_FLOORS][2] = {0};
int direction = 2; //direction

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
    
    if ((button == 2) && (floor > elevio_floorSensor())) {
        orders[floor][0] = 1;
        elevio_buttonLamp(floor, button, 1);
    }
    else if ((button == 2) && (floor < elevio_floorSensor())) {
        orders[floor][1] = 1;
        elevio_buttonLamp(floor, button, 1);
    }
    else if ((button == 2) && (floor == elevio_floorSensor())) { // Bør kanskje kommenteres ut
        openDoor();
    }
    else {
        orders[floor][button] = 1;
        elevio_buttonLamp(floor, button, 1);
    }  if (floor == -1) {
        return;
    }
}

void removeOrder(int floor) {
    if(floor == 0) {
        orders[floor][0] = 0;
        orders[floor][1] = 0;
        elevio_buttonLamp(floor, 0, 0);
    } else if(floor == 3) {
        orders[floor][1] = 0;
        orders[floor][0] = 0;
        elevio_buttonLamp(floor, 1, 0);

    } else {
        orders[floor][direction] = 0;
        elevio_buttonLamp(floor, direction, 0);

    }
    elevio_buttonLamp(floor, 2, 0);
}

void moveElevator(int floor) {
    if (floor == -1) {
        return;
    }

    for (int f = 0; f < N_FLOORS; f++) {
        if (f < floor && (orders[f][0] || orders[f][1])) {
            elevio_motorDirection(DIRN_DOWN);
            direction = 1;
            return;
        }
        else if (f > floor && (orders[f][0] || orders[f][1])) {
            elevio_motorDirection(DIRN_UP);
            direction = 0;
            return;
        }
    }
    elevio_motorDirection(DIRN_STOP);
}

void checkStop(int floor) {
    if (floor == -1) {
        return;
    }
    elevio_floorIndicator(floor);
    if (orders[floor][direction] == 1) {
        elevio_motorDirection(DIRN_STOP);
        removeOrder(floor);
        openDoor();

    } 
    else if ((orders[floor][0] || orders[floor][1]) && ((floor == 3 )|| (floor == 0))) {
        elevio_motorDirection(DIRN_STOP);
        removeOrder(floor);
        openDoor();
    }
}

void openDoor() {
    elevio_doorOpenLamp(1);


    time_t start = time(NULL);

    while (time(NULL) - start < 3) {
        if(elevio_obstruction()) {
            break;
        }
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if (elevio_callButton(f,b)) {
                    addOrder(f,b);
                }
            }
        }
    }
    obstruction();
    elevio_doorOpenLamp(0);
}

void obstruction() {
    if (elevio_obstruction()) {
    while (elevio_obstruction()) {}
    openDoor();
    }
}


void stopButton(int floor) {
    elevio_motorDirection(DIRN_STOP);
            for (int f = 0; f < N_FLOORS; f++) {
                elevio_buttonLamp(f, 0, 0);
                elevio_buttonLamp(f, 1, 0);
                elevio_buttonLamp(f, 2, 0);
                orders[f][0] = 0;
                orders[f][1] = 0;
            }
             if (floor != -1) {
                 elevio_doorOpenLamp(1);
                 while(elevio_stopButton()){
                    elevio_stopLamp(1);
                 }
                 openDoor();
                 elevio_stopLamp(0);
             } else{
                while(elevio_stopButton()){
                    elevio_stopLamp(1);
                }
                elevio_stopLamp(0);
                initialize();
             }
}
