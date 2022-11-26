#include <TimeLib.h>

#include "SensorDistance.h"
#include "ServoEngine.h"
#include "DriverMotorDC.h"
#include "Balance.h"
#include "Util.h"

SensorDistance sensorGrain(13, 12);
SensorDistance sensorWater(10, 11);
ServoEngine servo(9);
DriverMotorDC motordc;
//Balance balance;

int HOUR = 0;
int MINUTE = 0;

Detail currentDetail = {0, 0, 0, 2}; // La informacion actual que se esta procesando
String input = ""; // Input del serial

unsigned long timeForDispend = 0;
unsigned long startTime = 0;

void processDetail(Detail &detail)
{
  //Serial.println("Entro a processDetail");
  if (detail.hour == HOUR && detail.minute == MINUTE) // Tiempo de dispensar
  {
    //Serial.println("Tiempo de dispensar jajaja");
    if (isSameDetail(detail, currentDetail))
      return;
    currentDetail.hour = detail.hour;
    currentDetail.minute = detail.minute;
    currentDetail.amount = detail.amount;
    currentDetail.type = detail.type;

    timeForDispend = (25000 * detail.amount)  / 1000;
    startTime = millis();
    /* String message = "Enviando comando a servo para dispensar" + String(timeForDispend); */
    /* Serial.println(message); */
    servo.initDispend(timeForDispend);
    /* String message = "Tiempo: " + String(timeForDispend) + " Inicio: " + String(startTime); */
    /* Serial.println(message); */
  }
}

void resolveInput()
{
  if (input.length() <= 1)
    return;

  String datetime = input.substring(input.indexOf("_")+1);
  String shour = datetime.substring(0, 2);
  String sminute = datetime.substring(3);
  HOUR = shour.toInt();
  MINUTE = sminute.toInt();

  input = input.substring(0, input.indexOf("_"));

  String data = "";
  for (int i = 0; i < input.length(); i++)
  {
    char caracter = input.charAt(i);
    if (caracter == '-')
    {
      //String message = "Detail para evaluar: " + data + "en " + String(HOUR) + " " + String(MINUTE);
      //Serial.println(message);
      Detail detail = parseInput(data);

      //String message = "Detail Parseado: " + String(detail.hour) + " " + String(detail.minute) + " " + String(detail.amount);
      //Serial.println(message);

      processDetail(detail);
      data = "";
    }
    else
    {
      data += caracter;
    }
  }
  input = "";
}

void processInput()
{
  while (Serial.available())
  {
    char caracter = Serial.read();
    input += caracter;
  }
}

void sendDataToSerial()
{
  String data = String(sensorGrain.getDistance()) + "-" + String(sensorWater.getDistance());
  Serial.println(data);
  resolveInput();
}

void setup()
{
  Serial.begin(9600);

  sensorGrain.setup();
  sensorWater.setup();
  servo.setup();
  motordc.setup();
  //balance.setup();
}

// Test Sensors
// Get Data from PySerial
// Change flags, de ser necesario
// Send Data to PySerial

void loop()
{
  sensorGrain.loop();
  sensorWater.loop();
  servo.loop();
  motordc.loop();

  if ((millis() - startTime >= timeForDispend) && servo.smove == true)
  {
    servo.endDispend();
  }

  processInput();
  sendDataToSerial();

  delay(1000);
}
