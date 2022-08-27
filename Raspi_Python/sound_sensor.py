import serial
import time
import string
from datetime import datetime
import paho.mqtt.publish as publish

# reading and writing data from and to arduino serially

ser = serial.Serial("/dev/rfcomm0", 9600)
ser.write(str.encode('START'))

EC2_IP = "18.144.99.193"

while True:
        if ser.in_waiting > 0:
                rawserial = ser.readline()
                cookedserial = rawserial.decode('utf-8').strip('\r\n')
                dt = datetime.now()
                dt = dt.strftime('%X %x')
                print(cookedserial)
                if cookedserial[0] == "Y":
                        str = "Light Sound Detected at "
                        warning = str + dt
                        publish.single("s_level/phone",warning, hostname=EC2_IP)
                elif cookedserial[0] == "R":
                        str = "Loud Sound Detected at "
                        warning = str + dt
                        publish.single("s_level/phone",warning, hostname=EC2_IP)
                else:
                        pass