#include "Wire.h"

#define CH32_PIN_MODE_AF_OD ((PinMode)101)

TwoWire::TwoWire(I2C_TypeDef *i2c)
{
    _i2c = i2c;
};

void TwoWire::begin()
{
    end();
    is_master = true;
    slave_address = 0;
    _begin();
}

void TwoWire::_begin()
{
    I2C_InitTypeDef I2C_InitTSturcture = {};

    if (_i2c == I2C1)
    {
        pinMode(CH32_I2C1_SCL, CH32_PIN_MODE_AF_OD);
        pinMode(CH32_I2C1_SDA, CH32_PIN_MODE_AF_OD);
        ch32_i2c_init(1);
    }
#if defined(I2C2)
    else if (_i2c == I2C2)
    {
        pinMode(CH32_I2C2_SCL, CH32_PIN_MODE_AF_OD);
        pinMode(CH32_I2C2_SDA, CH32_PIN_MODE_AF_OD);
        ch32_i2c_init(2);
    }
#endif

    I2C_InitTSturcture.I2C_ClockSpeed = 100000;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = slave_address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(_i2c, &I2C_InitTSturcture);

    I2C_Cmd(_i2c, ENABLE);

    if (is_master)
    {
        // Master
    }
}

void TwoWire::begin(uint8_t address)
{
    end();
    is_master = false;
    slave_address = address;
    _begin();
}

void TwoWire::end()
{
    is_master = false;
    slave_address = 0;

    if (tr_address != 0)
    {
        I2C_GenerateSTOP(_i2c, ENABLE);
        tr_address = 0;
    }
}

void TwoWire::setClock(uint32_t freq)
{
    _freq = freq;
}

void TwoWire::beginTransmission(uint8_t address)
{
    tr_address = address;

    // I2C_FLAG_BUSY
    unsigned long start_time = millis();
    while (I2C_GetFlagStatus(_i2c, I2C_FLAG_BUSY) != RESET)
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            tr_address = 0;
            return;
        }
    }

    // I2C_GenerateSTART
    I2C_GenerateSTART(_i2c, ENABLE);

    start_time = millis();
    while (!I2C_CheckEvent(_i2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            I2C_GenerateSTOP(_i2c, ENABLE);
            tr_address = 0;
            return;
        }
    }

    I2C_Send7bitAddress(_i2c, tr_address << 1, I2C_Direction_Transmitter);

    start_time = millis();
    while (!I2C_CheckEvent(_i2c, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            I2C_GenerateSTOP(_i2c, ENABLE);
            tr_address = 0;
            return;
        }
    }
}

uint8_t TwoWire::endTransmission(bool stopBit)
{
    if (tr_address == 0)
    {
        return 2;
    }

    if (stopBit)
    {
        I2C_GenerateSTOP(_i2c, ENABLE);
        tr_address = 0;
    }

    return 0;
}

uint8_t TwoWire::endTransmission(void)
{
    return endTransmission((uint8_t) true);
}

size_t TwoWire::requestFrom(uint8_t address, size_t len, bool /*stopBit*/)
{
    tr_address = address;
    _len = len;

    I2C_GenerateSTART(_i2c, ENABLE);

    unsigned long start_time = millis();
    while (!I2C_CheckEvent(_i2c, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            I2C_GenerateSTOP(_i2c, ENABLE);
            tr_address = 0;
            return 2;
        }
    }

    I2C_Send7bitAddress(_i2c, tr_address << 1, I2C_Direction_Receiver);

    start_time = millis();
    while (!I2C_CheckEvent(_i2c, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            I2C_GenerateSTOP(_i2c, ENABLE);
            tr_address = 0;
            return 2;
        }
    }

    return 0;
}

size_t TwoWire::requestFrom(uint8_t address, size_t len)
{
    requestFrom(address, len, true);
    return 1;
}

void TwoWire::onReceive(void (*)(int))
{
}

void TwoWire::onRequest(void (*)(void))
{
}

size_t TwoWire::write(uint8_t c)
{
    if (tr_address == 0)
    {
        return 0;
    }

    I2C_SendData(_i2c, c);

    unsigned long start_time = millis();
    while (!I2C_CheckEvent(_i2c, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            I2C_GenerateSTOP(_i2c, ENABLE);
            tr_address = 0;
            return 0;
        }
    }

    return 1;
}

int TwoWire::available(void)
{
    if (_len == 0)
    {
        return 0;
    }
    return 1;
}

int TwoWire::read(void)
{
    if (tr_address == 0)
    {
        return 0;
    }
    if (_len == 0)
    {
        return 0;
    }

    I2C_AcknowledgeConfig(_i2c, ENABLE);
    if (_len == 1)
    {
        I2C_AcknowledgeConfig(_i2c, DISABLE);
    }

    unsigned long start_time = millis();
    while (I2C_GetFlagStatus(_i2c, I2C_FLAG_RXNE) == RESET)
    {
        if (this->timeout < (millis() - start_time))
        {
            // Timeout
            I2C_GenerateSTOP(_i2c, ENABLE);
            tr_address = 0;
            return 0;
        }
    }

    uint8_t temp = I2C_ReceiveData(_i2c);

    _len--;
    if (_len == 0)
    {
        I2C_GenerateSTOP(_i2c, ENABLE);
    }

    return temp;
}

int TwoWire::peek(void)
{
    return 0;
}

#if defined(I2C1)
TwoWire Wire(I2C1);
#endif
#if defined(I2C2)
TwoWire Wire1(I2C2);
#endif
