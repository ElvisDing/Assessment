#include <Wire.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"
#include <Servo.h>


OpenLog myLog; //Create instance
LPS25HB pressureSensor; // Create an object of the LPS25HB class
Servo myservo;  // create servo object to control a servo



int pos = 0;    // variable to store the servo position
const byte OpenLogAddress = 42; // Default Qwiic OpenLog I2C address
const byte SERVO = 11;// 

void setup()
{
 
  pressureSensor.begin();
  Wire.begin();
  myLog.begin(); //Open connection to OpenLog (no pun intended)

  Serial.begin(9600); //9600bps is used for debug statements
  myLog.create("Elvis.txt");
  myLog.append("Elvis.txt");
  myLog.print("Pressure, Temperature");
  myLog.syncFile();

/*Pressure, Temperature
 * 25,15
 * 25,300
 */

  Serial.println("set up finished");  
  myservo.attach(SERVO);  // attaches the servo on pin 9 to the servo object   
}

void loop() {
  if (pressureSensor.isConnected() == true)
  {
    if (pressureSensor.getStatus() == 0x00)
    {
      pressureSensor.begin();
    } // If it is connected but not responding (for example after a hot-swap) then it may need to be re-initialized

    Serial.print("Pressure (hPa): ");
    Serial.print(pressureSensor.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    Serial.print(", Temperature (degC): ");
    Serial.println(pressureSensor.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480


    myLog.print(pressureSensor.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    myLog.print(",");
    myLog.println(pressureSensor.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480

    myLog.syncFile();
  }
  else
  {
    Serial.println("Disconnected");
    pressureSensor.begin();
  }                                         // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
}
