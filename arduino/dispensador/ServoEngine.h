#ifndef SERVOENGINE_H_
#define SERVOENGINE_H_

#include <Servo.h>

#include "Timer.h"
#include "Util.h"

class ServoEngine
{
public:

    int pinAttach;

    Servo driver;

    bool smove;

    Timer timer;

public:

    ServoEngine(int _pinAttach)
    {
        pinAttach = _pinAttach;
        smove = false;
    }

    void setup()
    {
        //Serial.println("Servo Setup");
        driver.attach(pinAttach);
        driver.write(0);
        delay(1000);
    }

    int getTime()
    {
        return timer.getTime();
    }

    void loop()
    {
        /* if (timer.endTimer() && smove == true) */
        /*     smove = false; */
        if (smove == true)
        {
            //Serial.println("Dispensando comida...");
            driver.write(0);
            delay(1000);
            driver.write(90);
            delay(1000);
            driver.write(180);
            delay(1000);
        }
    }

    void initDispend(int timeDispend)
    {
        //timer.startTimer(timeDispend);
        smove = true;
    }

    void endDispend()
    {
        smove = false;
    }

    void cerrar()
    {
        driver.write(90);
        delay(1000);
    }
};

#endif // SERVOENGINE_H_
