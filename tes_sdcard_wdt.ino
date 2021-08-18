// sd card
#include <SD.h>
#include <SPI.h>

// watchdog time
#include <avr/wdt.h>


File myFile;

int pinCS = 53; // Pin 10 on Arduino Uno

void setup() {
    
  Serial.begin(9600);
  Serial.println("Setup started :");
  delay(2000);
  wdt_enable(WDTO_4S); // watchdog time
  
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
    wdt_disable();
  } else
  {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");

    wdt_reset();
    while(1){}
    return;
  }
  
  // Create/Open file 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println("Testing text 1, 2 ,3...");
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }

  // Reading the file
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
  
}
void loop() {
  // empty
}
