#include <SD.h>

const int lbit = 22; //The pin you want to be your "lowest significant bit"
const int hbit = 29; //The pin you want to be your "most significant bit" 
const int bitdepth = hbit - lbit;

uint8_t val;
long int t1;

const int samplerate = 4000;
const int loopdelay = 1000000/samplerate;

String filename = "YOUR AUDIO FILE"; // The name of your audio file goes here
File sdata;

void setup()
{
  Serial.begin(9600);

  // Assign pins lbit through hbit as outputs
  for (int n = lbit; n<=hbit; n++) {
  	pinMode(n, OUTPUT);
  }
  
  Serial.print("Initializing SD card...");

  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  File sdata = SD.open(filename,FILE_READ);

  if (sdata) {
    Serial.println("playing!");
    while (true) {
      t1 = micros();
      while (sdata.available()) {
        val = sdata.read();

        // Cycle bits of 'var' to pins lbit to hbit, with lbit as lsb and hbit as msb
        for (uint8_t n=0; n<=bitdepth; n++) {digitalWrite(n + lbit,(val >> n) & 1);}

        delayMicroseconds(loopdelay - (micros() - t1)); // Delay to samplerate
        t1 = micros();
      }
      sdata.seek(0);
      Serial.println("looping!");
    }
  }

  else {Serial.println("error opening file!");}

  Serial.println("Program end...");
  sdata.close();
}

void loop()
{

}