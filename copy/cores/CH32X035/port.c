#include <Arduino.h>
#include <debug.h>

/*
 *  board_init
 *  Description: Initialize the board
 *   - The beginning of main() in /EVT/EXAM/GPIO/GPIO_Toggle/User/main.c
 */
void board_init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
}

/*
 *  Delay_Init
 *  Description: Initialize the delay function
 *   - ClockCmd of GPIO_Toggle_INIT() in /EVT/EXAM/GPIO/GPIO_Toggle/User/main.c
 */
void gpion_enable(uint8_t gpion)
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
    // else if (gpion == CH32_GPIO_D)
    //{
    //     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    // }
}