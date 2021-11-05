/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

int command = 1;

// Declare function to pour water.
void pour_water(int amount);

void setup() {
  // Initialize serial.
  Serial.begin(9600);
  
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
//  // Arbitrary stepper motor motion - to be changed when mechanics are known.
//  // Set the spinning direction clockwise:
//  digitalWrite(dirPin, HIGH);
//
//  // Spin the stepper motor 1/4 revolution clockwise quickly to open the nozzle:
//  for (int i = 0; i < stepsPerRevolution / 4; i++) {
//    // These four lines result in 1 step:
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(500);
//  }
//
//  // Pause for specified amount of time.
//  delay(1000);
//
//  // Set the spinning direction counterclockwise:
//  digitalWrite(dirPin, LOW);
//
//  // Spin the stepper motor 1/4 revolution counterclockwise quickly to close the nozzle:
//  for (int i = 0; i < stepsPerRevolution / 4; i++) {
//    // These four lines result in 1 step:
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(500);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(500);
//  }
//  // Pause for specified amount of time.
//  delay(1000);
//  // Check if serial channel is available.
  if (Serial.available() > 0) {
    // read the incoming byte:
    command = Serial.parseInt();
  }
  if (command == 2){
      pour_water(100);
  }
}

// Function to pour water of a specified amount (scale 0 to 100 with 100 being a full cup).
void pour_water(int amount){
  int time_interval = amount*50; // Add function to convert the amount of liquid into the time to pour in milliseconds (using pressure etc.)
  
  // Arbitrary stepper motor motion - to be changed when mechanics are known.
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 1/4 revolution clockwise quickly to open the nozzle:
  for (int i = 0; i < stepsPerRevolution / 4; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  // Pause for specified amount of time.
  delay(time_interval);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1/4 revolution counterclockwise quickly to close the nozzle:
  for (int i = 0; i < stepsPerRevolution / 4; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  Serial.println("Your water has been poured!");
}
