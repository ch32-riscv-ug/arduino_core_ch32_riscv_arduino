#include <Arduino.h>
#include <debug.h>

int main(void) __attribute__((weak));
int main(void)
{
    ch32_board_init();

    setup();

    for (;;)
    {
        loop();
    }
}

void _fini() {}
void _init() {}
