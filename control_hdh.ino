#include <Servo.h>

Servo steer_motor;
Servo throt_motor;

// const int steer_in = 5;
// const int throt_in = 6;
const int steer_out = 11;
const int throt_out = 10;

int steer_in_value = 0;
int throt_in_value  = 0;
int steer_out_value = 1450;
int throt_out_value  = 1500;
// defines variables

/*
const int trigPin = 8;
const int echoPin = 9;
// defines variables

long duration;
int distance;
*/

void setup() {
  // pinMode(steer_in, INPUT); // Sets the trigPin as an Output
  // pinMode(throt_in, INPUT); // Sets the echoPin as an Input

  steer_motor.attach(steer_out);
  throt_motor.attach(throt_out);

  Serial.begin(9600); // Starts the serial communication
}

void loop() {

  // steer_in_value = pulseIn(steer_in, HIGH);
  // throt_in_value = pulseIn(throt_in, HIGH);
  if(Serial.available() > 0) {
    steer_in_value = Serial.parseInt();
    throt_in_value = Serial.parseInt();
    Serial.read();
    /* original data
     * throt: ~1450, 1500~ (center: 1500)
     * steer: 1100~1900 (center:1450)
     * 
     * parsing data
     * throt: 1500, 1525~1540 -> 0~7
     * steer: 1100~1900 -> -7~7
     */
  
    // TODO: Add reverse steering
    if(throt_in_value == 0) {
      throt_out_value = 1500;
    } else {
      throt_out_value = 1525 + (throt_in_value - 1) * 2;
    }
 
    steer_out_value = steer_in_value * 50 + 1450;
  }
  // steer_out_value = steer_in_value;
  // throt_out_value = 1500 - (1500 - throt_in_value) / 2;

  steer_out_value = steer_in_value;
  throt_out_value = throt_in_value;

  throt_motor.writeMicroseconds(throt_out_value);
  steer_motor.writeMicroseconds(steer_out_value);

  // Serial.println(steer_out_value);
  Serial.print(steer_out_value);
  Serial.println(throt_out_value);

}

