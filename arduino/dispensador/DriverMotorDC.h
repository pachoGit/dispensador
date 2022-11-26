#ifndef DRIVERMOTORDC_H_
#define DRIVERMOTORDC_H_

class DriverMotorDC
{

public:

    int enableA;  // Posicion en el arduino del enable A del driver
    int in1; // Posicion en el arduino de la entrada 1 del driver
    int in2; // Posicion en el arduino de la entrada 2 del driver

    bool smove;
    unsigned long timeDispend;

public:

    DriverMotorDC()
    {
        enableA = 3;
        in1 = 6;
        in2 = 7;
        smove = false;
        timeDispend = 0;
    }

    void setup()
    {
        pinMode(enableA, OUTPUT);
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);

    }

    void loop()
    {
        /* if (smove == false) */
        /* { */
        /*     digitalWrite(in1, LOW); */
        /*     digitalWrite(in2, LOW); */
        /*     delay(2000); */
        /*     analogWrite(enableA, 255); */
        /* } */

        if (smove == true)
        {
            analogWrite(enableA, 255);
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            Serial.println("Dispensando agua...");
            delay(timeDispend); // 100ml
            Serial.println("Termino dispensar el agua");
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            delay(2000);
            smove = false;
        }

        // Invertimos el sentido del giro del motor
        //digitalWrite(in1, LOW);
        //digitalWrite(in2, HIGH);
        //delay(2000);

        // Apagamos el motor
        //digitalWrite(in1, LOW);
        //digitalWrite(in2, LOW);
        //delay(2000);
    }

};

#endif // DRIVERMOTORDC_H_
