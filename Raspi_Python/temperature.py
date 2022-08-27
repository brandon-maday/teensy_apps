import serial
import time
import string
import paho.mqtt.publish as publish

# Receives input on serial from Teensy, and will push messages based off the temperature levels
# Change the raw_tempiables 'MEDIUM' and 'HIGH' to set temperature thresholds

ser = serial.Serial("/dev/rfcomm0", 9600)
ser.write(str.encode('START\r\n'))
raw_temp = ""
EC2_IP = "18.144.99.193"
HIGH = 27
MEDIUM = 26

while True:
        if ser.in_waiting > 0:
                rawserial = ser.readline()
                cookedserial = rawserial.decode('utf-8').strip('\r\n')
                raw_temp = cookedserial[13:15]
                temp = cookedserial[0:18]
                x = int(raw_temp)
                temp_float = float(cookedserial[13:18])

                if x >= MEDIUM:
                        medium_loop = True
                        publish.single("temp/teensy","MEDIUM_TEMP",hostname=EC2_IP)
                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                        while medium_loop:
                                rawserial = ser.readline()
                                cookedserial = rawserial.decode('utf-8').strip('\r\n')
                                raw_temp = cookedserial[13:15]
                                temp = cookedserial[0:19]
                                x = int(raw_temp)
                                temp_float = float(cookedserial[13:18])
                                if x < MEDIUM:
                                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                                        publish.single("temp/teensy","NORMAL_TEMP",hostname=EC2_IP)
                                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                                        print(cookedserial)
                                        medium_loop = False

                                elif x >= HIGH:
                                        high_loop = True
                                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                                        publish.single("temp/teensy","HIGH_TEMP",hostname=EC2_IP)
                                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                                        while high_loop:
                                                rawserial = ser.readline()
                                                cookedserial = rawserial.decode('utf-8').strip('\r\n')
                                                raw_temp = cookedserial[13:15]
                                                temp = cookedserial[0:19]
                                                x = int(raw_temp)
                                                temp_float = float(cookedserial[13:18])
                                                if x < HIGH:
                                                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                                                        publish.single("temp/teensy","MEDIUM_TEMP",hostname=EC2_IP)
                                                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                                                        print(cookedserial)
                                                        high_loop = False
                                                        if x < MEDIUM:
                                                                medium_loop = False
                                                else:
                                                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                                                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                                                        print(cookedserial)
                                else:
                                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                                        print(cookedserial)

                else:
                        publish.single("temp/phone/out",temp,hostname=EC2_IP)
                        publish.single("temp/graph",temp_float,hostname=EC2_IP)
                        print(cookedserial)
