#include <Arduino.h>
#include <debug.h>

#define CH32_PIN_MODE_ANALOG ((PinMode)100)
#define CH32_PIN_MODE_AF_OD ((PinMode)101)

void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
    GPIO_InitTypeDef GPIO_InitStructure = {};

    GPIO_InitStructure.GPIO_Pin = 1 << (pinNumber & CH32_PIN_MASK);
    GPIO_InitStructure.GPIO_Speed = CH32_GPIO_SPEED;

    // pinMode
    if (pinMode == INPUT)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    }
    else if (pinMode == OUTPUT)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (pinMode == INPUT_PULLUP)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    }
    else if (pinMode == INPUT_PULLDOWN)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    }
    else if (pinMode == OUTPUT_OPENDRAIN)
    {
#if defined(GPIO_Mode_Out_OD)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
#else
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
#endif
    }
    else if (pinMode == CH32_PIN_MODE_ANALOG)
    {
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    }
    else if (pinMode == CH32_PIN_MODE_AF_OD)
    {
#if defined(GPIO_Mode_AF_OD)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
#else
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
#endif
    }

    // GPIO
    if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_A)
    {
        ch32_gpion_enable(CH32_GPIO_A);
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
#if defined(CH32_GPIO_B)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_B)
    {
        ch32_gpion_enable(CH32_GPIO_B);
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
#endif
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_C)
    {
        ch32_gpion_enable(CH32_GPIO_C);
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
#if defined(CH32_GPIO_D)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_D)
    {
        ch32_gpion_enable(CH32_GPIO_D);
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
#endif
#if defined(CH32_GPIO_E)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_E)
    {
        ch32_gpion_enable(CH32_GPIO_E);
        GPIO_Init(GPIOE, &GPIO_InitStructure);
    }
#endif
#if defined(CH32_GPIO_F)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_F)
    {
        ch32_gpion_enable(CH32_GPIO_F);
        GPIO_Init(GPIOF, &GPIO_InitStructure);
    }
#endif
#if defined(CH32_GPIO_G)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_G)
    {
        ch32_gpion_enable(CH32_GPIO_G);
        GPIO_Init(GPIOG, &GPIO_InitStructure);
    }
#endif
}

void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
    uint16_t pin = 1 << (pinNumber & CH32_PIN_MASK);

    // GPIO
    if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_A)
    {
        GPIO_WriteBit(GPIOA, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#if defined(CH32_GPIO_B)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_B)
    {
        GPIO_WriteBit(GPIOB, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#endif
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_C)
    {
        GPIO_WriteBit(GPIOC, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#if defined(CH32_GPIO_D)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_D)
    {
        GPIO_WriteBit(GPIOD, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#endif
#if defined(CH32_GPIO_E)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_E)
    {
        GPIO_WriteBit(GPIOE, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#endif
#if defined(CH32_GPIO_F)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_F)
    {
        GPIO_WriteBit(GPIOF, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#endif
#if defined(CH32_GPIO_G)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_G)
    {
        GPIO_WriteBit(GPIOG, pin, (status == HIGH) ? Bit_SET : Bit_RESET);
    }
#endif
}

PinStatus digitalRead(pin_size_t pinNumber)
{
    uint16_t pin = 1 << (pinNumber & CH32_PIN_MASK);
    PinStatus ret = LOW;

    // GPIO
    if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_A)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOA, pin);
    }
#if defined(CH32_GPIO_B)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_B)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOB, pin);
    }
#endif
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_C)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOC, pin);
    }
#if defined(CH32_GPIO_D)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_D)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOD, pin);
    }
#endif
#if defined(CH32_GPIO_E)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_E)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOE, pin);
    }
#endif
#if defined(CH32_GPIO_F)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_F)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOF, pin);
    }
#endif
#if defined(CH32_GPIO_G)
    else if ((pinNumber & CH32_GPIO_MASK) == CH32_GPIO_G)
    {
        ret = (PinStatus)GPIO_ReadInputDataBit(GPIOG, pin);
    }
#endif

    return ret;
}

uint32_t ch32_adc1_init_flag = 0;
uint32_t ch32_adc2_init_flag = 0;
int16_t ch32_adc1_calibrattion_val = 0;
int16_t ch32_adc2_calibrattion_val = 0;

int analogRead(pin_size_t pinNumber)
{
    uint8_t adc = ch32_pin_to_adc(pinNumber);
    ADC_TypeDef *adc_unit;
    uint8_t ch = adc & CH32_ADC_CH_MASK;
    int16_t calibrattion_val;

    if ((adc & CH32_ADC_UNIT_MASK) == CH32_ADC2)
    {
#if defined(ADC2)
        adc_unit = ADC2;
        if (ch32_adc2_init_flag == 0)
        {
            // init ADC2 Unit
            ch32_adc_init(CH32_ADC2);
        }
        if ((ch32_adc2_init_flag & (1 << ch)) == 0)
        {
            // init pin
            pinMode(pinNumber, CH32_PIN_MODE_ANALOG);
        }
#endif
        calibrattion_val = ch32_adc2_calibrattion_val;
    }
    else
    {
        adc_unit = ADC1;
        if (ch32_adc1_init_flag == 0)
        {
            // init ADC1 Unit
            ch32_adc_init(CH32_ADC1);
        }
        if ((ch32_adc1_init_flag & (1 << ch)) == 0)
        {
            // init pin
            pinMode(pinNumber, CH32_PIN_MODE_ANALOG);
        }
        calibrattion_val = ch32_adc1_calibrattion_val;
    }

    ADC_RegularChannelConfig(adc_unit, ch, 1, CH32_ADC_SAMPLETIME);
    ADC_SoftwareStartConvCmd(adc_unit, ENABLE);

    while (!ADC_GetFlagStatus(adc_unit, ADC_FLAG_EOC))
        ;

    int32_t val = ADC_GetConversionValue(adc_unit) + calibrattion_val;

    if (val <= 0)
    {
        return 0;
    }
    if (4095 <= val)
    {
        return 4095;
    }
    return val;
}

void analogReference(uint8_t /*mode*/)
{
    // do nothing
}

void analogWrite(pin_size_t pinNumber, int value)
{
    printf("pinNumber = %d, value = %d\n", pinNumber, value);
}

volatile unsigned int _millis;

unsigned long millis(void)
{
    return _millis;
}

unsigned long micros(void)
{
    unsigned int micro = ch32_micros();

    while ((micro % 1000) < 5)
    {
        micro = ch32_micros();
    }

    return micro;
}

void delay(unsigned long ms)
{
    unsigned long start = millis();
    if (ms == 0)
    {
        return;
    }
    while (millis() < (start + ms))
    {
        // do nothing
    }
}

void delayMicroseconds(unsigned int us)
{
    unsigned long start = micros();
    if (us == 0)
    {
        return;
    }
    while (micros() < (start + us))
    {
        // do nothing
    }
}

unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout)
{
    printf("pin = %d, state = %d, timeout = %lu\n", pin, state, timeout);
    return 0;
}

unsigned long pulseInLong(pin_size_t pin, uint8_t state, unsigned long timeout)
{
    printf("pin = %d, state = %d, timeout = %lu\n", pin, state, timeout);
    return 0;
}

void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t val)
{
    printf("dataPin = %d, clockPin = %d, bitOrder = %d, val = %d\n", dataPin, clockPin, bitOrder, val);
}

uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder)
{
    printf("dataPin = %d, clockPin = %d, bitOrder = %d\n", dataPin, clockPin, bitOrder);
    return 0;
}

void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode)
{
    printf("interruptNumber = %d, callback = %d, mode = %d\n", interruptNumber, (int)callback, mode);
}

void attachInterruptParam(pin_size_t interruptNumber, voidFuncPtrParam callback, PinStatus mode, void *param)
{
    printf("interruptNumber = %d, callback = %d, mode = %d, param = %d\n", interruptNumber, (int)callback, mode, (int)param);
}

void detachInterrupt(pin_size_t interruptNumber)
{
    printf("interruptNumber = %d\n", interruptNumber);
}

void sysTickUpdate()
{
    Timer.update();
}
