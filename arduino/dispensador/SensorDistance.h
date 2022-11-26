#ifndef SENSORDISTANCE_H_
#define SENSORDISTANCE_H_

class SensorDistance
{

public:

    int pinTrigger;

    int pinEcho;

    long time;

    int distance;

public:

    SensorDistance(int _pinTrigger, int _pinEcho)
    {
        pinTrigger = _pinTrigger;
        pinEcho = _pinEcho;
        time = 0;
        distance = 0;
    }

    void setup()
    {
        pinMode(pinTrigger, OUTPUT);
        pinMode(pinEcho, INPUT);
        digitalWrite(pinTrigger, LOW);
    }

    void loop()
    {
        digitalWrite(pinTrigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinTrigger, LOW);

        time = pulseIn(pinEcho, HIGH);
        distance = time / 58.2;
    }

    int getDistance()
    {
        return distance;
    }

    void print()
    {
        Serial.print("Distancia: ");
        Serial.print(distance);
        Serial.print(" cm");
        Serial.println();
        delay(100);
    }

};

#endif // SENSORDISTANCE_H_
