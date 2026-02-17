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
    //int btnPressed = elevio_callButton(floor, button);
    if ((button == 2) && (floor > elevio_floorSensor())) {
        orders[floor][0] = 1;
    }
    else if ((button == 2) && (floor < elevio_floorSensor())) {
        orders[floor][1] = 1;
    }
    else {
        orders[floor][button] = 1;
    }  if (floor == -1) {
        return;
    }
}

void removeOrder(int floor) {
    orders[floor][0] = 0;
    orders[floor][1] = 0;
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
    if (orders[floor][direction] == 1) {
        elevio_motorDirection(DIRN_STOP);
        removeOrder(floor);
        openDoor();
        // direction = 2;
        // return;
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
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                if (elevio_callButton(f,b)) {
                    addOrder(f,b);
                }
            }
        }
    }
    elevio_doorOpenLamp(0);
}


// void removeOrder(int floor, int direction) {
//     orders[floor][direction] = 0;
// }

// void stop() {
//     elevio_motorDirection(DIRN_STOP);
//     // int floor = elevio_floorSensor();
//     // if (orders[floor][dir] == 1)
//     //     elevio_motorDirection(DIRN_STOP);
//     //if (floor != -1 && )
// }

// void buttonLamp() {
//     for(int f = 0; f < N_FLOORS; f++){
//             for(int b = 0; b < N_BUTTONS; b++){
//                 int btnPressed = elevio_callButton(f, b);
//                 if (btnPressed == 1) {
//                 orders[f][b] = 1;
//                 }
//                 elevio_buttonLamp(f, b, orders[f][b]);   
//             }
//         }
// }