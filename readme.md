# Code Repository for Raspi and Teensy 2.0

## How to use

The Raspi folder contains all files to be run on Raspberry pi. Ensure that dev/rfcomm is using the correct number upon connecting Teensy via bluetooth.

## Temperature Sensor
Reads temperature from Teensy DHT sensor and sends through serial1 to Raspi. Teensy will light 3 coloured LEDs depending on thresholds set in temperature.py.

### Commands
START_TEMP: Begins sending temperature

STOP_TEMP: Stops reading temperature

### Live Graph
To view a live updating temperature graph on another internet connected device, you need to first create an empty .csv file "data.csv" and run graph_client.py which will write the incoming data and timestamp to the .csv file.
Once this is running, execute live_graph.py (requires Matplotlib).  

## Sound Sensor
Uses analog sound level sensor and potentiometer to determine if sound thresholds have been exceeded. There are three levels: Normal, Medium and High. The thresholds can be set in sound_sensor.py.
### Commands

Needs to receieve _any_ message to begin transmitting data to Raspi.

If the thresholds are exceeded the corresponding LED will light up and send a message to Teensy. The idea is to subscribe to the MQTT topic s_level/phone on a mobile device to receive live updates if the noise level has passed the threshold.

## Light Show
Teensy will receive messages from MQTT to change between 4 light states: Yellow, Green, Red, and Light Show.

### Commands
CHANGE_STATE: Cycles to the next light state.
