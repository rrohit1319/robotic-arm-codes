#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

// Define the movement steps
int stepSize = 5; // Degrees to move per step
int delayTime = 15; // Delay between steps in milliseconds

// Define servo positions for different commands
int forwardPosition = 90;  
int backwardPosition = 0;  
int rotateClockwiseStart = 45;
int rotateClockwiseEnd = 135;
int rotateCounterClockwiseStart = 135;
int rotateCounterClockwiseEnd = 45;

void setup() {
  Serial.begin(9600); // Initialize Bluetooth serial communication
  servo1.attach(9);  // Pin connected to the first servo
  servo2.attach(10); // Pin connected to the second servo
  servo3.attach(11); // Pin connected to the third servo
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read the command sent from the phone

    switch (command) {
      case 'F': // Forward movement
        moveServos(forwardPosition);
        break;
      case 'B': // Backward movement
        moveServos(backwardPosition);
        break;
      case 'R': // Clockwise rotation
        rotateServos(rotateClockwiseStart, rotateClockwiseEnd);
        break;
      case 'L': // Counterclockwise rotation
        rotateServos(rotateCounterClockwiseStart, rotateCounterClockwiseEnd);
        break;
      default:
        // Handle other commands or ignore
        break;
    }
  }
}

// Function to move all servos to a specific position
void moveServos(int position) {
  servo1.write(position);
  servo2.write(position);
  servo3.write(position);
  delay(1000); // Delay to allow servos to reach the position
}

// Function to rotate servos from start to end position
void rotateServos(int startPosition, int endPosition) {
  for (int pos = startPosition; pos <= endPosition; pos += stepSize) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    delay(delayTime); // Delay between steps
  }
  for (int pos = endPosition; pos >= startPosition; pos -= stepSize) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(pos);
    delay(delayTime); // Delay between steps
  }
}
