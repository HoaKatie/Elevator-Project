#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include "ecs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    ECS* ecs;
    static int testFloors;
    static int testElevators;

    void displayConsoleLogs(QString);
    void displayE1Floor(Elevator*);
    void displayE2Floor(Elevator*);
    void delay(int);


private slots:
    void onClickClearConsoleButton();

    void onClickFireButton();
    void onClickPowerOutageButton();
    void onClickResetButton();

    void onClickUpButton1();
    void onClickUpButton2();

    void onClickDownButton1();
    void onClickDownButton2();

    void onClickOpenButton1();
    void onClickOpenButton2();

    void onClickCloseButton1();
    void onClickCloseButton2();

    void onClickHelpButton1();
    void onClickHelpButton2();

    void onClickBlockDoorButton1();
    void onClickBlockDoorButton2();

    void onChangeStartFloor1();
    void onChangeStartFloor2();
    
    void onClickE1F1Button();
    void onClickE1F2Button();
    void onClickE1F3Button();
    void onClickE1F4Button();

    void onClickE2F1Button();
    void onClickE2F2Button();
    void onClickE2F3Button();
    void onClickE2F4Button();

    void onTypeE1Weight();
    void onTypeE2Weight();


};
#endif // MAINWINDOW_H
