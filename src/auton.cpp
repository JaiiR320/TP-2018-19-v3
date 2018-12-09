#include "main.h"

int Acolor = 0;
int Aauton = 0;

void mainAuton(int side){
    //3 flags + 2 caps
    flyWheelSet(200);
    intake(200);

    driveDist(39, 200); // to cap
    driveDist(-36, 200); // back up

    driveTurn(side * 90); // turn towards flags
    driveDist(4, 100); // aim for top flag

    intake(200);
    index(200); // shoot
    delay(400);
    index(0);

    driveDist(21, 100); // aim for middle flag

    intake(200);
    index(200); // shoot
    delay(700);
    
    flyWheel(0); // stop shooting devices
    intake(0);
    index(0);

    driveDist(32, 100); // drive into bottom flag
    driveTurn(side * -50, 100);
    driveDist(6, 100);
    driveDist(-6, 100);
    driveTurn(side * 50, 100);

    driveDist(-42, 200);
    driveTurn(side * -105, 150); // turn into second cap

    intake(-200);
    driveDist(24, 50); // flip cap
    driveDist(-12, 200);

    driveTurn(side * 45, 200); // drive into low flag
    driveDist(30, 200);

    robotStop();
}

void secondAuton(int side){
    // cap, 2 high flags, cap on pole, park (brian auton)
    flyWheelSet(200);
    intake(200);

    driveDist(39, 200); // to cap
}

void safeAuton(int side){

}