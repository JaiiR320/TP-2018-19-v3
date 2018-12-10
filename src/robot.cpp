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

void driveDist(float dist, int speed){ //IMPORTANT, Distance in Inches
	dist = ((dist / 12.566) * 360);    //Converts desired inches into degrees

    int current = left_front.get_position();
    int target = current + dist;

	left_front.move_relative(dist, speed);
	left_back.move_relative(dist, speed);
	right_front.move_relative(dist, speed);
	right_back.move_relative(dist, speed);

    while (left_front.is_stopped() == 0) {
        delay(10);
    }
    delay(10);
}

void driveTurn(int degrees, int side, int speed){ //Pos degrees turns right
	double arclength = 2 * 3.1415926 * 7 * (double(degrees) / 360);

	double dist = (arclength / 12.566) * 360;

    dist *= side;

	left_front.move_relative(dist, speed);
	left_back.move_relative(dist, speed);
	right_front.move_relative(-dist, speed);
	right_back.move_relative(-dist, speed);

    while (left_front.is_stopped() == 0) {
        delay(10);
    }
    delay(10);
}

void driveArc(float true_distance, int side, int exit_angle, int max_speed){
    exit_angle *= 3.1415926 / 180.0
    double rad = true_distance / (double)exit_angle

    double arc_left = rad + (side * -7) * exit_angle;
    double arc_right = rad + (side * 7) * exit_angle;

    int vel_left = max_speed;
    int vel_right = max_speed;

    if (arc_left < arc_right) {
        vel_right = (double)max_speed * (arc_left / arc_right);
    }
    if (arc_right < arc_left) {
        vel_left = (double)max_speed * (arc_right / arc_left);
    }

    int rev = 1;

    if (true_distance < 0) {
        rev = -1;
    }

    left_front.move_relative(left_arc * rev, vel_left);
	left_back.move_relative(left_arc * rev, vel_left);
	right_front.move_relative(right_arc * rev, vel_right);
	right_back.move_relative(right_arc * rev, vel_right);
}

void liftSet(int pos, int speed){
	lift_mtr.move_relative(pos, speed);

    while (lift_mtr.is_stopped() == 0) {
        delay(10);
    }
    delay(10);
}

void flyWheel(int velocity){
	flywheel_mtr.move(velocity);
}

void intake(int velocity){
    intake_mtr.set_velocity(velocity);
}

void index(int velocity){
    index_mtr.set_velocity(velocity);
}

void robotStop(){
    driveSpeed(0, 0, 1);
    flyWheel(0);
    intake(0);
    index(0);
}