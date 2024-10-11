#include "DHT.h"
//#include <SoftwareSerial.h>

#define DHTPIN 21      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

#define LEDPIN 11
#define BUZZER 13
#define SOIL_PIN = 12;
#define LIGHTPIN A9
int counter = 0;

DHT dht(DHTPIN, DHTTYPE);

// Teensy 5V <--> HC-05 Vcc
// Teensy Ground <--> HC-05 GND
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx
//SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);
//String str="";
int BOX_ID = 0;


//warnings
float temperature_warning=999;
float humidity_warning=999
int light_warning=999;
int soil_warning=999;
bool buzzer = false;
bool led = false;


void setup() {
  //add some setup for encryption
  // Setup serial for monitor
  Serial.begin(9600); 

  // Setup DHT Sensor
  pinMode(DHTPIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LIGHTPIN, INPUT_PULLUP);//check
  dht.begin();

  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
  
}

void loop() {

  String input=Serial1.readString().substring(1);//what does the 1 do?
  //input would be like code|optional command|counter
  int code =...;
  String cmd=...;
  int input_counter=...;
  //extract counter and convert to integer, if you can't ignore
  //compare 
  if counter< input_counter{
    counter= input_counter;

    switch(case_code){//we dont want breaks as we always want to run the default then break...there is another way to do this
      case 1000:
        //change key... should have some timeout in the while, like or epoch>10000 etc
        while (case_code==1000){
          //send ready for key
          //look for input
          //if input valid change key
          case_code=1001
          while (case_code==1001){
            //send confirmation of key change
            //if acknowledged case_code=0000;
          }
        }
        case_code=0000;
        //break; 

      //change sensor warnings
      //it would be good if this canged if we want to care if we are above or below, as well as how to notify, you can do that later if you want
      case 9000:
        //temperature warning
        //convert cmd to float/int
        temperature_warning=cmd;
        case_code=0000;
        //break;
      case 9001:
        //humidity warning
        //convert cmd to float/int
        humidity_warning=cmd;
        case_code=0000;
        //break;
      case 9002:
        //soil warning
        //convert cmd to float/int
        soil_warning=cmd;
        case_code=0000;
        //break;
      case 9003:
        //light warning
        //convert cmd to float/int
        light_warning=cmd;
        case_code=0000;
        //break;

      default:
        //
        //record sensor values
        //if sensor value is greater than warning, do something
        //send sensor readings
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        int soil = analogRead(SOIL_PIN);
        int light = analogRead(LIGHTPIN);

        if ((temperature_warning<=temperature)||(humidity_warning<=humidity)||(soil_warning<=soil)||(light_warning<=light)){
          //turn on buzzer
        }
        else{
          //turn off buzzer
        }
        //Serial1 is the BT device
        Serial1.print(BOX_ID);
        Serial1.print("|");
        Serial1.print(t);
        Serial1.print("|");
        Serial1.print(h);
        Serial1.print("|");
        Serial1.print(soil);
        Serial1.print("|");
        Serial1.print(light);
        Serial1.print("|");
        Serial1.print(counter);

        
        counter=counter+1;
        case_code=0000;
        break;
    }
  }
}