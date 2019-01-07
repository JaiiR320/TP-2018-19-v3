#include "main.h"

void drivePIDPos(double Ltarget, double Rtarget, double max_speed){
	double kp = .34; // with only p, .25 is perfect
	double ki = .10;
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

	int stop_count = 0;

	bool pidRunning = true;

	left_front.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_back.tare_position();

	while(1){
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
		if ((Rerror < 8 && Rerror > -8) && (Lerror < 8 && Lerror > -8)) {
			stop_count++;
		}
		if(stop_count == 10){pidRunning = false;}

		std::cout << "P: " << (Lerror * kp) << '\n';
		std::cout << "I: " << (Lintegral * ki) << '\n';
		std::cout << "D: " << (Lderivative * kd) << '\n';
		std::cout << "Output: " << Lspeed << '\n';
		std::cout << "Error: " << Lerror << '\n';

		//50 Hz
		delay(25);
	}
}

void drivePPos(double Ltarget, double Rtarget, double max_speed){
	double kp = .32; // with only p, .25 is perfect

	double Lerror = Ltarget;
	double Rerror = Rtarget;

	double Lspeed = 0;
	double Rspeed = 0;
	double min_speed = max_speed * -1;

	bool pidRunning = true;

	left_front.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_back.tare_position();

	while(1){
		Lerror = Ltarget - left_back.get_position();
		Rerror = Rtarget - right_back.get_position();

		Lspeed = (Lerror * kp);
		Rspeed = (Rerror * kp);

		if(Lspeed > 0){
			Lspeed += 5;
		} else if(Lspeed < 0){
			Lspeed += -5;
		}
		if(Rspeed > 0){
			Rspeed += 5;
		} else if(Rspeed < 0){
			Rspeed += -5;
		}

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

		//if ((Rerror < 8 && Rerror > -8) && (Lerror < 8 && Lerror > -8)) {pidRunning = false;}

		std::cout << "P: " << (Lerror * kp) << '\n';
		std::cout << "Output: " << Lspeed << '\n';
		std::cout << "Target: " << Ltarget << '\n';
		std::cout << "Error: " << Lerror << '\n';
		std::cout << "" << '\n';

		//50 hz
		delay(25);
	}
}
