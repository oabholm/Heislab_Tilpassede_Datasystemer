#include "driver/elevio.h"

extern int orders[N_FLOORS][2];

void initialize();

void addOrder(int floor, int direction);

void removeOrder(int floor);

int checkOrder();

void buttonLamp();

void stop();

void moveElevator(int floor);

void checkStop(int floor);

void openDoor();
