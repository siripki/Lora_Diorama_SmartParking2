void servoSetup(){
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servoKiri.setPeriodHertz(50);    // standard 50 hz servo
	servoKiri.attach(15, 1000, 2000); // attaches the servo on pin 18 to the servo object
  servoKanan.setPeriodHertz(50);    // standard 50 hz servo
	servoKanan.attach(14, 1000, 2000); // attaches the servo on pin 18 to the servo object
}

void servoKiriOn(){
  servoKiri.write(180);
  delay(1000);
  servoKiri.write(0);
}
void servoKananOn(){
  servoKanan.write(0);
  delay(1000);
  servoKanan.write(180);
}