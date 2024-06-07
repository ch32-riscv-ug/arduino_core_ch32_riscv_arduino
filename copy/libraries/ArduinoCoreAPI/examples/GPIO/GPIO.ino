#if defined(CH32V003)
#define OUTPUT_PIN PC1
#define INPUT_PIN PC2
#else
#define OUTPUT_PIN PA0
#define INPUT_PIN PA1
#endif

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  pinMode(OUTPUT_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop()
{
  char buff[80];

  static PinStatus output = LOW;
  output = (output == LOW) ? HIGH : LOW;
  Serial.println("loop");
  digitalWrite(OUTPUT_PIN, output);

  snprintf(buff, sizeof(buff), " output = %d", output);
  Serial.println(buff);

  snprintf(buff, sizeof(buff), " input = %d", digitalRead(INPUT_PIN));
  Serial.println(buff);

  snprintf(buff, sizeof(buff), " millis = %d, micros = %d", (unsigned int)millis(), (unsigned int)micros());
  Serial.println(buff);

  delay(1000);
}
