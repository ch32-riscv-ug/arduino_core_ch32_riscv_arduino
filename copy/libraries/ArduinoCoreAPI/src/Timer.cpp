#include "Timer.h"

void TimerClass::update()
{
    unsigned int now = millis();
    for (std::list<TimerItem>::iterator it = _timers.begin(); it != _timers.end(); it++)
    {
        if (it->running && now >= it->nextRun)
        {
            if (it->repeat)
            {
                it->nextRun = now + it->interval;
            }
            else
            {
                it->running = false;
            }
            if (it->arg)
            {
                ((void (*)(void *))it->func)(it->arg);
            }
            else
            {
                ((void (*)())it->func)();
            }
        }
    }
}

uint8_t TimerClass::addOnce(int intervalMs, void (*func)())
{
    if (timerCount == 255)
    {
        TimerItem &item = _timers.back();
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = NULL;
        item.repeat = false;
        item.running = true;
        return item.timerId;
    }
    else
    {
        TimerItem item;
        item.timerId = timerCount++;
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = NULL;
        item.repeat = false;
        item.running = true;
        _timers.push_back(item);
        return item.timerId;
    }
}

uint8_t TimerClass::addOnce(int intervalMs, void (*func)(void *), void *arg)
{
    if (timerCount == 255)
    {
        TimerItem &item = _timers.back();
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = arg;
        item.repeat = false;
        item.running = true;
        return item.timerId;
    }
    else
    {
        TimerItem item;
        item.timerId = timerCount++;
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = arg;
        item.repeat = false;
        item.running = true;
        return item.timerId;
    }
}

uint8_t TimerClass::addRepeat(int intervalMs, void (*func)())
{
    if (timerCount == 255)
    {
        TimerItem &item = _timers.back();
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = NULL;
        item.repeat = true;
        item.running = true;
        return item.timerId;
    }
    else
    {
        TimerItem item;
        item.timerId = timerCount++;
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = NULL;
        item.repeat = true;
        item.running = true;
        _timers.push_back(item);
        return item.timerId;
    }
}

uint8_t TimerClass::addRepeat(int intervalMs, void (*func)(void *), void *arg)
{
    if (timerCount == 255)
    {
        TimerItem &item = _timers.back();
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = arg;
        item.repeat = true;
        item.running = true;
        return item.timerId;
    }
    else
    {
        TimerItem item;
        item.timerId = timerCount++;
        item.interval = intervalMs;
        item.nextRun = millis() + intervalMs;
        item.func = (void *)func;
        item.arg = arg;
        item.repeat = true;
        item.running = true;
        _timers.push_back(item);
        return item.timerId;
    }
}

void TimerClass::stop(uint8_t timerId)
{
    for (std::list<TimerItem>::iterator it = _timers.begin(); it != _timers.end(); it++)
    {
        if (it->timerId == timerId)
        {
            it->running = false;
            return;
        }
    }
}

void TimerClass::start(uint8_t timerId)
{
    for (std::list<TimerItem>::iterator it = _timers.begin(); it != _timers.end(); it++)
    {
        if (it->timerId == timerId)
        {
            it->running = true;
            it->nextRun = millis() + it->interval;
            return;
        }
    }
}

void TimerClass::stopAll()
{
    for (std::list<TimerItem>::iterator it = _timers.begin(); it != _timers.end(); it++)
    {
        it->running = false;
    }
}

TimerClass Timer;
