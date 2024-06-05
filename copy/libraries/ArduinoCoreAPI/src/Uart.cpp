#include <Arduino.h>
#include "Uart.h"

#define CH32_UART1 0
#define CH32_UART2 1
#define CH32_UART3 2
#define CH32_UART4 3
#define CH32_UART5 4
#define CH32_UART6 5
#define CH32_UART7 6
#define CH32_UART8 7

#define UART_BUFF_SIZE 100
#define UART_BUFF_COUNT 8

char *uart_buff[UART_BUFF_COUNT] = {};
uint16_t uart_buff_head[UART_BUFF_COUNT] = {};
uint16_t uart_buff_tail[UART_BUFF_COUNT] = {};

UartClass::UartClass(USART_TypeDef *sercom)
{
    _sercom = sercom;
};

void UartClass::begin(unsigned long baudrate, uint16_t config)
{
    USART_InitTypeDef USART_InitStructure = {};
    NVIC_InitTypeDef NVIC_InitStructure = {};

    USART_InitStructure.USART_BaudRate = baudrate;

    if (config == SERIAL_8N2)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
    }
    else if (config == SERIAL_8E1)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_Parity = USART_Parity_Even;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    else if (config == SERIAL_8E2)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_Parity = USART_Parity_Even;
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
    }
    else if (config == SERIAL_8O1)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    else if (config == SERIAL_8O2)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
        USART_InitStructure.USART_StopBits = USART_StopBits_2;
    }
    else
    {
        // SERIAL_8N1
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
    }
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(_sercom, &USART_InitStructure);

    USART_ITConfig(_sercom, USART_IT_RXNE, ENABLE);

#if defined(USART1) && defined(CH32_UART1_TX)
    if (_sercom == USART1)
    {
        comnum = CH32_UART1;
        NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        // Initialized
        // pinMode(CH32_UART1_TX, OUTPUT);
    }
#elif defined(UART1) && defined(CH32_UART1_TX)
    if (_sercom == UART1)
    {
        comnum = CH32_UART1;
        NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
        // Initialized
        // pinMode(CH32_UART1_TX, OUTPUT);
    }
#endif

#if defined(USART2) && defined(CH32_UART2_TX)
    if (_sercom == USART2)
    {
        comnum = CH32_UART2;
        NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
        pinMode(CH32_UART2_TX, OUTPUT);
    }
#elif defined(UART2) && defined(CH32_UART2_TX)
    if (_sercom == UART2)
    {
        comnum = CH32_UART2;
        NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;
        pinMode(CH32_UART2_TX, OUTPUT);
    }
#endif

#if defined(USART3) && defined(CH32_UART3_TX)
    if (_sercom == USART3)
    {
        comnum = CH32_UART3;
        NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
        pinMode(CH32_UART3_TX, OUTPUT);
    }
#elif defined(UART3) && defined(CH32_UART3_TX)
    if (_sercom == UART3)
    {
        comnum = CH32_UART3;
        NVIC_InitStructure.NVIC_IRQChannel = UART3_IRQn;
        pinMode(CH32_UART3_TX, OUTPUT);
    }
#endif

#if defined(USART4) && defined(CH32_UART4_TX)
    if (_sercom == USART4)
    {
        comnum = CH32_UART4;
        NVIC_InitStructure.NVIC_IRQChannel = USART4_IRQn;
        pinMode(CH32_UART4_TX, OUTPUT);
    }
#elif defined(UART4) && defined(CH32_UART4_TX)
    if (_sercom == UART4)
    {
        comnum = CH32_UART4;
        NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
        pinMode(CH32_UART4_TX, OUTPUT);
    }
#endif

#if defined(USART5) && defined(CH32_UART5_TX)
    if (_sercom == USART5)
    {
        comnum = CH32_UART5;
        NVIC_InitStructure.NVIC_IRQChannel = USART5_IRQn;
        pinMode(CH32_UART5_TX, OUTPUT);
    }
#elif defined(UART5) && defined(CH32_UART5_TX)
    if (_sercom == UART5)
    {
        comnum = CH32_UART5;
        NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
        pinMode(CH32_UART5_TX, OUTPUT);
    }
#endif

#if defined(USART6) && defined(CH32_UART6_TX)
    if (_sercom == USART6)
    {
        comnum = CH32_UART6;
        NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
        pinMode(CH32_UART6_TX, OUTPUT);
    }
#elif defined(UART6) && defined(CH32_UART6TX)
    if (_sercom == UART6)
    {
        comnum = CH32_UART6;
        NVIC_InitStructure.NVIC_IRQChannel = UART6_IRQn;
        pinMode(CH32_UART6_TX, OUTPUT);
    }
