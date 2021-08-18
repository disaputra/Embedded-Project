// sd card
#include <SD.h>
#include <SPI.h>

// watchdog time
#include <avr/wdt.h>

// dht
#include "DHT.h"

#define DHTPIN 2 // sambungkan ke pin digital board
#define DHTTYPE DHT11 // untuk dht11
DHT dht(DHTPIN, DHTTYPE); // objek sensor dht


File myFile; // objek sd card

int pinCS = 53; // Pin digital 53 SS mega

void setup() {
    
  Serial.begin(9600);
  Serial.println("Setup started :");
  dht.begin();
  
  delay(2000);
  wdt_enable(WDTO_4S); // enable watchdog time 4 detik
  
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
    wdt_disable(); // apabila sd card siap, disable watchdog time
  } else
  {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");

    wdt_reset(); // melakukan restard via watchdog time
    while(1){} // terus berulang selama 1 ms
    return;
  } 
}
void loop() {
  delay(1000);
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  
  // Create/Open file 
  myFile = SD.open("DHT11Log.txt", FILE_WRITE); // membuka file untuk ditulis
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Temperature = ");
    Serial.print(Temp);
    Serial.print("°C,    Humidity = ");
    Serial.print(RH);
    Serial.println("%");
    // Write data to SD card file (DHT11Log.txt)
    //dataFile.print(line++);
    myFile.print("Temperature = ");
    myFile.print(Temp);
    myFile.print("°C,    Humidity = ");
    myFile.print(RH);
    myFile.println("%");
    myFile.close();
    
    wdt_disable(); // apabila sd card siap, disable watchdog time
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening file");
    wdt_reset(); // melakukan restart via watchdog time
    delay(1);
    SD.begin();
  }

  // Reading the file
  myFile = SD.open("DHT11Log.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
    
   }
    myFile.close();
  }
  else {
    Serial.println("error opening file");
    wdt_reset(); // melakukan restard via watchdog time
    delay(1);
    SD.begin();
  }
}
