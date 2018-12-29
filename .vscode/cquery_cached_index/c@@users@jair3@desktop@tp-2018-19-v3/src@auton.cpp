#include "main.h"

int Acolor = 2;
int Aauton = 2;

void mainAuton(int side){
  //3 flags + 2 caps
  flyWheel(200);
  intake(200);

  driveDist(39, 140); // to cap
  delay(500);
  driveDist(-36, 140); // back up

  driveTurn(90, side, 75); // turn towards flags
  driveDist(-4, 100);

  intake(200);
  index(200); // shoot
  delay(400);
  index(0);

  driveDist(20, 100); // aim for middle flag

  intake(200);
  index(200); // shoot
  delay(700);

  flyWheel(0); // stop shooting devices
  intake(0);
  index(0);

  driveDist(32, 100); // drive into bottom flag
  driveTurn(-50, side, 100); // turn into bottom
  driveDist(6, 100);
  driveDist(-6, 100);
  driveTurn(50, side, 100); // turn out
  delay(1000);

  driveDist(-42, 200);
  driveTurn(-105, side, 150); // turn into second cap

  intake(-200);
  driveDist(24, 50); // flip cap
  driveDist(-12, 200);

  driveTurn(45, side, 200); // drive into low flag
  driveDist(30, 200);

  robotStop();
}

void secondAuton(int side){
  drivePPos(24.0, 24.0);
}

void safeAuton(int side){

}
