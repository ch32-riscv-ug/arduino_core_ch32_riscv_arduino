#include <Arduino.h>
#include <debug.h>

/*
 *  ch32_board_init
 *  Description: Initialize the board
 *   - The beginning of main() in /EVT/EXAM/GPIO/GPIO_Toggle/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V103/blob/main/EVT/EXAM/GPIO/GPIO_Toggle/User/main.c#L55
 */
void ch32_board_init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    ch32_systick_init_config((SystemCoreClock / 8 / 1000) - 1); // 1ms
    USART_Printf_Init(115200);
}

/*
 *  ch32_gpion_enable
 *  Description: Initialize gpio
 *   - ClockCmd of GPIO_Toggle_INIT() in /EVT/EXAM/GPIO/GPIO_Toggle/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V103/blob/main/EVT/EXAM/GPIO/GPIO_Toggle/User/main.c#L33
 */
void ch32_gpion_enable(uint8_t gpion)
{
    if (gpion == CH32_GPIO_A)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    }
    else if (gpion == CH32_GPIO_B)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    }
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
 *  https://github.com/ch32-riscv-ug/CH32V103/blob/main/EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c#L91
 */
void SysTick_Handler(void)
{
    SysTick->CNTL0 = 0;
    SysTick->CNTL1 = 0;
    SysTick->CNTL2 = 0;
    SysTick->CNTL3 = 0;
    SysTick->CNTH0 = 0;
    SysTick->CNTH1 = 0;
    SysTick->CNTH2 = 0;
    SysTick->CNTH3 = 0;
    _millis++;
}

/*
 *  ch32_systick_init_config
 *  Description: Initialize SysTick
 *  - SysTick_Config of SYSTICK_Init_Config() in /EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c
 *  https://github.com/ch32-riscv-ug/CH32V103/blob/main/EVT/EXAM/SYSTICK/SYSTICK_Interrupt/User/main.c#L35
 */
void ch32_systick_init_config(uint64_t ticks)
{
    SysTick->CTLR = 0x0000;

    SysTick->CNTL0 = 0;
    SysTick->CNTL1 = 0;
    SysTick->CNTL2 = 0;
    SysTick->CNTL3 = 0;
    SysTick->CNTH0 = 0;
    SysTick->CNTH1 = 0;
    SysTick->CNTH2 = 0;
    SysTick->CNTH3 = 0;

    SysTick->CMPLR0 = (u8)(ticks & 0xFF);
    SysTick->CMPLR1 = (u8)(ticks >> 8);
    SysTick->CMPLR2 = (u8)(ticks >> 16);
    SysTick->CMPLR3 = (u8)(ticks >> 24);
    SysTick->CMPHR0 = (u8)(ticks >> 32);
    SysTick->CMPHR1 = (u8)(ticks >> 40);
    SysTick->CMPHR2 = (u8)(ticks >> 48);
    SysTick->CMPHR3 = (u8)(ticks >> 56);

    NVIC_SetPriority(SysTicK_IRQn, 15);
    NVIC_EnableIRQ(SysTicK_IRQn);

    SysTick->CTLR = (1 << 0);
}

unsigned long millis(void); // common.cpp

/*
 *  ch32_micros
 *  Description: Get the current time in microseconds
 */
unsigned long ch32_micros(void)
{
    unsigned int cnt = *(uint32_t *)&SysTick->CNTL0;
    unsigned int cmp = *(uint32_t *)&SysTick->CMPLR0 + 1;
    unsigned int micros = (millis() * 1000) + (cnt * 1000 / cmp);
    return micros;
}
