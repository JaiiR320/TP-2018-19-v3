#include "main.h"

void opcontrol() {
    int left, right;
    int side;
    //duo
    while (duo == true) {
        //side selection
        if (partner.get_digital(DIGITAL_UP) == 1) {
            side = 1;
        } else if (partner.get_digital(DIGITAL_DOWN) == 1) {
            side = -1;
        }

        //drive
        left = partner.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        right = partner.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

        driveSpeed(left, right, side);

        //flywheel
        if (master.get_digital(DIGITAL_Y) == 1) {
            flyWheel(200);
        } else if (master.get_digital(DIGITAL_B) == 1) {
            flyWheel(0);
        }
        master.print(0, 0, "Flywheel Vel: %d", flywheel_mtr.get_actual_velocity());

        //intake
		if (master.get_digital(DIGITAL_L1) == true) {
			intake_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_L2) == true) {
			intake_mtr.move_velocity(-200);
		} else {
			intake_mtr.move_velocity(0);
		}

	    //index
	    if (master.get_digital(DIGITAL_R1) == true) {
			index_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_R2) == true) {
			index_mtr.move_velocity(-200);
		} else {
			index_mtr.move_velocity(0);
		}

        delay(20);
    }

    //solo
    while (duo == false) {
        //side selection
        if (master.get_digital(DIGITAL_UP) == 1) {
            side = 1;
        } else if (master.get_digital(DIGITAL_DOWN) == 1) {
            side = -1;
        }

        //drive
        left = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        right = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

        driveSpeed(left, right, side);

        //flywheel
        if (master.get_digital(DIGITAL_Y) == 1) {
            flyWheel(200);
        } else if (master.get_digital(DIGITAL_B) == 1) {
            flyWheel(0);
        }
        master.print(0, 0, "Flywheel Vel: %d", flywheel_mtr.get_actual_velocity());

        //intake
		if (master.get_digital(DIGITAL_L1) == true) {
			intake_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_L2) == true) {
			intake_mtr.move_velocity(-200);
		} else {
			intake_mtr.move_velocity(0);
		}

	    //index
	    if (master.get_digital(DIGITAL_R1) == true) {
			index_mtr.move_velocity(200);
		} else if (master.get_digital(DIGITAL_R2) == true) {
			index_mtr.move_velocity(-200);
		} else {
			index_mtr.move_velocity(0);
		}

        delay(20);
    }
}
