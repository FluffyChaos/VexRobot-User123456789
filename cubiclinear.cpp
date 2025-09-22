int main() {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  double leftControl = 0, rightControl = 0, leftPower = 0, rightPower = 0;

  Brain.Screen.print("Tank Control Program Started");

  Controller1.Screen.clearScreen();

  while (true) {

    // Saving the joystick values from the
    leftControl = Controller1.Axis3.position();
    rightControl = Controller1.Axis2.position();

    leftPower = (pow(leftControl, 3) / pow(100, 2) + leftControl) / 2;   // y = (x^3 / 100^2 + x) / 2
    rightPower = (pow(rightControl, 3) / pow(100, 2) + rightControl) / 2;

    LeftMotor.spin(forward, leftPower, pct);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Left = %3.0f Pwr = %3.0f", leftControl, leftPower);

    RightMotor.spin(forward, rightPower, pct);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Right = %3.0f Pwr = %3.0f", rightControl, rightPower);

    task::sleep(20);
  }
}
