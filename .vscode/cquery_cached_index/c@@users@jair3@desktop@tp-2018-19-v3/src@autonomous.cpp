#include "main.h"

void autonomous() {
  switch (Aauton) {
    case 1: mainAuton(Acolor);
    case 2: secondAuton(Acolor);
    case 3: skills(Acolor);
  }
}