#endif

#if defined(USART7) && defined(CH32_UART7_TX)
    if (_sercom == USART7)
    {
        comnum = CH32_UART7;
        NVIC_InitStructure.NVIC_IRQChannel = USART7_IRQn;
        pinMode(CH32_UART7_TX, OUTPUT);
    }
#elif defined(UART7) && defined(CH32_UART7_TX)
    if (_sercom == UART7)
    {
        comnum = CH32_UART7;
        NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
        pinMode(CH32_UART7_TX, OUTPUT);
    }
#endif

#if defined(USART8) && defined(CH32_UART8_TX)
    if (_sercom == USART8)
    {
        comnum = CH32_UART8;
        NVIC_InitStructure.NVIC_IRQChannel = USART8_IRQn;
        pinMode(CH32_UART8_TX, OUTPUT);
    }
#elif defined(UART8) && defined(CH32_UART8_TX)
    if (_sercom == UART8)
    {
        comnum = CH32_UART8;
        NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
        pinMode(CH32_UART8_TX, OUTPUT);
    }
#endif

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(_sercom, ENABLE);

    uart_buff[comnum] = (char *)malloc(UART_BUFF_SIZE);
    uart_buff_head[comnum] = 0;
    uart_buff_tail[comnum] = 0;
};

int UartClass::available(void)
{
    return (uart_buff_head[comnum] != uart_buff_tail[comnum]);
};

int UartClass::peek(void)
{
    return uart_buff[comnum][uart_buff_tail[comnum]];
};

int UartClass::read(void)
{
    int ret = uart_buff[comnum][uart_buff_tail[comnum]];
    uart_buff_tail[comnum]++;
    uart_buff_tail[comnum] %= UART_BUFF_SIZE;
    return ret;
};

//==============================================================================

#if defined(USART1) && defined(CH32_UART1_TX)
UartClass Serial1(USART1);
#elif defined(UART1) && defined(CH32_UART1_TX)
UartClass Serial1(UART1);
#endif

#if defined(USART2) && defined(CH32_UART2_TX)
UartClass Serial2(USART2);
#elif defined(UART2) && defined(CH32_UART2_TX)
UartClass Serial2(UART2);
#endif

#if defined(USART3) && defined(CH32_UART3_TX)
UartClass Serial3(USART3);
#elif defined(UART3) && defined(CH32_UART3_TX)
UartClass Serial3(UART3);
#endif

#if defined(USART4) && defined(CH32_UART4_TX)
UartClass Serial4(USART4);
#elif defined(UART4) && defined(CH32_UART4_TX)
UartClass Serial4(UART4);
#endif

#if defined(USART5) && defined(CH32_UART5_TX)
UartClass Serial5(USART5);
#elif defined(UART5) && defined(CH32_UART5_TX)
UartClass Serial5(UART5);
#endif

#if defined(USART6) && defined(CH32_UART6_TX)
UartClass Serial6(USART6);
#elif defined(UART6) && defined(CH32_UART6_TX)
UartClass Serial6(UART6);
#endif

#if defined(USART7) && defined(CH32_UART7_TX)
UartClass Serial7(USART7);
#elif defined(UART7) && defined(CH32_UART7_TX)
UartClass Serial7(UART7);
#endif

#if defined(USART8) && defined(CH32_UART8_TX)
UartClass Serial8(USART8);
#elif defined(UART8) && defined(CH32_UART8_TX)
UartClass Serial8(UART8);
#endif

