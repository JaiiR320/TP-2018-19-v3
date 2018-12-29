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

void drivePPos(double Ltarget, double Rtarget){
	double kp = .34; // with only p, .25 is perfect

	double Lerror = Ltarget;
	double Rerror = Rtarget;

	double Lspeed = 0;
	double Rspeed = 0;

	int Ladd = 6;
	int Radd = 6;

	left_front.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_back.tare_position();

	while(abs((int)Lerror) > 2 && abs((int)Rerror) > 2){
		Lerror = Ltarget - left_back.get_position();
		Rerror = Rtarget - right_back.get_position();

		if(Ltarget < 1){
			Ladd = -6;
		}
		if(Rtarget < 1){
			Radd = -6;
		}

		Lspeed = (Lerror * kp) + Ladd;
		Rspeed = (Rerror * kp) + Radd;

		left_front.move(Lspeed);
		left_back.move(Lspeed);
		right_front.move(Rspeed);
		right_back.move(Rspeed);

		delay(20);
	}
	//Hold Position
	left_front.move_relative(0, 0);
	left_back.move_relative(0, 0);
	right_front.move_relative(0, 0);
	right_back.move_relative(0, 0);
}

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

void driveDist(float dist, int speed){ //IMPORTANT, Distance in Inches
	dist = ((dist / 12.566) * 360);    //Converts desired inches into degrees

	int side;
	if(dist > 0){side = 1;}
	else if(dist < 0){side = -1;}

	drivePPos(dist, dist);
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

	drivePPos(arc_left, arc_right);
}

void liftSet(char *pos){
	int speed = 125;
	double set;
	if(strcmp(pos, "hold") == 0){
		set = 1;
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
}
