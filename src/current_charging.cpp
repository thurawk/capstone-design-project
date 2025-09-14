#include <Wire.h>
#include <Adafruit_INA219.h>

// INA219 object
Adafruit_INA219 ina219;

// PWM pins for balancing (6 MOSFETs)
const int s1Pin = 3;
const int s2Pin = 5;
const int s3Pin = 6;
const int s4Pin = 9;
const int s5Pin = 10;
const int s6Pin = 11;

// Digital pin for charging MOSFET (7th)
const int chargeMosfetPin = 7;

// Balancing PWM duty cycle
const int PWM = 200;

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);
  while (!Serial); // Wait for serial

  // Initialize INA219 sensor
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }

  // Set MOSFET pins as outputs
  pinMode(s1Pin, OUTPUT);
  pinMode(s2Pin, OUTPUT);
  pinMode(s3Pin, OUTPUT);
  pinMode(s4Pin, OUTPUT);
  pinMode(s5Pin, OUTPUT);
  pinMode(s6Pin, OUTPUT);
  pinMode(chargeMosfetPin, OUTPUT);
}

void loop() {
  // Read current from INA219 (mA)
  float current_mA = ina219.getCurrent_mA();

  // Determine if battery is charging
  // Positive current means current is flowing INTO the battery
  bool isCharging = current_mA > 50; // Threshold: 50 mA

  // Control charging MOSFET
  digitalWrite(chargeMosfetPin, isCharging ? HIGH : LOW);

  // Balancing control logic
  int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;

  if (isCharging) {
    // Simple example: balance in pairs
    s1 = PWM;
    s3 = PWM;
    s5 = PWM;
  }

  // Apply PWM to balancing MOSFETs
  analogWrite(s1Pin, s1);
  analogWrite(s2Pin, s2);
  analogWrite(s3Pin, s3);
  analogWrite(s4Pin, s4);
  analogWrite(s5Pin, s5);
  analogWrite(s6Pin, s6);

  // Debug output
  Serial.print("Charging Current: ");
  Serial.print(current_mA);
  Serial.println(" mA");

  delay(500);
}