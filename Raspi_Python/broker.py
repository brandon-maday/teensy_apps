import serial
import time
import string
import paho.mqtt.client as mqtt
from datetime import datetime

# reading and writing data from and to arduino serially

EC2_IP = "18.144.99.193"
RF_COMM = "/dev/rfcomm0"

def on_connect(client, userdata, flags, rc): # func for making connection and subscribing to topics
        print("You have connected to MQTT!")
        print("Connect returned the result....: " + str(rc) + "\n")
        client.subscribe("temp/teensy")
        client.subscribe("temp/phone")
        client.subscribe("light_state")
        client.subscribe("s_level/alarm")

def on_message(client, userdata, msg): # func for sending message
        ser.write(msg.payload)
        message_in = msg.payload
        message_in = message_in.decode()
        topic_in = msg.topic

        dt = datetime.now()
        if topic_in[-1] == "e":
                print("received: " + message_in + " at " + dt.strftime('%X %x') + " from iPhone")
        else:
                print("received: " + message_in + " at " + dt.strftime('%X %x'))

ser = serial.Serial(RF_COMM, 9600)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(EC2_IP,1883,60)

client.loop_forever()
