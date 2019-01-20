#include "main.h"

void opcontrol() {
  int left, right;
  int side = 1;
  lift_mtr.tare_position();
  //duo
  while (duo == true) {
    //hold drive
    while(partner.get_digital(DIGITAL_R2) == 1){
      left_front.move_relative(0, 0);
      left_back.move_relative(0, 0);
      right_front.move_relative(0, 0);
      right_back.move_relative(0, 0);
    }

    //drive
    left = partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    right = partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

    //speed control
    left *= (double)(abs(left) / 100);
    right *= (double)(abs(right) / 100);

    driveSpeed(left, right, side);

    //flywheel
    if (master.get_digital(DIGITAL_Y) == 1) {
      flyWheel(200);
    } else if (master.get_digital(DIGITAL_B) == 1) {
      flyWheel(0);
    }

    //intake
		if (master.get_digital(DIGITAL_L1) == true) {
			intake_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_L2) == true) {
			intake_mtr.move_velocity(-200);
		} else {
		  intake_mtr.move_velocity(0);
		}

	  //index
	  if (master.get_digital(DIGITAL_X) == true) {
			index_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_A) == true) {
			 index_mtr.move_velocity(-200);
		} else {
			index_mtr.move_velocity(0);
		}

    //lift
    if (master.get_digital(DIGITAL_R1) == 1) {
      lift_mtr.move_absolute(2.5, 125);
    } else if (master.get_digital(DIGITAL_R2) == 1) {
      lift_mtr.move_absolute(.8, 100);
    } else {
      lift_mtr.move_absolute(0, 200);
    }

    delay(20);
  }

  //solo
  while (duo == false) {
    //drive - arcade
    left = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    right = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
    /*
    left *= (double)(abs(left) / 100);
    right *= (double)(abs(right) / 100);
    */
    driveSpeed(left, right, side);

    //flywheel
    if (master.get_digital(DIGITAL_Y) == 1) {
      flyWheel(200);
    } else if (master.get_digital(DIGITAL_B) == 1) {
      flyWheel(0);
    }

    //intake
		if (master.get_digital(DIGITAL_L1) == true) {
			intake_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_L2) == true) {
			intake_mtr.move_velocity(-200);
	  } else {
			intake_mtr.move_velocity(0);
		}

	  //index
	  if (master.get_digital(DIGITAL_X) == true) {
			index_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_A) == true) {
			index_mtr.move_velocity(-200);
		} else {
			index_mtr.move_velocity(0);
		}

    //lift
    if (master.get_digital(DIGITAL_R1) == 1) {
      lift_mtr.move_absolute(2.5, 125);
    } else if (master.get_digital(DIGITAL_R2) == 1) {
      lift_mtr.move_absolute(.8, 100);
    } else {
      lift_mtr.move_absolute(0, 100);
    }

    std::cout << "left_back:   " << left_back.get_actual_velocity() << '\n';
    std::cout << "left_front:  " << left_front.get_actual_velocity() << '\n';
    std::cout << "right_back:  " << right_back.get_actual_velocity() << '\n';
    std::cout << "right_front: " << right_front.get_actual_velocity() << '\n';

    delay(20);
  }
}
