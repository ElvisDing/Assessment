#include <Wire.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"
#include <Servo.h>

OpenLog Data; //Create instance
LPS25HB pressureIndicators; // Create an object of the LPS25HB class
Servo Rotor;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
const byte SERVO = 11;//
const byte DELAY = 3000;
const byte ANGLE = 90;

//sets up the pins to read and write to/from
void setup()
{
  pressureIndicators.begin();
  Wire.begin();
  Data.begin(); //Open connection to data (no pun intended)

  Serial.begin(9600); //9600bps is used for debug statements
  Data.create("Elvis.txt");
  Data.append("Elvis.txt");
  Data.print("Pressure, Temperature");
  Data.syncFile();

  Rotor.attach(SERVO);  // attaches the servo on pin 9 to the servo object
  Rotor.write(0);
  Serial.println("set up finished");
}

// calls the test sensor method
void loop() {
  if (pressureIndicators.isConnected() == true)
  {
    if (pressureIndicators.getStatus() == 0x00)
    {
      pressureIndicators.begin(); // If it is connected but not responding (for example after a hot-swap) then it may need to be re-initialized
    }

    Serial.print("Pressure (hPa): ");
    Serial.print(pressureIndicators.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    Serial.print(", Temperature (degC): ");
    Serial.println(pressureIndicators.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480

    Data.print(pressureIndicators.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    Data.print(",");
    Data.println(pressureIndicators.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480

    Data.syncFile();
  }
  else
  {
    Serial.println("Disconnected");
    pressureIndicators.begin();
  }
  
  if (millis() > DELAY) {  // DELAY(3000) ms corresponds to the maximum update rate of the sensor.

    Serial.print("Parachute deployed");
    Rotor.write(ANGLE);              // tell servo to go to position in variable '90'.
  }
}
