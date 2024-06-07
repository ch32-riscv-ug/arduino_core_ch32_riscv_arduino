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
