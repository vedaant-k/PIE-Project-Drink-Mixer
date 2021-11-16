/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define SOLENOID_PIN 13


// Declare function to pour water.
void pour_water(int amount);

void setup() {
  // Initialize serial.
  Serial.begin(9600);
  
  // Declare pins as output:
  pinMode(SOLENOID_PIN, OUTPUT);
}

void loop() {

// Check if serial channel is available.
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
  
  // Open the valve for water.
  digitalWrite(SOLENOID_PIN, HIGH);
  Serial.println("Water is pouring...");
  // Pause for specified amount of time.
  delay(time_interval);

  // Close the valve.
  digitalWrite(SOLENOID_PIN, LOW);
  Serial.println("Your water has been poured!");
}
