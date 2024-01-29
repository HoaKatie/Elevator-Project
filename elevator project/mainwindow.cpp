#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::testFloors = 4;
int MainWindow::testElevators = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,ecs(new ECS(testElevators,testFloors))
{
    ui->setupUi(this);

    //Add slots to GUI
    connect(ui->ClearConsoleButton, SIGNAL(released()), this, SLOT(onClickClearConsoleButton()));

    connect(ui->FireButton, SIGNAL(released()), this, SLOT(onClickFireButton()));
    connect(ui->PowerOutageButton, SIGNAL(released()), this, SLOT(onClickPowerOutageButton()));
    connect(ui->ResetButton, SIGNAL(released()), this, SLOT(onClickResetButton()));

    connect(ui->HelpButton1, SIGNAL(released()), this, SLOT(onClickHelpButton1()));
    connect(ui->HelpButton2, SIGNAL(released()), this, SLOT(onClickHelpButton2()));

    connect(ui->OpenButton1, SIGNAL(released()), this, SLOT(onClickOpenButton1()));
    connect(ui->OpenButton2, SIGNAL(released()), this, SLOT(onClickOpenButton2()));

    connect(ui->CloseButton1, SIGNAL(released()), this, SLOT(onClickCloseButton1()));
    connect(ui->CloseButton2, SIGNAL(released()), this, SLOT(onClickCloseButton2()));

    connect(ui->UpButton1, SIGNAL(released()), this, SLOT(onClickUpButton1()));
    connect(ui->UpButton2, SIGNAL(released()), this, SLOT(onClickUpButton2()));

    connect(ui->DownButton1, SIGNAL(released()), this, SLOT(onClickDownButton1()));
    connect(ui->DownButton2, SIGNAL(released()), this, SLOT(onClickDownButton2()));

    connect(ui->BlockDoorButton1, SIGNAL(released()), this, SLOT(onClickBlockDoorButton1()));
    connect(ui->BlockDoorButton2, SIGNAL(released()), this, SLOT(onClickBlockDoorButton2()));

    connect(ui->StartFloorOptions1, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeStartFloor1()));
    connect(ui->StartFloorOptions2, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeStartFloor2()));

    connect(ui->E1WeightInput, SIGNAL(textChanged(const QString &)), this, SLOT(onTypeE1Weight()));
    connect(ui->E2WeightInput, SIGNAL(textChanged(const QString &)), this, SLOT(onTypeE2Weight()));

    connect(ui->E1F1Button, SIGNAL(released()), this, SLOT(onClickE1F1Button()));
    connect(ui->E1F2Button, SIGNAL(released()), this, SLOT(onClickE1F2Button()));
    connect(ui->E1F3Button, SIGNAL(released()), this, SLOT(onClickE1F3Button()));
    connect(ui->E1F4Button, SIGNAL(released()), this, SLOT(onClickE1F4Button()));

    connect(ui->E2F1Button, SIGNAL(released()), this, SLOT(onClickE2F1Button()));
    connect(ui->E2F2Button, SIGNAL(released()), this, SLOT(onClickE2F2Button()));
    connect(ui->E2F3Button, SIGNAL(released()), this, SLOT(onClickE2F3Button()));
    connect(ui->E2F4Button, SIGNAL(released()), this, SLOT(onClickE2F4Button()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete ecs;
}


void MainWindow::displayConsoleLogs(QString message) {ui->ConsoleLogs->append(message);}

void MainWindow::displayE1Floor(Elevator* elevator) {delay(2); ui->E1Display->setText(QString::number(elevator->getCurrentFloor()));}
void MainWindow::displayE2Floor(Elevator* elevator) {delay(2); ui->E2Display->setText(QString::number(elevator->getCurrentFloor()));}

void MainWindow::delay(int sec) {
    while (QTime::currentTime() < QTime::currentTime().addMSecs(sec)) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

///////////////////////////////////////////////////////////////////
void MainWindow::onClickClearConsoleButton() {
    ui->ConsoleLogs->clear();
}


void MainWindow::onChangeStartFloor1() {
    QString str = "Passenger(s) is at Floor: ";
    QString floor = ui->StartFloorOptions1->currentText();
    str += floor;
    displayConsoleLogs(str);
    displayConsoleLogs("-------------------------");
}
void MainWindow::onChangeStartFloor2() {
    QString str = "Passenger(s) is at Floor: ";
    QString floor = ui->StartFloorOptions2->currentText();
    str += floor;
    displayConsoleLogs(str);
    displayConsoleLogs("-------------------------");
}


void MainWindow::onClickUpButton1() {
    if (ui->StartFloorOptions1->currentText() == "NA") {
        displayConsoleLogs("Please choose start floor 1");
        displayConsoleLogs("-------------------------");
        return;
    }
    int startFloor = ui->StartFloorOptions1->currentText().toInt();
    displayConsoleLogs("Requesting Up from Floor " + QString::number(startFloor));
    Elevator* elevator = ecs->findAvailableElevator(ecs->getFloor(startFloor));
    displayConsoleLogs("E" + QString::number(elevator->getEID()) + ": Moving from floor " + QString::number(elevator->getCurrentFloor()) + " to floor " + QString::number(startFloor) + " to pick up passenger(s)");
    displayConsoleLogs("-------------------------");
    elevator->setCurrentFloor(startFloor);
    elevator->setGoingUp(true);
    elevator->setGoingDown(false);
    ecs->getFloor(startFloor)->setRequestingUp(true);
    if (elevator->getEID() == 1) displayE1Floor(elevator);
    else displayE2Floor(elevator);
}
void MainWindow::onClickUpButton2() {
    if (ui->StartFloorOptions2->currentText() == "NA") {
        displayConsoleLogs("Please choose start floor 2");
        displayConsoleLogs("-------------------------");
        return;
    }
    int startFloor = ui->StartFloorOptions2->currentText().toInt();
    displayConsoleLogs("Requesting Up from Floor " + QString::number(startFloor));
    Elevator* elevator = ecs->findAvailableElevator(ecs->getFloor(startFloor));
    displayConsoleLogs("E" + QString::number(elevator->getEID()) + ": Moving from floor " + QString::number(elevator->getCurrentFloor()) + " to floor " + QString::number(startFloor) + " to pick up passenger(s)");
    displayConsoleLogs("-------------------------");
    elevator->setCurrentFloor(startFloor);
    elevator->setGoingUp(true);
    elevator->setGoingDown(false);
    ecs->getFloor(startFloor)->setRequestingUp(true);
    if (elevator->getEID() == 1) displayE1Floor(elevator);
    else displayE2Floor(elevator);
}


void MainWindow::onClickDownButton1() {
    if (ui->StartFloorOptions1->currentText() == "NA") {
        displayConsoleLogs("Please choose start floor 1");
        displayConsoleLogs("-------------------------");
        return;
    }
    int startFloor = ui->StartFloorOptions1->currentText().toInt();
    displayConsoleLogs("Requesting Down from Floor " + QString::number(startFloor));
    Elevator* elevator = ecs->findAvailableElevator(ecs->getFloor(startFloor));
    displayConsoleLogs("E" + QString::number(elevator->getEID()) + ": Moving from floor " + QString::number(elevator->getCurrentFloor()) + " to floor " + QString::number(startFloor) + " to pick up passenger(s)");
    displayConsoleLogs("-------------------------");
    elevator->setCurrentFloor(startFloor);
    elevator->setGoingDown(true);
    elevator->setGoingUp(false);
    ecs->getFloor(startFloor)->setRequestingDown(true);
    if (elevator->getEID() == 1) displayE1Floor(elevator);
    else displayE2Floor(elevator);
}
void MainWindow::onClickDownButton2() {
    if (ui->StartFloorOptions2->currentText() == "NA") {
        displayConsoleLogs("Please choose start floor 2");
        displayConsoleLogs("-------------------------");
        return;
    }
    int startFloor = ui->StartFloorOptions2->currentText().toInt();
    displayConsoleLogs("Requesting Down from Floor " + QString::number(startFloor));
    Elevator* elevator = ecs->findAvailableElevator(ecs->getFloor(startFloor));
    displayConsoleLogs("E" + QString::number(elevator->getEID()) + ": Moving from floor " + QString::number(elevator->getCurrentFloor()) + " to floor " + QString::number(startFloor) + " to pick up passenger(s)");
    displayConsoleLogs("-------------------------");
    elevator->setCurrentFloor(startFloor);
    elevator->setGoingDown(true);
    elevator->setGoingUp(false);
    ecs->getFloor(startFloor)->setRequestingDown(true);
    if (elevator->getEID() == 1) displayE1Floor(elevator);
    else displayE2Floor(elevator);
}

/*
You have to enter the start floor and request at least 1 direction from the start floor to enter the elevator and press a floor button.
*/
void MainWindow::onClickE1F1Button() {
    if (ui->StartFloorOptions1->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions1->currentText().toInt();
    int requestedFloor = 1;
    Elevator* elevator = ecs->getElevator(1);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(1, requestedFloor);
        displayConsoleLogs("E1: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);
        elevator->setGoingDown(!elevator->isGoingDown());
        elevator->setGoingUp(!elevator->isGoingUp());
        
        displayE1Floor(elevator);
        displayConsoleLogs("E1: " + elevator->ringBell());
        displayConsoleLogs("E1: " + elevator->openDoor());
        displayConsoleLogs("E1: Passenger(s) exit");
        displayConsoleLogs("E1: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE1F2Button() {
    if (ui->StartFloorOptions1->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions1->currentText().toInt();
    int requestedFloor = 2;
    Elevator* elevator = ecs->getElevator(1);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(1, requestedFloor);
        displayConsoleLogs("E1: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);

        displayE1Floor(elevator);
        displayConsoleLogs("E1: " + elevator->ringBell());
        displayConsoleLogs("E1: " + elevator->openDoor());
        displayConsoleLogs("E1: Passenger(s) exit");
        displayConsoleLogs("E1: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE1F3Button() {
    if (ui->StartFloorOptions1->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions1->currentText().toInt();
    int requestedFloor = 3;
    Elevator* elevator = ecs->getElevator(1);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(1, requestedFloor);
        displayConsoleLogs("E1: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);

        displayE1Floor(elevator);
        displayConsoleLogs("E1: " + elevator->ringBell());
        displayConsoleLogs("E1: " + elevator->openDoor());
        displayConsoleLogs("E1: Passenger(s) exit");
        displayConsoleLogs("E1: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE1F4Button() {
    if (ui->StartFloorOptions1->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions1->currentText().toInt();
    int requestedFloor = 4;
    Elevator* elevator = ecs->getElevator(1);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(1, requestedFloor);
        displayConsoleLogs("E1: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);
        elevator->setGoingDown(!elevator->isGoingDown());
        elevator->setGoingUp(!elevator->isGoingUp());
        
        displayE1Floor(elevator);
        displayConsoleLogs("E1: " + elevator->ringBell());
        displayConsoleLogs("E1: " + elevator->openDoor());
        displayConsoleLogs("E1: Passenger(s) exit");
        displayConsoleLogs("E1: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE2F1Button() {
    if (ui->StartFloorOptions2->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions2->currentText().toInt();
    int requestedFloor = 1;
    Elevator* elevator = ecs->getElevator(2);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(2, requestedFloor);
        displayConsoleLogs("E2: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);
        elevator->setGoingDown(!elevator->isGoingDown());
        elevator->setGoingUp(!elevator->isGoingUp());
        
        displayE2Floor(elevator);
        displayConsoleLogs("E2: " + elevator->ringBell());
        displayConsoleLogs("E2: " + elevator->openDoor());
        displayConsoleLogs("E2: Passenger(s) exit");
        displayConsoleLogs("E2: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE2F2Button() {
    if (ui->StartFloorOptions2->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions2->currentText().toInt();
    int requestedFloor = 2;
    Elevator* elevator = ecs->getElevator(2);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(2, requestedFloor);
        displayConsoleLogs("E2: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);

        displayE2Floor(elevator);
        displayConsoleLogs("E2: " + elevator->ringBell());
        displayConsoleLogs("E2: " + elevator->openDoor());
        displayConsoleLogs("E2: Passenger(s) exit");
        displayConsoleLogs("E2: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE2F3Button() {
    if (ui->StartFloorOptions2->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions2->currentText().toInt();
    int requestedFloor = 3;
    Elevator* elevator = ecs->getElevator(2);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(2, requestedFloor);
        displayConsoleLogs("E2: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);

        displayE2Floor(elevator);
        displayConsoleLogs("E2: " + elevator->ringBell());
        displayConsoleLogs("E2: " + elevator->openDoor());
        displayConsoleLogs("E2: Passenger(s) exit");
        displayConsoleLogs("E2: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onClickE2F4Button() {
    if (ui->StartFloorOptions2->currentText() == "NA") return;
    int startFloor = ui->StartFloorOptions2->currentText().toInt();
    int requestedFloor = 4;
    Elevator* elevator = ecs->getElevator(2);
    if (startFloor == requestedFloor && elevator->isStartFloor()) {elevator->toggleStartFloor(); return;}
    if (!ecs->getFloor(startFloor)->isRequestingDown() && !ecs->getFloor(startFloor)->isRequestingUp()) return;
    if (!elevator->hasWarning() && !ecs->hasEmergency()) {
        ecs->sendRequestToElevator(2, requestedFloor);
        displayConsoleLogs("E2: Moving to floor " + QString::number(requestedFloor));
        elevator->setCurrentFloor(requestedFloor);
        elevator->setGoingDown(!elevator->isGoingDown());
        elevator->setGoingUp(!elevator->isGoingUp());

        displayE2Floor(elevator);
        displayConsoleLogs("E2: " + elevator->ringBell());
        displayConsoleLogs("E2: " + elevator->openDoor());
        displayConsoleLogs("E2: Passenger(s) exit");
        displayConsoleLogs("E2: " + elevator->closeDoor());
        displayConsoleLogs("-------------------------");
    }
}


void MainWindow::onClickFireButton() {
    ecs->sendFireSignalToElevators();
    displayConsoleLogs("Fire! All elevators move to 1st floor");
    displayConsoleLogs("-------------------------");
    displayE1Floor(ecs->getElevator(1));
    displayE2Floor(ecs->getElevator(2));
}
void MainWindow::onClickPowerOutageButton() {
    ecs->sendPowerOutageSignalToElevators();
    displayConsoleLogs("Power Outage! All elevators move to 1st floor");
    displayConsoleLogs("-------------------------");
    displayE2Floor(ecs->getElevator(1));
    displayE1Floor(ecs->getElevator(2));
}
void MainWindow::onClickResetButton() {
    displayConsoleLogs("Reseting");
    displayConsoleLogs("-------------------------");
    ecs->setFire(false);
    ecs->setPowerOutage(false);
}

void MainWindow::onClickHelpButton1() {
    displayConsoleLogs("E1: Help is needed!");
    displayConsoleLogs("E1: Connecting to safety service");
    ecs->getElevator(1)->setHelpSignal(true);
    delay(2);
    displayConsoleLogs("E1: Open Door. Please exit for help");
    ecs->getElevator(1)->setHelpSignal(false);
    displayConsoleLogs("-------------------------");
}
void MainWindow::onClickHelpButton2() {
    displayConsoleLogs("E2: Help is needed!");
    displayConsoleLogs("E2: Connecting to safety service");
    ecs->getElevator(2)->setHelpSignal(true);
    delay(2);
    displayConsoleLogs("E2: Open Door. Please exit for help");
    ecs->getElevator(2)->setHelpSignal(false);
    displayConsoleLogs("-------------------------");

}

void MainWindow::onClickBlockDoorButton1() {
    displayConsoleLogs("E1: Door Obstacle Detected!");
    displayConsoleLogs("Please get away from the door");
    ecs->getElevator(1)->setDoorObstacle(true);
    delay(2);
    ecs->getElevator(1)->setHelpSignal(false);
    displayConsoleLogs("E1: Door Clear. Continue moving");
    displayConsoleLogs("-------------------------");
}
void MainWindow::onClickBlockDoorButton2() {
    displayConsoleLogs("E2: Door Obstacle Detected!");
    displayConsoleLogs("Please get away from the door");
    ecs->getElevator(2)->setDoorObstacle(true);
    delay(2);
    ecs->getElevator(2)->setHelpSignal(false);
    displayConsoleLogs("E2: Door Clear. Continue moving");
    displayConsoleLogs("-------------------------");
}

void MainWindow::onTypeE1Weight() {
    QString E1Weight = ui->E1WeightInput->text();
    int w = E1Weight.toInt();
    ecs->getElevator(1)->setCurrentWeight(w);
    if (ecs->getElevator(1)->isOverloaded()) {
        displayConsoleLogs("E1 Overload! Reduce the load now!");
        displayConsoleLogs("-------------------------");
    }
}
void MainWindow::onTypeE2Weight() {
    QString E2Weight = ui->E2WeightInput->text();
    int w = E2Weight.toInt();
    ecs->getElevator(2)->setCurrentWeight(w);
    if (ecs->getElevator(2)->isOverloaded()) {
        displayConsoleLogs("E2 Overload! Reduce the load now!");
        displayConsoleLogs("-------------------------");
    }
}

void MainWindow::onClickOpenButton1() {
    displayConsoleLogs("E1: Door Opening for 10 seconds");
    displayConsoleLogs("-------------------------");
    delay(2);
}
void MainWindow::onClickOpenButton2() {
    displayConsoleLogs("E2: Door Opening for 10 seconds");
    displayConsoleLogs("-------------------------");
    delay(2);
}

void MainWindow::onClickCloseButton1() {
    if (ecs->hasEmergency()) return;
    displayConsoleLogs("E1: Door Closing");
    displayConsoleLogs("-------------------------");
}
void MainWindow::onClickCloseButton2() {
    if (ecs->hasEmergency()) return;
    displayConsoleLogs("E2: Door Closing");
    displayConsoleLogs("-------------------------");
}








