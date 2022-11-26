#ifndef BALANCE_H_
#define BALANCE_H_

#include <HX711.h>

class Balance
{

public:

    HX711 driver;

    int pinDT;

    int pinSCK;

public:

    Balance()
    {
        pinDT = A1;
        pinSCK = A0;
    }

    void setupCalibrate()
    {
        driver.begin(pinDT, pinSCK);
        Serial.print("Lectura del valor del ADC: ");
        Serial.println(driver.read());
        Serial.println("No ponga ningún objeto sobre la driver");
        Serial.println("Destarando...");
        driver.set_scale(); //La escala por defecto es 1
        driver.tare(20);  //El peso actual es considerado Tara.
        Serial.println("Coloque un peso conocido:");
    }

    void loopCalibrate()
    {
        Serial.print("Valor de lectura: ");
        Serial.println(driver.get_value(10),0);
        delay(100);
    }

    void setup()
    {
        driver.begin(pinDT, pinSCK);
        driver.set_scale(439430.25); // Establecemos la escala
        driver.tare(20);
    }

    void getWeight()
    {
        int weight = driver.get_units(20) * 1000.f;
        return weight;
    }

    void loop()
    {
        return;
    }
};

#endif // BALANCE_H_
