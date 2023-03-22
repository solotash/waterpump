#define BLYNK_TEMPLATE_ID "TMPLrSAsWDDB"
#define BLYNK_TEMPLATE_NAME "Water meter template"
#define BLYNK_AUTH_TOKEN "PRUqyzguLZ8Y1olTZBAfRtMihLyI52ZF"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


const int ledPin =  5; // the LED pin number connected
char auth[] = BLYNK_AUTH_TOKEN;
double counter = 0;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "RIO";
char pass[] = "research!";

BlynkTimer timer;

BLYNK_WRITE(V1) // Executes when the value of virtual pin 1 changes
{
int virtual_pin_value = param.asInt();  
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(5,LOW);  // Set digital pin  HIGH
    counter = 0; 
     Blynk.virtualWrite(V3, counter); 
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(5,HIGH);  // Set digital pin LOW   
        
  }
}
BLYNK_WRITE(V3) // Executes when the value of virtual pin 1 changes
{
int virtual_pin_value = param.asInt();  
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(4,LOW);  // Set digital pin  HIGH
    counter = 0; 
     Blynk.virtualWrite(V3, counter); 
  }
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(4,HIGH);  // Set digital pin LOW   
        
  }
}
void myTimerEvent()
{
  if (digitalRead(5)==0){
    counter+=1;
    Blynk.virtualWrite(V3, counter/60);       
  }
  Blynk.virtualWrite(V2, millis() /1000 );
}



BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V1);  // will cause BLYNK_WRITE(V0) to be executed
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
  
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}