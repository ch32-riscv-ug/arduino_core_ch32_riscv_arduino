#if defined(CH32V003)
#define OUTPUT_PIN PC1
#define INPUT_PIN PC2
#else
#define OUTPUT_PIN PA1
#define INPUT_PIN PA2
#endif

void setup() {
  printf("setup\n");
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {
  static PinStatus output = LOW;
  output = (output == LOW) ? HIGH : LOW;
  printf("loop\n");
  digitalWrite(OUTPUT_PIN, output);
  printf(" output = %d\n", output);
  printf(" input = %d\n", digitalRead(INPUT_PIN));
  delay(1000);
}
