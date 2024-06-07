#include <stdint.h>

#ifdef __cplusplus
#include <ArduinoCoreAPI.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    void setup();
    void loop();
    void ch32_board_init();
    void ch32_gpion_enable(uint8_t gpion);

    void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
    void ch32_systick_init_config(uint64_t ticks);
    unsigned long ch32_micros(void);

#ifdef __cplusplus
}
#endif

#define CH32_GPIO_A (1 << 5)
#define CH32_GPIO_B (2 << 5)
#define CH32_GPIO_C (3 << 5)
#define CH32_GPIO_D (4 << 5)
// #define CH32_GPIO_E (5 << 5)
// #define CH32_GPIO_F (6 << 5)
// #define CH32_GPIO_G (7 << 5)
#define CH32_GPIO_MASK (0xe0)
#define CH32_PIN_MASK (0x1f)

#define CH32_GPIO_SPEED GPIO_Speed_50MHz

#define PA0 (CH32_GPIO_A | (0))
#define PA1 (CH32_GPIO_A | (1))
#define PA2 (CH32_GPIO_A | (2))
#define PA3 (CH32_GPIO_A | (3))
#define PA4 (CH32_GPIO_A | (4))
#define PA5 (CH32_GPIO_A | (5))
#define PA6 (CH32_GPIO_A | (6))
#define PA7 (CH32_GPIO_A | (7))
#define PA8 (CH32_GPIO_A | (8))
#define PA9 (CH32_GPIO_A | (9))
#define PA10 (CH32_GPIO_A | (10))
#define PA11 (CH32_GPIO_A | (11))
#define PA12 (CH32_GPIO_A | (12))
#define PA13 (CH32_GPIO_A | (13))
#define PA14 (CH32_GPIO_A | (14))
#define PA15 (CH32_GPIO_A | (15))

#define PB0 (CH32_GPIO_B | (0))
#define PB1 (CH32_GPIO_B | (1))
#define PB2 (CH32_GPIO_B | (2))
#define PB3 (CH32_GPIO_B | (3))
#define PB4 (CH32_GPIO_B | (4))
#define PB5 (CH32_GPIO_B | (5))
#define PB6 (CH32_GPIO_B | (6))
#define PB7 (CH32_GPIO_B | (7))
#define PB8 (CH32_GPIO_B | (8))
#define PB9 (CH32_GPIO_B | (9))
#define PB10 (CH32_GPIO_B | (10))
#define PB11 (CH32_GPIO_B | (11))
#define PB12 (CH32_GPIO_B | (12))
#define PB13 (CH32_GPIO_B | (13))
#define PB14 (CH32_GPIO_B | (14))
#define PB15 (CH32_GPIO_B | (15))

#define PC0 (CH32_GPIO_C | (0))
#define PC1 (CH32_GPIO_C | (1))
#define PC2 (CH32_GPIO_C | (2))
#define PC3 (CH32_GPIO_C | (3))
#define PC4 (CH32_GPIO_C | (4))
#define PC5 (CH32_GPIO_C | (5))
#define PC6 (CH32_GPIO_C | (6))
#define PC7 (CH32_GPIO_C | (7))
#define PC8 (CH32_GPIO_C | (8))
#define PC9 (CH32_GPIO_C | (9))
#define PC10 (CH32_GPIO_C | (10))
#define PC11 (CH32_GPIO_C | (11))
#define PC12 (CH32_GPIO_C | (12))
#define PC13 (CH32_GPIO_C | (13))
#define PC14 (CH32_GPIO_C | (14))
#define PC15 (CH32_GPIO_C | (15))

#define PD0 (CH32_GPIO_D | (0))
#define PD1 (CH32_GPIO_D | (1))
#define PD2 (CH32_GPIO_D | (2))
// #define PD3 (CH32_GPIO_D | (3))
// #define PD4 (CH32_GPIO_D | (4))
// #define PD5 (CH32_GPIO_D | (5))
// #define PD6 (CH32_GPIO_D | (6))
// #define PD7 (CH32_GPIO_D | (7))
// #define PD8 (CH32_GPIO_D | (8))
// #define PD9 (CH32_GPIO_D | (9))
// #define PD10 (CH32_GPIO_D | (10))
// #define PD11 (CH32_GPIO_D | (11))
// #define PD12 (CH32_GPIO_D | (12))
// #define PD13 (CH32_GPIO_D | (13))
// #define PD14 (CH32_GPIO_D | (14))
// #define PD15 (CH32_GPIO_D | (15))

// #define PE0 (CH32_GPIO_E | (0))
// #define PE1 (CH32_GPIO_E | (1))
// #define PE2 (CH32_GPIO_E | (2))
// #define PE3 (CH32_GPIO_E | (3))
// #define PE4 (CH32_GPIO_E | (4))
// #define PE5 (CH32_GPIO_E | (5))
// #define PE6 (CH32_GPIO_E | (6))
// #define PE7 (CH32_GPIO_E | (7))
// #define PE8 (CH32_GPIO_E | (8))
// #define PE9 (CH32_GPIO_E | (9))
// #define PE10 (CH32_GPIO_E | (10))
// #define PE11 (CH32_GPIO_E | (11))
// #define PE12 (CH32_GPIO_E | (12))
// #define PE13 (CH32_GPIO_E | (13))
// #define PE14 (CH32_GPIO_E | (14))
// #define PE15 (CH32_GPIO_E | (15))

// #define PF0 (CH32_GPIO_F | (0))
// #define PF1 (CH32_GPIO_F | (1))
// #define PF2 (CH32_GPIO_F | (2))
// #define PF3 (CH32_GPIO_F | (3))
// #define PF4 (CH32_GPIO_F | (4))
// #define PF5 (CH32_GPIO_F | (5))
// #define PF6 (CH32_GPIO_F | (6))
// #define PF7 (CH32_GPIO_F | (7))
// #define PF8 (CH32_GPIO_F | (8))
// #define PF9 (CH32_GPIO_F | (9))
// #define PF10 (CH32_GPIO_F | (10))
// #define PF11 (CH32_GPIO_F | (11))
// #define PF12 (CH32_GPIO_F | (12))
// #define PF13 (CH32_GPIO_F | (13))
// #define PF14 (CH32_GPIO_F | (14))
// #define PF15 (CH32_GPIO_F | (15))

// #define PG0 (CH32_GPIO_G | (0))
// #define PG1 (CH32_GPIO_G | (1))
// #define PG2 (CH32_GPIO_G | (2))
// #define PG3 (CH32_GPIO_G | (3))
// #define PG4 (CH32_GPIO_G | (4))
// #define PG5 (CH32_GPIO_G | (5))
// #define PG6 (CH32_GPIO_G | (6))
// #define PG7 (CH32_GPIO_G | (7))
// #define PG8 (CH32_GPIO_G | (8))
// #define PG9 (CH32_GPIO_G | (9))
// #define PG10 (CH32_GPIO_G | (10))
// #define PG11 (CH32_GPIO_G | (11))
// #define PG12 (CH32_GPIO_G | (12))
// #define PG13 (CH32_GPIO_G | (13))
// #define PG14 (CH32_GPIO_G | (14))
// #define PG15 (CH32_GPIO_G | (15))

#define CH32_UART1_TX PA9
#define CH32_UART2_TX PA2
#define CH32_UART3_TX PB10
#define CH32_UART4_TX PB0
