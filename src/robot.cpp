#include "main.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

Motor left_front(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor left_back(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor right_front(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor right_back(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor flywheel(8, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_ROTATIONS);

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

    while (current < target) {
        current = left_front.get_position();
        delay(10);
    }
}

void driveTurn(double degrees, char* side, int speed){ //Pos degrees turns right
	double arclength = 2 * 3.1415926 * 7 * (degrees / 360);

	double dist = (arclength / 12.566) * 360;

    if (strcmp(side, "left") == 0) {
        dist *= -1;
    } else if (strcmp(side, "right") == 0) {
        dist *= 1;
    } else {
        dist = 0;
    }

    int current = left_front.get_position();
    int target = current + dist;

	left_front.move_relative(dist, speed);
	left_back.move_relative(dist, speed);
	right_front.move_relative(-dist, speed);
	right_back.move_relative(-dist, speed);

    while (current < target) {
        current = left_front.get_position();
        delay(10);
    }
}

void liftSet(int pos, int speed){
    int current = lift_mtr.get_position();
    int target = current + pos;

	lift_mtr.move_relative(pos, speed);

    while (current < target) {
        current = lift_mtr.get_position();
        delay(10);
    }
}

void flyWheelSet(int velocity){
	flywheel.move(velocity);
}
