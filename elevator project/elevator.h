#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QString>

class Elevator
{
private:
    static int index;
    int eID;

    int currentFloor;
    int currentWeight;

    bool startFloor;
    bool goingUp;
    bool goingDown;

    bool helpSignal;
    bool doorObstacle;
    bool overloaded;

public:
    const static int maxWeight = 500;

    Elevator();
    Elevator(int);
    ~Elevator();

    int getEID();

    int getCurrentFloor();
    int getCurrentWeight();
    void setCurrentFloor(int);
    void setCurrentWeight(int);

    bool isStartFloor();
    bool isGoingUp();
    bool isGoingDown();
    void toggleStartFloor();
    void setGoingUp(bool);
    void setGoingDown(bool);

    bool receiveHelpSignal();
    bool hasDoorObstacle();
    bool isOverloaded();
    void setHelpSignal(bool);
    void setDoorObstacle(bool);
    
    bool hasWarning();

    QString ringBell();
    QString openDoor();
    QString closeDoor();
    QString elevatorWarning();

    void moveToFloor(int);



};

#endif // ELEVATOR_H
