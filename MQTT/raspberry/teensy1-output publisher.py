import paho.mqtt.publish as publish
from IP import IP
import serial 

ser = serial.Serial("COM5", 9600)
#/dev/rfcomm0
#COM(4,5)
ser.write(str.encode('Start\r\n'))

while True:
    
    if ser.in_waiting > 0:
        rawserial = ser.readline()
        cookedserial = rawserial.decode('utf-8').strip('\r\n')
        #if cookedserial is sensor values
        publish.single("test/teensy1/output", cookedserial, hostname=IP)#IP or "localhost", would be better to import this
        '''#implement key switching
        #something like if counter mod 100, initiate key switching
        #the key should be stored in secrets nd read each time so other rpi scripts can use it 
        '''
#publish.single("ifn649", "Hello World", hostname="3.27.30.149")#IP or "localhost", would be better to import this
#print("Done")