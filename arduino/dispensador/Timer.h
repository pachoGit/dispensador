#ifndef TIMER_H_
#define TIMER_H_

class Timer
{

public:

    int end;

    int start;

public:

    Timer()
    {
        end = 0;
        start = 0;
    }

    void startTimer(int _end)
    {
        start = millis();
        end = _end;
    }

    int getTime()
    {
        return millis() - start;
    }

    bool endTimer()
    {
        if (millis() - start >= end)
        {
            start = 0;
            end = 0;
            return true;
        }
        return false;
    }

};

#endif // TIMER_H_
