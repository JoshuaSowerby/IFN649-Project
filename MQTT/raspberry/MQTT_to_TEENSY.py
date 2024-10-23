'''
MQTT_to_TEENSY
look at MQTT, if MQTT has warning change, send to teensy (using shared counter?)
potentially look for confirmation that it as been recieved, 

TODO, implement count check and encryption
'''
import sys
sys.path.append(r'.\secrets')
from IP import IP
import paho.mqtt.client as mqtt
import serial
"""
replace "COM5" or COM4 with "/dev/rfcomm0"
"""
boxid=1#import
def on_connect(client, userdata, flags, rc): #func for making connection
    print("connected to MQQT")
    print(f"Connection result: {str(rc)}")
          
    client.subscribe(f"{boxid}/input")#rename
def on_message(client, userdata, msg): #func for sending message
    print(msg.topic+": "+(msg.payload).decode())#str.decode adds a b for bytes, this looks better but doesnt have as much info i guess
    cmd_deocded=(msg.payload).decode()
    #code;cmd;
    if cmd_deocded.count(';')==2:#there should be more checks here, but it doesn't really matter
        cmd_deocded=msg+f'{counter};'#import counter
    #fix the space, add counter
    cmd=str.encode(" "+msg.payload.decode()) #it keeps cutting of first letter so we add soemthign unimportant to cutt off
    #add encryption
    ser=serial.Serial("/dev/rfcomm0",9600)#!!!change to /dev etc for rpi, this is only for windows testing
    #"/dev/rfcomm0"
    #"COM4"
    ser.write(cmd)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(IP,1883,60)

client.loop_forever()
