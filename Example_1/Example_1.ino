#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>  // Click here to get the library: http://librarymanager/All#SparkFun_LPS25HB
OpenLog myLog; 

LPS25HB pressureSensor; // Create an object of the LPS25HB class

void setup() {
  Wire.begin();// Inialize I2C
  myLog.begin();// Open connecing to OpenLog 

  pressureSensor.begin();    // Begin links an I2C port and I2C address to the sensor, sets an I2C speed, begins I2C on the main board, and then sets default settings

const byte OpenLogAddress = 42;// default qwiic openLog I2C address

  if(pressureSensor.isConnected() == false)  // The library supports some different error codes such as "DISCONNECTED"
  {
    Serial.println("LPS25HB disconnected. Reset the board to try again.");        // Alert the user that the device cannot be reached
    Serial.println("Are you using the right Wire port and I2C address?");         // Suggest possible fixes
    Serial.println("See Example2_I2C_Configuration for how to change these.");    // Suggest possible fixes
    Serial.println("");
    while(1);
  }
}

void loop() {

  myLog.println ("This goes to the log file");
  Serial.println ("This goes to the terminal");  
  Serial.print("Pressure in hPa");
    delay(40);// Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
}
myLog.println("This is recorded to the default log file");
  myLog.append("appendMe.txt");
  myLog.println("This is recorded to appendMe.txt");
  myLog.println("If this file doesn't exist it is created and");
  myLog.println("anything sent to OpenLog will be recorded to this file");

  myLog.println();
  myLog.println(F("Note: We can use the F(\"\") in sketches to move big print statements into program memory to save RAM"));
  myLog.append("appendMe1.txt");
  myLog.println(F("Note: We can use the F(\"\") in sketches to move big print statements into program memory to save RAM"));
  myLog.println(F("Note: We can use the F(\"\") in sketches to move big print statements into program memory to save RAM"));
  myLog.syncFile();

  Serial.println("Done!");
}

void loop()
{
  //Blink the Status LED because we're done!
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
