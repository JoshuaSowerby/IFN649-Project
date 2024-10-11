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
        publish.single("test/teensy1/output", cookedserial, hostname=IP)#IP or "localhost", would be better to import this
        """add this here or in one fo the clients
        dynamodb = boto3.resource('dynamodb', region_name='ap-southeast-2')
        table = dynamodb.Table('iotDB')
        
        data = {
        "box": 1999,
        "timestamp": "1999-09-15T00:00:00Z",
        "temp": 1,
        "light": 1,
        "soil": 1}
        
        response = table.put_item(
            Item=data
        )
        print("PutItem succeeded:")
        print(response)
        """
        """
        #print(cookedserial)
        if('10' in cookedserial):
            ser.write(str.encode('BUZZER_ON'))
            #time.sleep(0.5) 
        else:
            ser.write(str.encode('BUZZER_OFF'))
        """
#publish.single("ifn649", "Hello World", hostname="3.27.30.149")#IP or "localhost", would be better to import this
#print("Done")