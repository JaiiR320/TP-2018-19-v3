#include "main.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

Motor left_front(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor left_back(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor right_front(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor right_back(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

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

void drivePDist(double distance){
	double kp = 1;
	double minSpeed = 5;
	double current;
	double outcome;

	double target = (distance / 12.566) * 360;

	while(outcome > 5){
		current = left_back.get_position();
		outcome = kp * (target - current);
		std::cout << "outcome: " << outcome << "\n";

		left_front.move(outcome + minSpeed);
		left_back.move(outcome + minSpeed);
		right_front.move(-(outcome + minSpeed));
		right_back.move(-(outcome + minSpeed));
	}
}

void driveDist(float dist, int speed){ //IMPORTANT, Distance in Inches
	dist = ((dist / 12.566) * 360);    //Converts desired inches into degrees

	left_front.move_relative(dist, speed);
	left_back.move_relative(dist, speed);
	right_front.move_relative(dist, speed);
	right_back.move_relative(dist, speed);

	delay(500);
	while (left_back.is_stopped() == 0 && right_back.is_stopped() == 0) {
		delay(10);
	}
	delay(100);
}

void driveTurn(int degrees, int side, int speed){ //Pos degrees turns right
	double arclength = 2 * 3.1415926 * 7 * (double(degrees) / 360);

	double dist = (arclength / 12.566) * 360;

  dist *= side;

	left_front.move_relative(dist, speed);
	left_back.move_relative(dist, speed);
	right_front.move_relative(-dist, speed);
	right_back.move_relative(-dist, speed);

	delay(500);
	while (left_back.is_stopped() == 0 && right_back.is_stopped() == 0) {
		delay(10);
	}
	delay(100);
}

void driveArc(float radius, double exit_angle, int side, int max_speed){
	exit_angle *= 3.1415926 / 180.0; //1.5 for 90 deg
	//48 r arc left = 64.40
  double arc_left = (radius + (side * 7.325)) * exit_angle;
  double arc_right = (radius + (side * -7.325)) * exit_angle;

	arc_left = (arc_left / 12.566) * 360;
	arc_right = (arc_right / 12.566) * 360;

  int vel_left = max_speed;
  int vel_right = max_speed;

  if (arc_left < arc_right) {
    vel_left = (double)max_speed * (arc_left / arc_right);
  }
  if (arc_right < arc_left) {
    vel_right = (double)max_speed * (arc_right / arc_left);
  }

  int rev = 1;

  if (arc_right < 0) {
    rev = -1;
  }
	arc_left *= rev;
	arc_right *= rev;

  left_front.move_relative(arc_left, vel_left);
	left_back.move_relative(arc_left, vel_left);
	right_front.move_relative(arc_right, vel_right);
	right_back.move_relative(arc_right, vel_right);

	delay(500);
	while (left_back.is_stopped() == 0 && right_back.is_stopped() == 0) {
		delay(10);
	}
	delay(100);
}

void liftSet(int pos, int speed){
	lift_mtr.move_relative(pos, speed);
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

void robotStop(){ //stops robot
  flyWheel(0);
  intake(0);
  index(0);
}
