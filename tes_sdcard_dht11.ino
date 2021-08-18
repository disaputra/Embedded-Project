// sd card
#include <SD.h>
#include <SPI.h>

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
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");

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

    myFile.print("Temperature = ");
    myFile.print(Temp);
    myFile.print("°C,    Humidity = ");
    myFile.print(RH);
    myFile.println("%");
    myFile.close();
    
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening file");
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
  }
}
