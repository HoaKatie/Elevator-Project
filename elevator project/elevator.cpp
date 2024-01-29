#include "elevator.h"

int Elevator::index = 1;

Elevator::Elevator(): eID(index++), currentFloor(1), currentWeight(0), startFloor(true), goingUp(false), goingDown(false), helpSignal(false), doorObstacle(false), overloaded(false) {}

Elevator::Elevator(int i): eID(i), currentFloor(1), currentWeight(0), startFloor(true), goingUp(false), goingDown(false), helpSignal(false), doorObstacle(false), overloaded(false) {}

Elevator::~Elevator(){}

int Elevator::getEID() {
    return eID;
}
int Elevator::getCurrentFloor() {return currentFloor;}
int Elevator::getCurrentWeight() {return currentWeight;}
void Elevator::setCurrentFloor(int floor) {currentFloor = floor;}
void Elevator::setCurrentWeight(int weight) {
    currentWeight = weight;
    if (currentWeight > maxWeight)
        overloaded = true;
    else
        overloaded = false;
}

void Elevator::moveToFloor(int floor) {currentFloor = floor;}

bool Elevator::isStartFloor() {return startFloor;}
bool Elevator::isGoingUp() {return goingUp;}
bool Elevator::isGoingDown() {return goingDown;}
void Elevator::toggleStartFloor() {startFloor = !startFloor;}
void Elevator::setGoingUp(bool goingUp) {this->goingUp = goingUp;}
void Elevator::setGoingDown(bool goingDown) {this->goingDown = goingDown;}

bool Elevator::receiveHelpSignal() {return helpSignal;}
bool Elevator::hasDoorObstacle() {return doorObstacle;}
bool Elevator::isOverloaded() {return overloaded;}
void Elevator::setHelpSignal(bool helpSignal) {this->helpSignal = helpSignal;}
void Elevator::setDoorObstacle(bool doorObstacle) {this->doorObstacle = doorObstacle;}

bool Elevator::hasWarning() {return helpSignal || doorObstacle || overloaded;}


QString Elevator::ringBell(){return "Bell Ringing";}
QString Elevator::openDoor() {return "Door Opening for 10 sec";}
QString Elevator::closeDoor() {return "Door Closing";}

QString Elevator::elevatorWarning() {
    QString message = "";

    if (doorObstacle) {
        message += "Please move from the Door.\n";
    }
    else if (overloaded) {
        message += "Overloaded! Please exit the elevator!\n";
    }
    else if (helpSignal) {
        message += "Helping: safety service is notified!\n";
    }

    return message;
}
