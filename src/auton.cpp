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

  driveTurn(90, side, 80); // turn towards flags
  delay(800);
  driveDist(-6, 140); // back up

  delay(650);
  intake(0);
  index(200); // shoot
  delay(700);
  index(-1);
  delay(20);

  intake(200); // start pushing ball into indexer

  driveDist(24, 100); // aim for middle flag

  index(200); // 2nd shoot
  delay(800);

  flyWheel(0); // stop shooting devices
  intake(0);
  index(0);

  driveTurn(12, side, 100);
  delay(500);
  driveDist(23, 140); // turn into bottom flag and push then back up
  driveDist(-23, 140);

  driveTurn(-110, side, 100); // turn into cap
  delay(800);

  intake(-200);
  driveDist(35, 125); // flip cap  END OF NORMAL AUTON
  delay(500);
  driveDist(-10, 100);

  robotStop();
}

void secondAuton(int side){
  robotStop();
}

void skills(int side){
  //3 flags + 2 caps
  flyWheel(200);
  delay(250);
  intake(200);

  driveDist(38.0, 125); // to cap
  delay(250);
  driveDist(-36.0, 125); // back up

  driveTurn(90, side, 80); // turn towards flags
  delay(800);
  driveDist(-6, 140); // back up

  delay(650);
  intake(0);
  index(200); // shoot
  delay(700);
  index(-1);
  delay(20);

  intake(200); // start pushing ball into indexer

  driveDist(24, 100); // aim for middle flag

  index(200); // 2nd shoot
  delay(800);

  flyWheel(0); // stop shooting devices
  intake(0);
  index(0);

  driveTurn(12, side, 100);
  delay(500);
  driveDist(23, 140); // turn into bottom flag and push then back up
  driveDist(-23, 140);

  driveTurn(-110, side, 100); // turn into cap
  delay(800);

  intake(-200);
  driveDist(35, 125); // flip cap  END OF NORMAL AUTON
  delay(500);
  driveDist(-10, 100);

  driveTurn(12, side, 100); // turn
  delay(400);
  driveDist(-22, 150);

  driveTurn(-90, side, 85);
  delay(700);
  intake(0);
  driveDist(47, 150);

  driveTurn(85, side, 85);
  delay(700);

  driveDist(12, 85);

  driveDist(68, 150);

  left_front.move_relative(0, 0);
  left_back.move_relative(0, 0);
  right_front.move_relative(0, 0);
  right_back.move_relative(0, 0);

  robotStop();
}
