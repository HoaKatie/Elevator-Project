#ifndef ECS_H
#define ECS_H

#include <QVector>
#include "elevator.h"
#include "floor.h"

class ECS
{
private:
    int totalFloorNo;
    int totalElevatorNo;

    bool fire;
    bool powerOutage;

    QVector<Elevator*> elevators;
    QVector<Floor*> floors;



public:
    ECS();
    ECS(int, int);
    ~ECS();

    int getTotalFloorNo();
    int getTotalElevatorNo();
    void setTotalFloorNo(int);
    void setTotalElevatorNo(int);

    bool hasFire();
    bool hasPowerOutage();
    void setFire(bool);
    void setPowerOutage(bool);

    bool hasEmergency();

    Elevator* getElevator(int);
    Floor* getFloor(int);

    void sendFireSignalToElevators();
    void sendPowerOutageSignalToElevators();

    void sendRequestToElevator(int, int);
    Elevator* findAvailableElevator(Floor*);

    QString ecsWarning();

};

#endif // ECS_H
