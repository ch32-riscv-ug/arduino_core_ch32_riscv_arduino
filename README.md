# arduino_core_ch32_riscv_arduino
CH32 Risc-V for Arduino IDE

```
https://raw.githubusercontent.com/ch32-riscv-ug/arduino_core_ch32_riscv_arduino/main/package_ch32-riscv-arduino.json
```
## Supported Features

- [ ] Common
  - [ ] GPIO
    - [x] void pinMode(pin_size_t pinNumber, PinMode pinMode)
    - [x] PinStatus digitalRead(pin_size_t pinNumber)
    - [x] void digitalWrite(pin_size_t pinNumber, PinStatus status)
    - [ ] void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode)
    - [ ] void attachInterruptParam(pin_size_t interruptNumber, voidFuncPtrParam callback, PinStatus mode, void *param)
    - [ ] void detachInterrupt(pin_size_t interruptNumber)
    - [ ] uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder)
    - [ ] void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t val)
    - [ ] unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout)
    - [ ] unsigned long pulseInLong(pin_size_t pin, uint8_t state, unsigned long timeout)
  - [x] ADC
    - [x] void analogReference(uint8_t mode)
    - [x] int analogRead(pin_size_t pinNumber)
  - [ ] DAC
    - [ ] void analogWrite(pin_size_t pinNumber, int value)
  - [x] SysTick
    - [x] unsigned long micros(void)
    - [x] unsigned long millis(void)
    - [x] void delay(unsigned long ms)
    - [x] void delayMicroseconds(unsigned int us)

- [x] USART/UART(Serial, UartClass)
- [ ] I2C(Wire)
- [ ] I2S
- [ ] SPI
- [ ] Timer
- [ ] WDT
- [ ] RTC
- [ ] USB Client
- [ ] USB Host
- [ ] USB PD
- [ ] Ethernet
 
