//temperature and humidity sensor
#include "DHT.h"
#define DHTPIN 21      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//various pins
#define LEDPIN 11
#define BUZZER 14
#define SOIL_PIN 13 //A8
#define LIGHTPIN 20//A9


//bluetooth pins
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

//misc constants
const int BOX_ID = 0;

//global variables
//int aes_key;

//t 999, h 999, s 0, l 999
String key;
int COUNTER = 0;
float temperature_warning=9999;
float humidity_warning=9999;
int light_warning=999; //0 is high light
int soil_warning=0;//0 is low moisture
bool buzzer = false;
bool led = false;
int out_counter=0;
String input;


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
  temperature_warning=9999;
  humidity_warning=9999;
  light_warning=999; //0 is high light
  soil_warning=10;//0 is low moisture
}

void loop() {

  delay(2000);
  int code=0000;
  int cmd=0;
  int counter=0;
  //fix all reads to have this, otherwise we read junk in
  if (Serial1.available()>0){
    input=Serial1.readString().substring(1);//I don't kow wy we always have a weird char out the front
    Serial.println(input);
    //Serial.print(Serial1.read(), HEX);//readString may be bad
    //input expected like code;cmd;counter;
    //where they are all integers
    // 123;;12;, would result in 123, 0, 12
    int inputs[3], r=0, t=0;

      for (int i=0; i < input.length(); i++)
      { 
        if(input.charAt(i) == ';') 
          { 
            inputs[t] = input.substring(r, i).toInt(); 
            r=(i+1); 
            t++; 
          }
      }
    code =inputs[0];
    cmd=inputs[1];
    counter=inputs[2];

    COUNTER = counter;
    switch(code){//we dont want breaks as we always want to run the default then break...there is another way to do this
      //change key
      case 1000:
        //change key... should have some timeout in the while, like or epoch>10000 etc
        while (code==1000){
          //send ready for key
          Serial1.println("ready for key");
          //look for input
          if (Serial1.available()>0){
            key = Serial1.readString().substring(1);
          }
          //if input valid change key
          if (key.length() == 1){
            code=1001;
            while (code==1001){
              //send confirmation of key change
              String acknowledgement;
              Serial1.print("key changed to:");
              Serial1.println(key);
              if (Serial1.available()>0){
                acknowledgement = Serial1.readString().substring(1);
              }
              if (acknowledgement == "acknowledged"){
                code=0000;
                }
            }
          }
          
        }
        code=0000;
        break;

      //change sensor warnings
      //it would be good if this canged if we want to care if we are above or below, as well as how to notify, you can do that later if you want
      case 9000:
        //temperature warning
        //convert cmd to float/int
        temperature_warning=cmd;
        code=0000;
        Serial.print("temperature warning changed to ");
        Serial.println(temperature_warning);
        break;
      case 9001:
        //humidity warning
        //convert cmd to float/int
        humidity_warning=cmd;
        code=0000;
        break;
      case 9002:
        //soil warning
        //convert cmd to float/int
        soil_warning=cmd;
        code=0000;
        break;
      case 9003:
        //light warning
        //convert cmd to float/int
        light_warning=cmd;
        code=0000;
        break;
    }
  }
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int soil = analogRead(SOIL_PIN);
  int light = analogRead(LIGHTPIN);

  //Serial.print(temperature);
  //Serial1 is the BT device
  Serial1.print(BOX_ID);
  Serial1.print(";");
  Serial1.print(temperature);
  Serial1.print(";");
  Serial1.print(humidity);
  Serial1.print(";");
  Serial1.print(soil);
  Serial1.print(";");
  Serial1.print(light);
  Serial1.print(";");
  out_counter=out_counter+1;
  Serial1.println(out_counter);

  if ((temperature_warning<temperature)||(humidity_warning<humidity)||(soil_warning>soil)||(light_warning<light)){//((temperature_warning>=temperature)||(humidity_warning>=humidity)||(soil_warning<=soil)||(light_warning<=light)){
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    if(temperature_warning<temperature){
      Serial.println("temp");
      Serial.println(temperature_warning);
      Serial.println(temperature);
    }
    if(humidity_warning<humidity){
      Serial.println("humid");
      Serial.println(humidity_warning);
      Serial.println(humidity);
    }
    if(soil_warning>soil){
      Serial.println("soil");
      Serial.println(soil_warning);
      Serial.println(soil);
    }
    if(light_warning<light){
      Serial.println("light");
      Serial.println(light_warning);
      Serial.println(light);

    }

  }
  else{
    digitalWrite(BUZZER, LOW);
  }

}