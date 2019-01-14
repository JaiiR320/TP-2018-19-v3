#include "main.h"

int Acolor = 2;
int Aauton = 2;

void mainAuton(int side){
  //3 flags + 2 caps
  flyWheel(200);
  delay(250);
  intake(200);

  driveDist(38.0, 125); // to cap
  delay(250);
  driveDist(-36.0, 125); // back up

  driveTurn(91, side, 80); // turn towards flags
  delay(800);
  driveDist(0, 140); // back up

  delay(450);
  intake(0);
  index(200); // shoot
  delay(700);
  index(-1);
  delay(20);

  intake(200); // start pushing ball into indexer

  driveDist(24, 100); // aim for middle flag

  index(200); // 2nd shoot
  delay(750);

  flyWheel(0); // stop shooting devices
  intake(0);
  index(0);

  driveTurn(12, side, 100);
  delay(500);
  driveDist(23, 140); // turn into bottom flag and push then back up
  driveDist(-23, 140);

  driveTurn(-112, side, 100); // turn into cap
  delay(800);

  intake(-200);
  driveDist(25, 125); // flip cap
  delay(500);

  robotStop();
}

void secondAuton(int side){
  lift_mtr.tare_position();
  flyWheel(200);
  intake(200);
  driveDist(38, 200); // to cap & drop
  driveDist(-12, 100); // back up slightly

  driveTurn(135, side, 100); // turn into cap
  delay(1200);

  driveDist(-24, 150);
  liftSet(0, 100);  // lift cap
  delay(700);

  driveTurn(45, side, 100); // turn towards pole
  delay(600);

  driveDist(36, 150);
  liftSet(1, 100); // place cap on pole
  delay(1200);

  driveDist(-18, 100); // back up
  driveTurn(-90, side, 100);

  driveDist(24, 100);
  driveTurn(-45, side, 100); // turn to flags

  index(200);
  delay(300);
  intake(200); // shoot
  delay(3000);

  robotStop();
}

void safeAuton(int side){
}
