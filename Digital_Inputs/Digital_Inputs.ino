//Pin Definition
//The maximum voltage on any isolated digital pin is 36V.
#define IN1 32
#define IN2 33
#define IN3 34
#define IN4 35

void setup() {
  Serial.begin(115200);
  
  // Configure pins as inputs
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
  pinMode(IN3, INPUT);
  pinMode(IN4, INPUT);

  Serial.println("Reading inputs from D32, D33, D34, D35...");
}

void loop() {
  // Read input states
  int val1 = digitalRead(IN1);
  int val2 = digitalRead(IN2);
  int val3 = digitalRead(IN3);
  int val4 = digitalRead(IN4);

  // Print values
  Serial.print("D32: "); Serial.print(val1);
  Serial.print("  D33: "); Serial.print(val2);
  Serial.print("  D34: "); Serial.print(val3);
  Serial.print("  D35: "); Serial.println(val4);

  delay(200); // adjust refresh rate as needed
}
