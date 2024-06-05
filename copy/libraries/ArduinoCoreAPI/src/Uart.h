#pragma once

#include <Arduino.h>
#include "api/HardwareSerial.h"
#include "api/RingBuffer.h"
#include "debug.h"

using namespace arduino;

class UartClass : public HardwareSerial
{
public:
    UartClass(USART_TypeDef *sercom);

    void begin(unsigned long baudrate)
    {
        begin(baudrate, SERIAL_8N1);
    };

    void begin(unsigned long baudrate, uint16_t config);

    void end() {
    };

    int available(void);

    int peek(void);

    int read(void);

    void flush(void) {
        // No need to run
    };

    virtual size_t write(uint8_t c)
    {
        while (USART_GetFlagStatus(_sercom, USART_FLAG_TC) == RESET)
            ;
        USART_SendData(_sercom, c);
        return 1;
    };

    using Print::write; // pull in write(str) and write(buf, size) from Print

    explicit operator bool() { return true; }

private:
    USART_TypeDef *_sercom;
    uint8_t comnum;
};

#if defined(CH32_UART1_TX)
extern UartClass Serial1;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial2;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial3;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial4;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial5;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial6;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial7;
#endif
#if defined(CH32_UART1_TX)
extern UartClass Serial8;
#endif

#define Serial Serial1
