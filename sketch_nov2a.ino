#include <TimeLib.h>
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <HX711.h>

// Configurar con la fecha y hora actual
#define HOUR     21
#define MINUTE   45
#define SECOND   0
#define DAY      22
#define MONTH    11
#define YEAR     2022

// Maxima cantidad de configuraciones (hora y fecha de dispensado)
#define MAX_DETAIL 10

struct Detail
{
  int hour;

  int minute;

  int amount;

  int type; // 1 - Agua, 2 - Comida

  int isOcuped;
};

class ManageDetail
{
  public:

  Detail details[MAX_DETAIL];

  int idetail;

  public:

  ManageDetail()
  {
    idetail = 0;
  }

  void add(int hour, int minute, int amount, int type)
  {
    if (idetail >= MAX_DETAIL)
      return;
    details[idetail++] = {hour, minute, amount, type, 0};
    Serial.println("MANAGE DETAIL: add: Guardado");
  }

  void add(Detail detail)
  {
    if (idetail >= MAX_DETAIL)
      return;
    details[idetail++] = detail;
  }

  void size()
  {
    return idetail;
  }

  Detail get(int position)
  {
    return details[position];
  }

  void changeOcuped(int position)
  {
    details[position].isOcuped = 1;
  }

  void deleteByPosition(int position)
  {
    if (position < 0 || position > idetail)
      return;
    for (int i = position; i < idetail; i++)
      details[i] = details[i+1];
    if (details > 0)
      idetail--;
    else
      idetail = 0;
    Serial.println("MANAGE DETAIL: delete: Borrado");
  }

  void gdelete(int hour, int minute, int amount, int type)
  {
    for (int i = 0; i < idetail; i++)
    {
      if (details[i].hour == hour && details[i].minute == minute
          && details[i].type == type)
      {
        deleteByPosition(i);
        return;
      }
    }
  }

  int isTimeDispend(int hour, int minute)
  {
    if (idetail == 0)
      return -1;
    for (int i = 0; i < idetail; i++)
    {
      if (details[i].hour == hour && details[i].minute == minute)
      {
        return i;
      }
    }
    return -1;
  }

  void resolveFromInput(String input)
  {
    int hour, minute, amount, type;
    char command = input.charAt(0);
    input = input.substring(2);
    int ikey = 0;
    while (input.length() > 1)
    {
      String output = input.substring(0, input.indexOf(","));
      input = input.substring(input.indexOf(output) + output.length() + 1);

      if (ikey == 0) // Parse la hora
      {
        String shour = output.substring(0, output.indexOf(":"));
        String sminute = output.substring(output.indexOf(":")+1);
        hour = shour.toInt();
        minute = sminute.toInt();
      }
      if (ikey == 1)
      {
        amount = output.toInt();
      }
      if (ikey == 2)
      {
        type = output.toInt();
      }
      ikey++;
    }
    if (command == 'i')
      add(hour, minute, amount, type);
    if (command == 'd')
      gdelete(hour, minute, amount, type);
  }

};

ManageDetail gdetail;

class DriverMotorDC
{
  public:

  int enableA;  // Posicion en el arduino del enable A del driver
  int in1; // Posicion en el arduino de la entrada 1 del driver
  int in2; // Posicion en el arduino de la entrada 2 del driver

  bool smove;
  int timeDispend;

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
    if (smove == false)
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      delay(2000);
      analogWrite(enableA, 255);
    }

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

  void calibrateSetup()
  {
    driver.begin(pinDT, pinSCK);
    Serial.print("Lectura del valor del ADC:t ");
    Serial.println(driver.read());
    Serial.println("No ponga ningún objeto sobre la balanza");
    Serial.println("Destarando...");
    driver.set_scale();
    driver.tare(20);
    Serial.println("Coloque un peso conocido");
  }

  void calibrateLoop()
  {
    Serial.print("Valor de lectura: ");
    Serial.println(driver.get_value(10),0);
    delay(100);
  }

  void setup()
  {
    Serial.begin(9600);
    driver.begin(pinDT, pinSCK);
    Serial.print("Lectura del valor del ADC:  ");
    Serial.println(driver.read());
    Serial.println("No ponga ningun  objeto sobre la balanza");
    Serial.println("Destarando...");
    Serial.println("...");
    driver.set_scale(441152.95); // Establecemos la escala
    driver.tare(20);  //El peso actual es considerado Tara.

    Serial.println("Listo para pesar");
  }

  void loop()
  {
    Serial.print("Peso: ");
    Serial.print(driver.get_units(20),3);
    Serial.println(" kg");
    delay(500);
  }

};

