// Define output pins
#define OUT1 23
#define OUT2 25
#define OUT3 26
#define OUT4 27

void setup() {
  Serial.begin(115200);
  
  // Set pins as outputs
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);

  Serial.println("Sequential output control ...");
}

void loop() {
  // Turn each pin ON one by one, then OFF before moving to next
  digitalWrite(OUT1, HIGH);
  Serial.println("GPIO 23 ON");
  delay(500);
  digitalWrite(OUT1, LOW);
  Serial.println("GPIO 23 OFF");
  delay(200);

  digitalWrite(OUT2, HIGH);
  Serial.println("GPIO 25 ON");
  delay(500);
  digitalWrite(OUT2, LOW);
  Serial.println("GPIO 25 OFF");
  delay(200);

  digitalWrite(OUT3, HIGH);
  Serial.println("GPIO 26 ON");
  delay(500);
  digitalWrite(OUT3, LOW);
  Serial.println("GPIO 26 OFF");
  delay(200);

  digitalWrite(OUT4, HIGH);
  Serial.println("GPIO 27 ON");
  delay(500);
  digitalWrite(OUT4, LOW);
  Serial.println("GPIO 27 OFF");
  delay(200);
}
