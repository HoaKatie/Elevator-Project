#include "ecs.h"

ECS::ECS(): totalFloorNo(4), totalElevatorNo(2), fire(false), powerOutage(false) {
    for (int i=0; i<totalElevatorNo; i++) {
        Elevator* e = new Elevator(i+1);
        elevators.append(e);
    }

    for (int i=0; i<totalFloorNo; i++) {
        Floor* f = new Floor(i+1);
        floors.append(f);
    }

}

ECS::ECS(int totalElevatorNo, int totalFloorNo): totalFloorNo(totalFloorNo), totalElevatorNo(totalElevatorNo), fire(false), powerOutage(false) {
    for (int i=0; i<totalElevatorNo; i++) {
        Elevator* e = new Elevator(i+1);
        elevators.append(e);
    }

    for (int i=0; i<totalFloorNo; i++) {
        Floor* f = new Floor(i+1);
        floors.append(f);
    }

}

ECS::~ECS() {
    for (Elevator* elevator: elevators) {
        delete elevator;
    }

    for (Floor* floor: floors) {
        delete floor;
    }
}

Elevator* ECS::getElevator(int eID) {return elevators[eID - 1];}
Floor* ECS::getFloor(int fID) {return floors[fID - 1];}

int ECS::getTotalFloorNo() {return totalFloorNo;}
int ECS::getTotalElevatorNo() {return totalElevatorNo;}
void ECS::setTotalFloorNo(int totalFloorNo) {this->totalFloorNo = totalFloorNo;}
void ECS::setTotalElevatorNo(int totalElevatorNo){this->totalElevatorNo = totalElevatorNo;}

bool ECS::hasPowerOutage() {return powerOutage;}
bool ECS::hasFire() {return fire;}
void ECS::setFire(bool fire) {this->fire = fire;}
void ECS::setPowerOutage(bool powerOutage) {this->powerOutage = powerOutage;}

bool ECS::hasEmergency() {return fire || powerOutage;}

void ECS::sendFireSignalToElevators() {
    for (Elevator *e: elevators) {
        e->moveToFloor(1);
    }
    fire = true;
}
void ECS::sendPowerOutageSignalToElevators() {
    for (Elevator *e: elevators) {
        e->moveToFloor(1);
    }
    powerOutage = true;
}

void ECS::sendRequestToElevator(int elevatorID, int floorID) {
    Elevator* e = elevators[elevatorID - 1];
    e->moveToFloor(floorID);
}

Elevator* ECS::findAvailableElevator(Floor* passengerOnFloor) {
    Elevator* chosenElevator = nullptr;
    int startFloor = passengerOnFloor->getFID();

    int minDistance = 100;

    //find the elevator closest to the passenger floor
    //choose elevator in Idle mode - 1st priority
    //choose elevator going in the same direction as the direction passenger on floor requests - 2nd priority

    for (Elevator* e: elevators) {

        if (!e->hasWarning()) {
            //if passenger request is Up and elevator is going Up but has already passed the floor -> continue
            if (e->isGoingUp() && passengerOnFloor->isRequestingUp() && (startFloor - e->getCurrentFloor() < 0)) continue;
            //if passenger request is Down and elevator is going Down but has already passed the floor -> continue
            if (e->isGoingDown() && passengerOnFloor->isRequestingDown() && (e->getCurrentFloor() - startFloor <0)) continue;

            //if there is a closer elevator that can pick up, then choose that elevator
            int distance = abs(e->getCurrentFloor() - startFloor);

            if (distance < minDistance || chosenElevator == nullptr) {
                minDistance = distance;
                chosenElevator = e;
            }
        }
    }
    return chosenElevator;
}


QString ECS::ecsWarning() {
    QString message = "";

    if (fire) {
        message += "Fire! Please exit when reach floor 1!\n";
    }
    else if (powerOutage) {
        message += "Power Outage! Please exit when reach floor 1!\n";
    }

    return message;
}
