import paho.mqtt.client as mqtt
from IP import IP
def on_connect(client, userdata, flags, rc): #func for making connection
    print("connected to MQQT")
    print(f"Connection result: {str(rc)}")
          
    client.subscribe("test/teensy1/output")
def on_message(client, userdata, msg): #func for sending message
    print(msg.topic+": "+(msg.payload).decode())#str.decode adds a b for bytes, this looks better but doesnt have as much info i guess
    """add this here or in the input...
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

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

#IP="3.27.30.149"#AWS instance IP or "localhost"
client.connect(IP,1883,60)

client.loop_forever()