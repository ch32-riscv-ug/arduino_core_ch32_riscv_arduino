#pragma once

#include <Arduino.h>
#include <list> // std::list

typedef struct
{
    uint8_t timerId;
    uint16_t interval;
    unsigned int nextRun;
    void *func;
    void *arg;
    bool repeat;
    bool running;
} TimerItem;

class TimerClass
{
public:
    TimerClass() {}

    ~TimerClass()
    {
        stopAll();
    }

    void update();

    uint8_t addOnce(int intervalMs, void (*func)());
    uint8_t addOnce(int intervalMs, void (*func)(void *), void *arg);
    uint8_t addRepeat(int intervalMs, void (*func)());
    uint8_t addRepeat(int intervalMs, void (*func)(void *), void *arg);

    void stop(uint8_t timerId);
    void start(uint8_t timerId);

    void stopAll();

    uint8_t timerCount = 0;
    std::list<TimerItem> _timers;
};

extern TimerClass Timer;
