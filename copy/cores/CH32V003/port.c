#include <Arduino.h>
#include <debug.h>

/*
 *  ch32_board_init
 *  Description: Initialize the board
 *   - The beginning of main() in /EVT/EXAM/GPIO/GPIO_Toggle/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V003/blob/main/EVT/EXAM/GPIO/GPIO_Toggle/User/main.c#L54
 */
void ch32_board_init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    ch32_systick_init_config((SystemCoreClock / 1000) - 1); // 1ms
    USART_Printf_Init(115200);
}

/*
 *  ch32_gpion_enable
 *  Description: Initialize gpio
 *   - ClockCmd of GPIO_Toggle_INIT() in /EVT/EXAM/GPIO/GPIO_Toggle/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V003/blob/main/EVT/EXAM/GPIO/GPIO_Toggle/User/main.c#L32
 */
void ch32_gpion_enable(uint8_t gpion)
{
    if (gpion == CH32_GPIO_A)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    // else if (gpion == CH32_GPIO_B)
    //{
    //     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // }
    else if (gpion == CH32_GPIO_C)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }
    else if (gpion == CH32_GPIO_D)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    }
}

extern volatile unsigned long _millis;

/*
 *  SysTick_Handler
 *  Description: SysTick interrupt handler
 *   - SysTick_Handler in /EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V003/blob/main/EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c#L61
 */
void SysTick_Handler(void)
{
    SysTick->SR = 0;
    _millis++;
}

/*
 *  ch32_systick_init_config
 *  Description: Initialize SysTick
 *  - SysTick_Config of SYSTICK_Init_Config() in /EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V003/blob/main/EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c#L43
 */
void ch32_systick_init_config(uint64_t ticks)
{
    NVIC_EnableIRQ(SysTicK_IRQn);
    SysTick->SR &= ~(1 << 0);
    SysTick->CMP = (uint32_t)ticks;
    SysTick->CNT = 0;
    SysTick->CTLR = 0xF;
}

unsigned long millis(void); // common.cpp

/*
 *  ch32_micros
 *  Description: Get the current time in microseconds
 */
unsigned long ch32_micros(void)
{
    unsigned int cnt = SysTick->CNT;
    unsigned int cmp = SysTick->CMP + 1;
    unsigned int micros = (millis() * 1000) + (cnt * 1000 / cmp);
    return micros;
}

/*
 *  ch32_pin_to_adc
 *  Description: Convert pin to ADC channel
 *  https://ch32-riscv-ug.github.io/CH32V003/datasheet_en/CH32V003DS0.PDF#page=15
 */
uint8_t ch32_pin_to_adc(uint8_t pin)
{
    switch (pin)
    {
    case PA2:
        return CH32_ADC1_0;
    case PA1:
        return CH32_ADC1_1;
    case PC4:
        return CH32_ADC1_2;
    case PD2:
        return CH32_ADC1_3;
    case PD3:
        return CH32_ADC1_4;
    case PD5:
        return CH32_ADC1_5;
    case PD6:
        return CH32_ADC1_6;
    case PD4:
        return CH32_ADC1_7;

    default:
        return 0;
    }
}

/*
 *  ch32_adc_init
 *  Description: Initialize the ADC
 *  https://github.com/ch32-riscv-ug/CH32V003/blob/main/EVT/EXAM/ADC/ADC_DMA/User/main.c#L33
 *  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Enable to Disable
 */
void ch32_adc_init(uint8_t adc_unit)
{
    if (adc_unit != CH32_ADC1)
    {
        // only ADC1
        return;
    }

    ADC_InitTypeDef ADC_InitStructure = {};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Enable to Disable
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_Calibration_Vol(ADC1, ADC_CALVOL_50PERCENT);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;

    extern int16_t ch32_adc1_calibrattion_val;
    ch32_adc1_calibrattion_val = 0;
}

/*
 *  ch32_i2c_init
 *  Description: Initialize the I2C
 *  https://github.com/ch32-riscv-ug/CH32V003/blob/main/EVT/EXAM/I2C/I2C_7bit_Mode/User/main.c#L58
 */
void ch32_i2c_init(uint8_t i2c)
{
    if (i2c == 1)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    }
#if defined(I2C2)
    else if (i2c == 2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    }
#endif
}