class SensorDistance
{
  public:

  int pinTrigger;

  int pinEcho;

  long time;

  long distance;

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
    return (int) distance;
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

static const char *nameWifi = "Nerita3";
static const char *password = "Nerita1234t";
static const char *server = "app.solucionesahora.com";
SoftwareSerial SoftSerial = SoftwareSerial(10, 11);

String keyRequest[3] = {"time=", "amount=", "type="};

class ModuloWifi
{
  public:

  int baudRate;

  String response;

  // Para el WIFI
  int status;

  WiFiEspClient client;

  public:

  // Constructor para las pruebas de los comandos AT del modulo
  ModuloWifi(int _baudRate)
  {
    baudRate = _baudRate;
    response = "";
    status = WL_IDLE_STATUS;
  }

  void printWifiStatus()
  {
    // print the SSID of the network you're attached to
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }

  void sendServer(String route)
  {
    client.stop();
    if (client.connect(server, 80))
    {
      Serial.println("Conectando al servidor");
      route.replace('\n', ' ');
      route = route.substring(0, route.indexOf(' '));
      route.trim();

      String buffer = "GET " + route + " HTTP/1.1";
      buffer.trim();

      Serial.println(buffer);
      client.println(buffer);
      client.println(F("Host: app.solucionesahora.com"));
      client.println(F("Connection: close"));
      client.println();
    }

  }

  // Envia una solicitud para ingresar un nueva hora y porcion de un tipo (comida o agua)
  // @param String input - Formato "tiempo,cantidad,tipo"
  //                       Donde: tiempo -> 23:21
  //                              cantidad -> 513
  //                              tipo -> 1 | 2
  void sendInsert(String input)
  {
    String route = "/dispensador/public/web/home/api?";

    int ikey = 0;
    while (input.length() > 1)
    {
      String output = input.substring(0, input.indexOf(","));
      input = input.substring(input.indexOf(output) + output.length() + 1);
      output = keyRequest[ikey++] + output + "&";
      route += output;
    }
    sendServer(route);
  }

  void sendDelete(String input)
  {
    String route = "/dispensador/public/web/home/apiDelete?";

    int ikey = 0;
    while (input.length() > 1)
    {
      String output = input.substring(0, input.indexOf(","));
      input = input.substring(input.indexOf(output) + output.length() + 1);
      output = keyRequest[ikey++] + output + "&";
      route += output;
    }
    sendServer(route);
  }

  // Enviar el porcetanje de comida de los contenedores
  void sendWaterAndGrain(int distanceWater, int distanceGrain)
  {
    String route = "/dispensador/public/web/home/apiMount?";

    // La distancia que marcan los sensores cuando el contentedor esta vacio
    int distanceWaterEmpty = 13;
    int distanceGrainEmpty = 13;

    // Normalizamos los valores
    distanceWater = constrain(distanceWater, 0, distanceWaterEmpty);
    distanceGrain = constrain(distanceGrain, 0, distanceGrainEmpty);

    // Cuanto mas distancia mas vacio esta el contenedor
    int water_porc = 100.f - (distanceWater * 100.f) / distanceWaterEmpty;
    int grain_porc = 100.f - (distanceGrain * 100.f) / distanceGrainEmpty;

    route += "water_porc=" + String(water_porc) + "&";
    route += "grain_porc=" + String(grain_porc);

    sendServer(route);
  }

  void httpRequest(String input)
  {
    if (input.charAt(0) == 'i')
    {
      input = input.substring(2);
      sendInsert(input);
    }
    else if (input.charAt(0) == 'd')
    {
      input = input.substring(2);
      sendDelete(input);
    }
    else
    {
      Serial.println("Mal comando para enviar al servidor");
    }
  }

  // Setup para las pruebas de los comandos AT del modulo
  void setup()
  {
    SoftSerial.begin(baudRate);
    SoftSerial.setTimeout(5000);
    WiFi.init(&SoftSerial);

    // check for the presence of the shield
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi escudo no esta presente");
      // don't continue
      Serial.println("Reiniciando");
      //resetFunc();  //call reset
    }

    // attempt to connect to WiFi network
    while ( status != WL_CONNECTED) {
      Serial.print("Intentando conectar a WPA SSID: ");
      Serial.println(nameWifi);
      // Connect to WPA/WPA2 network
      status = WiFi.begin(nameWifi, password);
    }
    Serial.println("Estas conectado a la red :D");

