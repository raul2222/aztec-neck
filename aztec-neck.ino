
#include <ESP32Servo.h>

// create four servo objects 
Servo servo1;
Servo servo2;

// Published values for SG90 servos; adjust if needed
int minUs = 500;
int maxUs = 2500;

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42
// for the ESP32-S3 the GPIO pins are 1-21,35-45,47-48
// for the ESP32-C3 the GPIO pins are 1-10,18-21

int servo1Pin = 14;
int servo2Pin = 12;

int mytime = 39;

int pos = 0;      // position in degrees
ESP32PWM pwm;
void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	Serial.begin(115200);
	servo1.setPeriodHertz(250);      // Standard 50hz servo
	servo2.setPeriodHertz(250);      // Standard 50hz servo
  servo1.attach(servo1Pin, minUs, maxUs);
	servo2.attach(servo2Pin, minUs, maxUs);
  normal_pose();
}

void normal_pose(){
  servo1.write(100);
  delay(1000);   
  servo2.write(72);
  delay(1000); 
}

void loop() {
  /*

	for (pos = 65; pos >= 77; pos -= 1) { // sweep from 180 degrees to 0 degrees
		servo2.write(pos);
		delay(mytime);
	}

  servo2.write(77);
	for (pos = 50; pos <= 140; pos += 1) { // sweep from 0 degrees to 180 degrees
		// in steps of 1 degree
		servo1.write(pos);
		delay(mytime);             // waits mytimems for the servo to reach the position
	}
	for (pos = 140; pos >= 50; pos -= 1) { // sweep from 180 degrees to 0 degrees
		servo1.write(pos);
		delay(mytime);
	}



	for (pos = 50; pos <= 140; pos += 1) { // sweep from 0 degrees to 180 degrees
		// in steps of 1 degree
		servo1.write(pos);
		delay(mytime);             // waits mytimems for the servo to reach the position
	}
	for (pos = 65; pos <= 95; pos += 1) { // sweep from 0 degrees to 180 degrees
		// in steps of 1 degree
		servo2.write(pos);
		delay(mytime);             // waits mytimems for the servo to reach the position
	}

	for (pos = 140; pos >= 50; pos -= 1) { // sweep from 180 degrees to 0 degrees
		servo1.write(pos);
		delay(mytime);
	}


	for (pos = 95; pos >= 65; pos -= 1) { // sweep from 180 degrees to 0 degrees
		servo2.write(pos);
		delay(mytime);
	}
	for (pos = 50; pos <= 140; pos += 1) { // sweep from 0 degrees to 180 degrees
		// in steps of 1 degree
		servo1.write(pos);
		delay(mytime);             // waits mytimems for the servo to reach the position
	}
	for (pos = 140; pos >= 50; pos -= 1) { // sweep from 180 degrees to 0 degrees
		servo1.write(pos);
		delay(mytime);
	}
  
*/


	//delay(1000);

}

