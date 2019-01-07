#include "main.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

Motor left_front(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor left_back(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor right_front(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor right_back(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor flywheel_mtr(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_ROTATIONS);

Motor intake_mtr(7, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_ROTATIONS);

Motor index_mtr(9, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor lift_mtr(10, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_ROTATIONS);

void driveSpeed(double left, double right, int side){
	if(side == 1){
		left_front.move(left);
		left_back.move(left);
		right_front.move(right);
		right_back.move(right);
	}
	else if(side == -1){
		left_front.move(right * -1);
		left_back.move(right * -1);
		right_front.move(left * -1);
		right_back.move(left * -1);
	}
}

void driveDist(double dist, int speed){ //IMPORTANT, Distance in Inches
	dist = ((dist / 12.566) * 360);    //Converts desired inches into degrees

	drivePIDPos(dist, dist, speed);
}

void driveTurn(int degrees, int side, int speed){ //Pos degrees turns right
	double arclength = 2 * 3.1415926 * 7.25 * (double(degrees) / 360);

	double dist = (arclength / 12.566) * 360;

  dist *= side;

	left_back.move_relative(dist, speed);
	left_front.move_relative(dist, speed);
	right_back.move_relative(-dist, speed);
	right_front.move_relative(-dist, speed);
}

void driveArc(double radius, double exit_angle, int side, int max_speed){
	exit_angle *= 3.1415926 / 180.0; //1.5 for 90 deg
	//48 r arc left = 64.40
  double arc_left = (radius + (side * 7.325)) * exit_angle;
  double arc_right = (radius + (side * -7.325)) * exit_angle;

	arc_left = (arc_left / 12.566) * 360;
	arc_right = (arc_right / 12.566) * 360;

  int rev = 1;

  if (arc_right < 0) {
    rev = -1;
  }
	arc_left *= rev;
	arc_right *= rev;

	drivePPos(arc_left, arc_right, max_speed);
}

void liftSet(char *pos){
	int speed = 125;
	double set;
	if(strcmp(pos, "hold") == 0){
		set = .8;
	} else if (strcmp(pos, "up") == 0){
		set = 2.5;
	} else if (strcmp(pos, "down") == 0){
		set = 0;
	}

	lift_mtr.move_absolute(set, speed);
}

void flyWheel(int velocity){
	flywheel_mtr.move(velocity);
}

void intake(int velocity){
  intake_mtr.move_velocity(velocity);
}

void index(int velocity){
  index_mtr.move_velocity(velocity);
}

void robotStop(){
	driveSpeed(0, 0, 1);
  flyWheel(0);
  intake(0);
  index(0);
	while(1){delay(10);}
}
