###this file will look at the MQTT topic for warning values then send those to the relevant teensy
import paho.mqtt.client as mqtt
import serial
import string

from IP import IP
def on_connect(client, userdata, flags, rc): #func for making connection
    print("connected to MQQT")
    print(f"Connection result: {str(rc)}")
          
    client.subscribe("test/teensy1/input")
def on_message(client, userdata, msg): #func for sending message
    print(msg.topic+": "+(msg.payload).decode())#str.decode adds a b for bytes, this looks better but doesnt have as much info i guess
    
    #fix the space, add counter
    cmd=str.encode(" "+msg.payload.decode()) #it keeps cutting of first letter so we add soemthign unimportant to cutt off
    ser=serial.Serial("COM4",9600)
    #"/dev/rfcomm0"
    #"COM4"
    ser.write(cmd)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

#IP="3.27.30.149"#AWS instance IP or "localhost"
client.connect(IP,1883,60)

client.loop_forever()
