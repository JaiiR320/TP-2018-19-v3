#include "main.h"

int Acolor = 1;
int Aauton = 1;

void mainAuton(int side){
  //3 flags + 2 caps
  flyWheel(200);
  intake(200);

  driveDist(39, 200); // to cap
  delay(500);
  driveDist(-36, 200); // back up

  driveTurn(90, side, 100); // turn towards flags
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
  driveTurn(-50, side, 100); // turn into bottom
  driveDist(6, 100);
  driveDist(-6, 100);
  driveTurn(50, side, 100); // turn out

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
  // cap, 2 high flags, cap on pole, park (brian auton)
  flyWheel(200);
  intake(200);

  driveDist(39, 200); // to cap
}

void safeAuton(int side){
  driveArc(48.0, 90, side, 100); //right 86.393 | left 64.402
  delay(4000);
  driveDist(-36, 200);
  driveTurn(90, side, 200);
  delay(2000);

  robotStop();
}
