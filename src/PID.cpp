#include "main.h"

void drivePIDPos(double Ltarget, double Rtarget, double max_speed){
	double kp = .28; // with only p, .25 is perfect
	double ki = .15;
	double kd = .20;

	//error variables
	double Lerror = Ltarget;
	double Rerror = Rtarget;

	//Integral and Derivative terms
	double Lintegral, Rintegral = 0;
	double Lderivative, Rderivative;

	double prevLError, prevRError = 0;

	//Init speed terms
	double Lspeed = 0;
	double Rspeed = 0;

	double min_speed = max_speed * -1;

	//window for integral term to take effect
	double ki_limit = 10;

	double THRESH = 3;

	bool pidRunning = true;

	left_front.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_back.tare_position();

	while(pidRunning){
		/*~~~~~~~~~~~~~
		CALCULATE ERROR
		~~~~~~~~~~~~~*/
		Lerror = Ltarget - left_back.get_position();
		Rerror = Rtarget - right_back.get_position();

		/*~~~~~~~~~~~~~~~~~~
		CACLULATING INTEGRAL
		~~~~~~~~~~~~~~~~~~*/
		if (abs((int)Lerror) < ki_limit) {
			Lintegral = (Lintegral + Lerror);
		}
		if (abs((int)Rerror) < ki_limit) {
			Rintegral = (Rintegral + Rerror);
		}

		/*~~~~~~~~~~~~~~~~~~~~
		CACLULATING DERIVATIVE
		~~~~~~~~~~~~~~~~~~~~*/
		Lderivative = Lerror - prevLError;
		Rderivative = Rerror - prevRError;

		prevLError = Lerror;
		prevRError = Rerror;

		/*~~~~~~~~~~~~~~~
		CACLULATE OUTPUTS
		~~~~~~~~~~~~~~~*/
		Lspeed = (Lerror * kp) + (Lintegral * ki) + (Lderivative * kd);
		Rspeed = (Rerror * kp) + (Rintegral * ki) + (Rderivative * kd);

		/*~~~~~~~~~~~~~~
		lIMITING OUTPUTS
		~~~~~~~~~~~~~~*/
		if (Lspeed > max_speed) {
			Lspeed = max_speed;
		} else if (Lspeed < min_speed) {
			Lspeed = min_speed;
		}

		if (Rspeed > max_speed) {
			Rspeed = max_speed;
		} else if (Rspeed < min_speed) {
			Rspeed = min_speed;
		}

		/*~~~~~~~~~~~~~
		SETTING OUTPUTS
		~~~~~~~~~~~~~*/
		left_front.move(Lspeed);
		left_back.move(Lspeed);
		right_front.move(Rspeed);
		right_back.move(Rspeed);

		/*~~~~~~~~~
		CHECK ERROR
		~~~~~~~~~*/
		if (Lderivative == 0) {
			pidRunning = false;
		}

		std::cout << "Running" << '\n';

		//50 Hz
		delay(25);
	}
	left_front.move_relative(0, 0);
	left_back.move_relative(0, 0);
	right_front.move_relative(0, 0);
	right_back.move_relative(0, 0);
}
