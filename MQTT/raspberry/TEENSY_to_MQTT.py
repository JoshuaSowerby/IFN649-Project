"""
TEENSY_to_MQTT
look at TEENSY serial output, if counter is valid send to MQTT
this should handle key change as it doesnt need to watch MQTT topics
last_key_change = X
if in_counter+1000>last_key_change: change key
"""
import sys
sys.path.append(r'.\secrets')
from IP import IP

import paho.mqtt.publish as publish
import serial 
from time import time
"""
replace "COM5" with "/dev/rfcomm0"
"""
boxid=1#import this

ser = serial.Serial("/dev/rfcomm0", 9600)
#ser.write(str.encode('Start\r\n'))#I don't think I need this
last_counter=0
change_key_counter=1000
while True:
    if ser.in_waiting > 0:
        rawserial = ser.readline()
        cookedserial = rawserial.decode('utf-8').strip('\r\n')
        #decode using encryption key
        print(cookedserial)
        #if cookedserial is sensor values
        #box;temp;humid;soil;light;counter;
        #assume sensor value
        if cookedserial.count(';')==6:
            inputs=cookedserial.split(';')
            current_counter=inputs[-2]
            if False:#current_counter>change_key_counter:
                change_key_counter=current_counter+1000
                """
                enter chagne key mode etc
                """
                #pass
                raise NotImplementedError
            if True:#:current_counter>last_counter:
                last_counter=current_counter
                #box;temp;humid;soil;light;time
                print(inputs)
                publish.single(f"{boxid}/outputs", f"{inputs[0]};{inputs[1]};{inputs[2]};{inputs[3]};{inputs[4]};{time.time()}", hostname=IP)

        '''#implement key switching
        #something like if counter mod 100, initiate key switching
        #the key should be stored in secrets nd read each time so other rpi scripts can use it
        # https://docs.arduino.cc/libraries/aeslib/ 
        '''
#publish.single("ifn649", "Hello World", hostname="3.27.30.149")#IP or "localhost", would be better to import this
#print("Done")