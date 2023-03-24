#define BLYNK_TEMPLATE_ID "TMPLrSAsWDDB"
#define BLYNK_TEMPLATE_NAME "Water meter template"
#define BLYNK_AUTH_TOKEN "PRUqyzguLZ8Y1olTZBAfRtMihLyI52ZF"

// Comment this out to disable prints and save space
//#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_FIRMWARE_VERSION        "0.1.2"

const int ledPin =  5; // the LED pin number connected
char auth[] = BLYNK_AUTH_TOKEN;
int powerPin;
int waterPin;
int counter = 0;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "RIO";
char pass[] = "research!";

BlynkTimer timer;
// connects to the pump off switch
BLYNK_WRITE(V0) // Executes when the value of virtual pin 0 changes
{
int virtual_pin_value = param.asInt();  
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(5,HIGH);  // Set digital pin  HIGH    
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(5,LOW);  // Set digital pin LOW        
  }
}
//connects to the pump off switch
BLYNK_WRITE(V1) // Executes when the value of virtual pin 1 changes
{
int virtual_pin_value = param.asInt();  
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(4,LOW);  // Set digital pin  HIGH   
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(4,HIGH);  // Set digital pin LOW           
  }
}
void myTimerEvent()
{
  Blynk.virtualWrite(V3, waterPin);
  Blynk.virtualWrite(V2, millis() /1000 );
}



BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V1);  // will cause BLYNK_WRITE(V0) to be executed
  Blynk.syncVirtual(V0);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(5, OUTPUT);   
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}
void loop()
{
  waterPin = touchRead(13);
  if (waterPin < 70){
    counter ++;
  }
  Blynk.run();
  timer.run();
 
}
