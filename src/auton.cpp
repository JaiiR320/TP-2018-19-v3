#include "main.h"

int Acolor = 2;
int Aauton = 2;

void mainAuton(int side){
  //3 flags + 2 caps
  flyWheel(200);
  delay(250);
  intake(200);

  driveDist(38.0, 125); // to cap
  delay(400);
  driveDist(-35.0, 125); // back up

  driveTurn(90, side, 75); // turn towards flags
  delay(800);
  driveDist(-5, 120); // back up

  delay(800);
  intake(0);
  index(200); // shoot
  delay(700);
  index(0);

  driveDist(28, 100); // aim for middle flag

  intake(200);
  index(200); // shoot
  delay(800);

  flyWheel(0); // stop shooting devices
  intake(0);
  index(0);

  driveTurn(25, side, 100);
  delay(600);
  driveDist(18, 140); // turn into bottom flag and push then back up
  driveDist(-18, 140);

  driveTurn(-135, side, 100); // turn into cap
  delay(800);

  intake(-200);
  driveDist(18, 100); // flip cap

  driveTurn(55, side, 200);
  delay(800);
  driveDist(32, 200);
  driveTurn(-100, side, 200); // bolt to flag and turn into it
  delay(1000);

  robotStop();
}

void secondAuton(int side){
}

void safeAuton(int side){
}
