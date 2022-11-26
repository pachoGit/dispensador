#!/usr/bin/env python3

import serial, time, json
import requests as http
from time import process_time
from datetime import datetime

arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1, write_timeout=1)
time.sleep(2)

class Timer:
    def __init__(self, timeFinal):
        self.start = time.time()
        self.timeFinal = timeFinal

    def endTimer(self):
        if (time.time() - self.start >= self.timeFinal):
            self.start = time.time()
            return True
        return False

def clamp(n, smallest, largest):
    return max(smallest, min(n, largest))

def getDataFromServer():
    data = http.get('http://app.solucionesahora.com/dispensador/public/web/home/api')
    return data.text

def sendDataToServer(dataArduino):
    if (len(dataArduino) <= 0):
        return
    if (not dataArduino[0].isnumeric()):
        return
    route = 'http://app.solucionesahora.com/dispensador/public/web/home/apiMount?'
    distanceWaterEmpty = 12;
    distanceGrainEmpty = 12;

    data = dataArduino.split('-');
    grain = int(data[0])
    water = int(data[1])

    distanceGrain = clamp(grain, 0, distanceGrainEmpty);
    distanceWater = clamp(water, 0, distanceWaterEmpty);

    grain_porc = int(100.0 - (distanceGrain * 100.0) / distanceGrainEmpty);
    water_porc = int(100.0 - (distanceWater * 100.0) / distanceWaterEmpty);

    route = route +  'water_porc=' + str(water_porc) + '&'
    route = route +  'grain_proc=' + str(grain_porc)

    print('SEND DATA TO SERVER: ', route)
    http.get(route)

def sendDataToArduino(data):
    if (len(data) <= 0):
        return
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    data += "_" + current_time[0:5]
    print("SEND DATA TO ARDUINO: ", data)
    arduino.write(data.encode('utf-8'))

def getDataOfArduino():
    raw_data = arduino.readline();
    return raw_data.decode('utf-8')

def main():
    # while True:
        # data_server = getDataFromServer()
        # sendDataToServer(data_arduino);

        # sendDataToArduino("hola");
        # data = getDataOfArduino();
        # print("DATA FROM ARDUINO: ", data)
    data_arduino = ""
    data_server = ""
    timer1 = Timer(30)
    timer2 = Timer(2)

    while True:
        if timer1.endTimer():
            data_server = getDataFromServer()
            #print("DATA DEL SERVIDOR: ", data_server)
            if (len(data_arduino) >= 0):
                sendDataToServer(data_arduino)
            continue

        #if timer2.endTimer():
        if (len(data_server) >= 0):
            sendDataToArduino(data_server)
        data_arduino = getDataOfArduino()
        print("DATA DEL ARDUINO: ", data_arduino)
        time.sleep(2)

    arduino.close()

# getDataFromServer()
# sendDataToArduino()
# getDataFromArduino()
# sendDataFromServer()

if __name__ == '__main__':
    main()

