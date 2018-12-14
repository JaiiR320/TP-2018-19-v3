#ifndef ROBOT_H
#define ROBOT_H

#include "api.h"
using namespace pros;

extern Controller master;
extern Controller partner;

extern Motor left_back;
extern Motor right_back;
extern Motor left_front;
extern Motor right_front;

extern Motor flywheel_mtr;

extern Motor intake_mtr;
extern Motor index_mtr;

extern Motor lift_mtr;

void driveSpeed(double left, double right, int side);

void driveDist(float dist, int speed);

void driveTurn(int degrees, int side, int speed);

void driveArc(float radius, double exit_angle, int side, int max_speed);

void liftSet(int pos, int speed);

void flyWheel(int velocity);

void intake(int velocity);

void index(int velocity);

void robotStop();

#endif
