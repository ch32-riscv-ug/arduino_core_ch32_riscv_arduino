#include <Arduino.h>
#include <debug.h>

int main(void)
{
    board_init();

    setup();

    for (;;)
    {
        loop();
    }
}

void _fini() {}
void _init() {}
