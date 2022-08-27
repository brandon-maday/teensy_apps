import serial
import time
import string
import paho.mqtt.publish as publish

# reading and writing data from and to arduino serially

ser = serial.Serial("/dev/rfcomm0", 9600)
ser.write(str.encode('START'))

EC2_IP = "18.144.99.193"

while True:
        if ser.in_waiting > 0:
                rawserial = ser.readline()
                cookedserial = rawserial.decode('utf-8').strip('\r\n')
                print(cookedserial)
                if cookedserial == "CHANGE":
                        publish.single("light_state","CHANGE_STATE", hostname=EC2_IP)
                elif cookedserial == "STOP":
                        publish.single("light_state","STOP", hostname=EC2_IP)
                else:
                        pass