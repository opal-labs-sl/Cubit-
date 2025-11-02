
#include <Wire.h>

#define ADS1115_ADDRESS 0x48
#define ADS1115_POINTER_CONVERT 0x00
#define ADS1115_POINTER_CONFIG  0x01

// Voltage divider ratios
// Actual Input Voltage = Measured Voltage * Divider_Ratio
#define DIVIDER_AIN0 1.0                   // Direct input
#define DIVIDER_AIN1 ((220.0 + 15.0) / 15.0) // 220k / 15k = ~15.67
#define DIVIDER_AIN2 ((120.0 + 15.0) / 15.0) // 120k / 15k = 9.0
#define DIVIDER_AIN3 ((120.0 + 15.0) / 15.0) // 120k / 15k = 9.0

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL
  Serial.println("ADS1115 Analog Reading....");
}

void loop() {
  for (int channel = 0; channel < 4; channel++) {
    int16_t raw = readADS1115Channel(channel);

    // Convert raw to voltage (for ±6.144V range)
    float measuredV = raw * 0.1875 / 1000.0; // 0.1875 mV/bit
    float actualV = measuredV * getDividerRatio(channel);

    Serial.print("AIN");
    Serial.print(channel);
    Serial.print(" | Raw: ");
    Serial.print(raw);
    Serial.print(" | Measured: ");
    Serial.print(measuredV, 4);
    Serial.print(" V | Actual Input: ");
    Serial.print(actualV, 4);
    Serial.println(" V");
  }

  Serial.println("-----------------------------------");
  delay(1000);
}

float getDividerRatio(uint8_t channel) {
  switch (channel) {
    case 0: return DIVIDER_AIN0;
    case 1: return DIVIDER_AIN1;
    case 2: return DIVIDER_AIN2;
    case 3: return DIVIDER_AIN3;
    default: return 1.0;
  }
}

int16_t readADS1115Channel(uint8_t channel) {
  uint16_t config = 0x8000;                     // Start single conversion
  config |= (0x4000 | (channel << 12));         // MUX AINx vs GND
  config |= 0x0000;                             // PGA ±6.144V
  config |= 0x0100;                             // Single-shot mode
  config |= 0x0080;                             // 128 SPS
  config |= 0x0003;                             // Disable comparator

  Wire.beginTransmission(ADS1115_ADDRESS);
  Wire.write(ADS1115_POINTER_CONFIG);
  Wire.write((config >> 8) & 0xFF);
  Wire.write(config & 0xFF);
  Wire.endTransmission();

  delay(9); // Wait conversion

  Wire.beginTransmission(ADS1115_ADDRESS);
  Wire.write(ADS1115_POINTER_CONVERT);
  Wire.endTransmission();

  Wire.requestFrom(ADS1115_ADDRESS, (uint8_t)2);
  while (Wire.available() < 2);
  int16_t val = (Wire.read() << 8) | Wire.read();

  return val;
}
