#include "Timer.h"

uint32_t cnt;
uint8_t onceTimerId;

void timer5000() {
  Serial.println("timer 5000");
  Timer.start(onceTimerId);
}

void timer10000(void *arg) {
  UartClass *com = (UartClass *)arg;
  com->println("timer 10000");
}

void setup() {
  Serial.begin(115200);

  Timer.addRepeat(5000, timer5000);

  Timer.addRepeat(10000, timer10000, (void *)&Serial);

  Timer.addRepeat(3000, []() {
    Serial.println("timer 3000");
  });

  Timer.addRepeat(
    1000, [](void *arg) {
      uint32_t *count = (uint32_t *)arg;
      Serial.printf("timer count = %d\n", *count);
    },
    (void *)&cnt);

  onceTimerId = Timer.addOnce(500, []() {
    Serial.println("Ones");
  });
  Timer.stop(onceTimerId);
}

void loop() {
  cnt++;
}
