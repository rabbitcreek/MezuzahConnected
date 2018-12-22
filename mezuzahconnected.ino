/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - ESP32 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <OneWire.h>
#include <DallasTemperature.h>
// pin driven high to turn off power
#define donePin 33
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//temp measure pin
#define ONE_WIRE_BUS 15
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);




 float Celcius=0;
 float Fahrenheit=0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "place blynk credential here";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your wifi name";
char pass[] = "wifi password";
 
  
  
  BlynkTimer timer_temp;
  //temp function
  void myTempEvent(){
  sensors.requestTemperatures(); 
  delay(20);
  Celcius=sensors.getTempCByIndex(0);
  delay(20);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  delay(20);
   Serial.print(" C  ");
  Serial.print(Celcius);
  Serial.print(" F  ");
  Serial.println(Fahrenheit); 
   Blynk.virtualWrite(V6,Fahrenheit);
   delay(1000);
  //this turns off power 
    while (1) {
    digitalWrite(donePin, HIGH);
    delay(1);
    digitalWrite(donePin, LOW);
    delay(1);
   
  }
 
  }
void setup()
{
  // Debug console
  Serial.begin(115200);
  sensors.begin();
  pinMode(donePin, OUTPUT);
  digitalWrite(donePin, LOW);
  sensors.requestTemperatures(); 
  delay(20);
  Celcius=sensors.getTempCByIndex(0);
  delay(20);
  Fahrenheit=sensors.toFahrenheit(Celcius);
  delay(20);
 delay(1000);
 //set up blynk timer operation 
 
  Blynk.begin(auth, ssid, pass);
   timer_temp.setInterval(5000L, myTempEvent);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer_temp.run();
  
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