#define Serial1 Serial

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(USART1) && defined(CH32_UART1_TX)
    void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART1_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        uart_buff[CH32_UART1][uart_buff_head[CH32_UART1]] = USART_ReceiveData(USART1);
        uart_buff_head[CH32_UART1]++;
        uart_buff_head[CH32_UART1] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART1) && defined(CH32_UART1_TX)
    void UART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART1_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART1, USART_IT_RXNE);
        uart_buff[CH32_UART1][uart_buff_head[CH32_UART1]] = USART_ReceiveData(UART1);
        uart_buff_head[CH32_UART1]++;
        uart_buff_head[CH32_UART1] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART2) && defined(CH32_UART2_TX)
    void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART2_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        uart_buff[CH32_UART2][uart_buff_head[CH32_UART2]] = USART_ReceiveData(USART2);
        uart_buff_head[CH32_UART2]++;
        uart_buff_head[CH32_UART2] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART2) && defined(CH32_UART2_TX)
    void UART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART2_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART2, USART_IT_RXNE);
        uart_buff[CH32_UART2][uart_buff_head[CH32_UART2]] = USART_ReceiveData(UART2);
        uart_buff_head[CH32_UART2]++;
        uart_buff_head[CH32_UART2] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART3) && defined(CH32_UART3_TX)
    void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART3_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        uart_buff[CH32_UART3][uart_buff_head[CH32_UART3]] = USART_ReceiveData(USART3);
        uart_buff_head[CH32_UART3]++;
        uart_buff_head[CH32_UART3] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART3) && defined(CH32_UART3_TX)
    void UART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART3_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART3, USART_IT_RXNE);
        uart_buff[CH32_UART3][uart_buff_head[CH32_UART3]] = USART_ReceiveData(UART3);
        uart_buff_head[CH32_UART3]++;
        uart_buff_head[CH32_UART3] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART4) && defined(CH32_UART4_TX)
    void USART4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART4_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART4, USART_IT_RXNE);
        uart_buff[CH32_UART4][uart_buff_head[CH32_UART4]] = USART_ReceiveData(USART4);
        uart_buff_head[CH32_UART4]++;
        uart_buff_head[CH32_UART4] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART4) && defined(CH32_UART4_TX)
    void UART4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART4_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
        uart_buff[CH32_UART4][uart_buff_head[CH32_UART4]] = USART_ReceiveData(UART4);
        uart_buff_head[CH32_UART4]++;
        uart_buff_head[CH32_UART4] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART5) && defined(CH32_UART5_TX)
    void USART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART5_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART5, USART_IT_RXNE);
        uart_buff[CH32_UART5][uart_buff_head[CH32_UART5]] = USART_ReceiveData(USART5);
        uart_buff_head[CH32_UART5]++;
        uart_buff_head[CH32_UART5] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART5) && defined(CH32_UART5_TX)
    void UART5_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART5_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
        uart_buff[CH32_UART5][uart_buff_head[CH32_UART5]] = USART_ReceiveData(UART5);
        uart_buff_head[CH32_UART5]++;
        uart_buff_head[CH32_UART5] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART6) && defined(CH32_UART6_TX)
    void USART6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART6_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);
        uart_buff[CH32_UART6][uart_buff_head[CH32_UART6]] = USART_ReceiveData(USART6);
        uart_buff_head[CH32_UART6]++;
        uart_buff_head[CH32_UART6] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART6) && defined(CH32_UART6_TX)
    void UART6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART6_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART6, USART_IT_RXNE);
        uart_buff[CH32_UART6][uart_buff_head[CH32_UART6]] = USART_ReceiveData(UART6);
        uart_buff_head[CH32_UART6]++;
        uart_buff_head[CH32_UART6] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART7) && defined(CH32_UART7_TX)
    void USART7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART7_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART7, USART_IT_RXNE);
        uart_buff[CH32_UART7][uart_buff_head[CH32_UART7]] = USART_ReceiveData(USART7);
        uart_buff_head[CH32_UART7]++;
        uart_buff_head[CH32_UART7] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART7) && defined(CH32_UART7_TX)
    void UART7_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART7_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART7, USART_IT_RXNE);
        uart_buff[CH32_UART7][uart_buff_head[CH32_UART7]] = USART_ReceiveData(UART7);
        uart_buff_head[CH32_UART7]++;
        uart_buff_head[CH32_UART7] %= UART_BUFF_SIZE;
    }
#endif

#if defined(USART8) && defined(CH32_UART8_TX)
    void USART8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void USART8_IRQHandler(void)
    {
        USART_ClearITPendingBit(USART8, USART_IT_RXNE);
        uart_buff[CH32_UART8][uart_buff_head[CH32_UART8]] = USART_ReceiveData(USART8);
        uart_buff_head[CH32_UART8]++;
        uart_buff_head[CH32_UART8] %= UART_BUFF_SIZE;
    }
#endif
#if defined(UART8) && defined(CH32_UART8_TX)
    void UART8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void UART8_IRQHandler(void)
    {
        USART_ClearITPendingBit(UART8, USART_IT_RXNE);
        uart_buff[CH32_UART8][uart_buff_head[CH32_UART8]] = USART_ReceiveData(UART8);
        uart_buff_head[CH32_UART8]++;
        uart_buff_head[CH32_UART8] %= UART_BUFF_SIZE;
    }
#endif

#ifdef __cplusplus
}
#endif