#pragma once

#include <Arduino.h>
#include "api/HardwareI2C.h"
#include "debug.h"

class TwoWire : public arduino::HardwareI2C
{
public:
    TwoWire(I2C_TypeDef *i2c);

    void begin();
    void begin(uint8_t address);
    void end();

    void setClock(uint32_t freq);

    void beginTransmission(uint8_t address);
    uint8_t endTransmission(bool stopBit);
    uint8_t endTransmission(void);

    size_t requestFrom(uint8_t address, size_t len, bool stopBit);
    size_t requestFrom(uint8_t address, size_t len);

    void onReceive(void (*)(int));
    void onRequest(void (*)(void));

    size_t write(uint8_t);
    int available(void);
    int read(void);
    int peek(void);

private:
    I2C_TypeDef *_i2c;

    void _begin();

    bool is_master;
    uint16_t slave_address;
    uint16_t tr_address;
    uint8_t timeout = 30;
    uint32_t _freq;
    uint8_t _len;
};

#if defined(I2C1)
extern TwoWire Wire;
#endif
#if defined(I2C2)
extern TwoWire Wire1;
#endif
