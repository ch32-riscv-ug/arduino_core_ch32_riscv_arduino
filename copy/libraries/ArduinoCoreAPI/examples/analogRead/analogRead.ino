#if defined(CH32V003)
#define ANALOG_IN PD2
#else
#define ANALOG_IN PA2
#endif

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");
}

void loop() {
  Serial.println("loop");
  uint16_t ain = analogRead(ANALOG_IN);

#if defined(CH32V003)
  Serial.printf(" analogRead() : %d(%dmv)\n", ain, 3300 * ain / 1024);
#else
  Serial.printf(" analogRead() : %d(%dmv)\n", ain, 3300 * ain / 4096);
#endif
  delay(500);
}