    printWifiStatus();
  }

  void loop(String input)
  {
    if (input.length() <= 1)
      return;
    while (client.connected())
    {
      while (client.available())
      {
        char c = client.read();
        response += c;
      }
    }
    client.stop();
    if (response.length() > 1)
    {
      Serial.print("Respuesta: ");
      Serial.println(response);
      if (response.indexOf("OK") != -1)
      {
          gdetail.resolveFromInput(input);
      }
      response = "";
    }
  }

};

class ServoMotor
{
  public:

  int pinAttach;

  Servo driver;

  bool smove;

  bool ocuped;

  long timeDispend;

  long initTime;

  public:

  ServoMotor(int _pinAttach)
  {
    pinAttach = _pinAttach;
    smove = false;
    ocuped = false;
    timeDispend = 2000L;
    initTime = 0;
  }

  void setup()
  {
    driver.attach(pinAttach);
    driver.write(0);
    delay(1000);
  }

  void loop()
  {
    if (smove == true && ocuped == true)
    {
      driver.write(0);
      delay(1000);
      driver.write(90);
      delay(1000);
      driver.write(180);
      delay(1000);
    }
  }
};

//Balance balance;
SensorDistance sensorGrain(13, 12);
SensorDistance sensorWater(2, 4);
ServoMotor servo(9);
int rate = 9600;
DriverMotorDC driverMotor;
ModuloWifi modWifi(rate);

void printDateTime()
{
  Serial.print("Hora registrado: ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.println(year());

}

long lastConnectionTime = 0;
long timeForSendPorcentage = 20000L;

void sendPorcentage()
{
  modWifi.sendWaterAndGrain(sensorWater.getDistance(), sensorGrain.getDistance());
  //modWifi.sendWaterAndGrain(sensorWater.getDistance(), sensorGrain.getDistance());
  lastConnectionTime = millis();
}

void setup()
{

  Serial.begin(rate);
  setTime(HOUR, MINUTE, SECOND, DAY, MONTH, YEAR);
  printDateTime();

  //balance.calibrateSetup();
  //balance.setup();
  sensorGrain.setup();
  sensorWater.setup();
  //servo.smove = true;
  servo.setup();
  driverMotor.setup();

  //gdetail.add(21, 45, 100, 1);

  modWifi.setup();

}

void loop()
{
  String input = "";
  while (Serial.available())
  {
    char car = Serial.read();
    input += car;
  }

  /* Serial.print("Input: "); */
  /* Serial.println(input); */
  if (input.length() > 1)
    modWifi.httpRequest(input);
  modWifi.loop(input);

  //balance.calibrateLoop();
  //balance.loop();
  sensorGrain.loop();
  /* sensorGrain.print(); */
  sensorWater.loop();
  //sensorWater.print();
  servo.loop(); // 25 seconds 1 kg
  driverMotor.loop(); // 25 seconds 100ml

  // Comprobar si es hora de dispensar
  int ginfo = gdetail.isTimeDispend(hour(), minute());
  if (ginfo != -1)
  {
    Detail detail = gdetail.get(ginfo);
    if (detail.type == 1) // Agua
    {
      if (detail.isOcuped == 0)
      {
        int waterTime = (25000 * detail.amount) / 100;
        driverMotor.timeDispend = waterTime;
        driverMotor.smove = true;
        //detail.isOcuped = 1;
        gdetail.changeOcuped(ginfo);
        Serial.println("Comenzo a dispensar el agua...");
      }
    }
    if (detail.type == 2) // Comida
    {
      int grainTime = (25000 * detail.amount)  / 1000;
      servo.smove = true;
      if (servo.ocuped == false && detail.isOcuped == 0)
      {
        servo.timeDispend = grainTime;
        servo.ocuped = true;
        servo.initTime = millis();
        Serial.print("Comenzo a dispesar comida en: ");
        Serial.print(millis());
        Serial.print(" Hasta: ");
        Serial.println(grainTime);
      }
      else
      {
        Serial.print("Dispensando comida: ");
        Serial.println(millis() - servo.initTime);
        if (millis() - servo.initTime > servo.timeDispend)
        {
          servo.ocuped = false;
          servo.smove = false;
          Serial.println("Termino dispensar comida");
        }
      }
      gdetail.changeOcuped(ginfo);
      //detail.isOcuped = 1;
    }
  }

  if (millis() - lastConnectionTime > timeForSendPorcentage)
  {
    sendPorcentage();
  }

  delay(1000);
}
