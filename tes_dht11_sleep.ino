#include "DHT.h"

#define DHTPIN 4 // sambungkan ke pin digital board
#define DHTTYPE DHT11 // untuk dht11

#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 3 //Pin we are going to use to wake up the Arduino

DHT dht(DHTPIN, DHTTYPE); // objek sensor dht

void setup() {
  Serial.begin(115200);//Start Serial Comunication
  dht.begin();
  pinMode(LED_BUILTIN,OUTPUT);//We use the led on pin 13 to indecate when Arduino is A sleep
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
  digitalWrite(LED_BUILTIN,HIGH);//turning LED on
}

void loop() {
  delay(100);
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  
  Serial.print("Temperature = ");
  Serial.print(Temp);
  Serial.print("*C,    Humidity = ");
  Serial.print(RH);
  Serial.println("%");

  delay(3000);//wait 3 seconds before going to sleep
  menuju_tidur();
}

void menuju_tidur(){
    sleep_enable();//Enabling sleep mode
    attachInterrupt(0, bangun, LOW);//attaching a interrupt to pin d2
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
    digitalWrite(LED_BUILTIN,LOW);//turning LED off
    delay(3000); //wait a second to allow the led to be turned off before going to sleep
    sleep_cpu();//activating sleep mode
    Serial.println("baru saja bangun!");//next line of code executed after the interrupt 
    digitalWrite(LED_BUILTIN,HIGH);//turning LED on
  }

void bangun(){
  Serial.println("Interrrupt dinyalakan, mode tidur on");//Print message to serial monitor
   sleep_disable();//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}
