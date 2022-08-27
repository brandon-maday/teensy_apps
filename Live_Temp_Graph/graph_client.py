import paho.mqtt.client as mqtt
import csv
import time
from datetime import datetime

def on_connect(client, userdata, flags, rc): # func for making connection
	print("Connected to MQTT")
	print("Connection returned result: " + str(rc) )
	client.subscribe("temp/graph")


def on_message(client, userdata, msg): # Func for Sending msg
	
	variable = float(bytes.decode(msg.payload))	
	temperature = variable

	with open('data.csv', 'a') as csv_file:
		csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
		current_time = datetime.now()
		current_time = current_time.strftime('%X')
		
		info = {
			"current_time": current_time,
			"temperature": temperature
		}

		csv_writer.writerow(info)

		#UNCOMMENT BELOW IF WANT TO PRINT TO CONSOLE
		print(current_time, temperature)


fieldnames = ["current_time","temperature"]

with open('data.csv', 'w') as csv_file:
	csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
	csv_writer.writeheader()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("18.144.99.193", 1883, 60)

client.loop_forever()