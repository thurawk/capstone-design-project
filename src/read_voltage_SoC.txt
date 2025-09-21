// 4 batteries, 4 voltage sensors, just connecting with arduino without mosfets, inductors and resistors.
// Result: Cell1: 3.69 V | SoC1: 57.5% | Cell2: 7.48 V | SoC2: 100.0% | Cell3: 11.27 V | SoC3: 100.0% | Cell4: 15.10 V | SoC4: 100.0%
// 4S Li-ion battery monitoring with Arduino Mega
// NO MOSFET balancing, NO current sensor
// Just reading voltages and printing SoC

// Analog input pins for voltages
const int soc1Pin = A0;
const int soc2Pin = A1;
const int soc3Pin = A2;
const int soc4Pin = A3;

// Battery parameters
const float Vmax = 4.2;
const float Vmin = 3.0;

// Divider scaling factor (adjust to your resistors!)
// Example: if you use 100k / 10k divider, factor = 11
const float scaleFactor = 5.0;

void setup() {
Serial.begin(9600);
while (!Serial);

Serial.println("4S Li-ion Battery Monitor");
Serial.print("Scale factor = ");
Serial.println(scaleFactor);
}

float readVoltage(int pin) {
int raw = analogRead(pin);
float v = (raw * 5.0 / 1023.0) * scaleFactor; // convert to real voltage
return v;
}

void loop() {
// Read voltages
float v1 = readVoltage(soc1Pin);
float v2 = readVoltage(soc2Pin);
float v3 = readVoltage(soc3Pin);
float v4 = readVoltage(soc4Pin);

// Individual cell voltages (difference of taps)
float cell1 = v1;
float cell2 = v2;
float cell3 = v3;
float cell4 = v4;
}
