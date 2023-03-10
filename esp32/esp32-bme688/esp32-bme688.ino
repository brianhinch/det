#include "Zanshin_BME680.h"  // Include the BME680 Sensor library

const uint32_t DELAY_TIME = 1000;

BME680_Class BME680;  ///< Create an instance of the BME680 class

///< Forward function declaration with default value for sea level
float altitude(const int32_t press, const float seaLevel = 1013.25);
float altitude(const int32_t press, const float seaLevel) {
  /*!
  @brief     This converts a pressure measurement into a height in meters
  @details   The corrected sea-level pressure can be passed into the function if it is known,
             otherwise the standard atmospheric pressure of 1013.25hPa is used (see
             https://en.wikipedia.org/wiki/Atmospheric_pressure) for details.
  @param[in] press    Pressure reading from BME680
  @param[in] seaLevel Sea-Level pressure in millibars
  @return    floating point altitude in meters.
  */
  static float Altitude;
  Altitude =
    44330.0 * (1.0 - pow(((float)press / 100.0) / seaLevel, 0.1903));  // Convert into meters
  return (Altitude);
}  // of method altitude()

void setup() {
  Serial.begin(115200);  // Start serial port at Baud rate

  while (!BME680.begin(I2C_STANDARD_MODE)) {  // Start BME680 using I2C, use first device found
    Serial.print("-  Unable to find BME680. Trying again in 5 seconds.\n");
    delay(5000);
  }  // of loop until device is located

  BME680.setOversampling(TemperatureSensor, Oversample16);  // Use enumerated type values
  BME680.setOversampling(HumiditySensor, Oversample16);     // Use enumerated type values
  BME680.setOversampling(PressureSensor, Oversample16);     // Use enumerated type values

  BME680.setIIRFilter(IIR4);  // Use enumerated type values

  BME680.setGas(320, 150);  // 320 degrees C for 150 milliseconds

  delay(3000);  // wait 3s for serial monitor to open (optional)
}

void loop() {

  static int32_t temp, humidity, pressure, gas;  // BME readings
  static char buf[17];                           // sprintf text buffer
  static float alt;                              // Temporary variable
  static uint16_t loopCounter = 0;               // Display iterations

  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings
  alt = altitude(pressure);  // temp altitude

  if (loopCounter++ != 0) {
    Serial.print("Loop:");
    Serial.print((loopCounter - 1) % 9999);  // Clamp to 9999,
    Serial.print(",");

    sprintf(buf, "TempC:00000%03d.%02d,",
            (int8_t)(temp / 100), (uint8_t)(temp % 100));  // Temp in decidegrees
    Serial.print(buf);

    sprintf(buf, "HumPc:0000%03d.%03d,",
            (int8_t)(humidity / 1000), (uint16_t)(humidity % 1000));  // Humidity milli-pct
    Serial.print(buf);

    sprintf(buf, "PrsPa:0%07d.%02d,",
            (int16_t)(pressure / 100), (uint8_t)(pressure % 100));  // Pressure Pascals
    Serial.print(buf);

    sprintf(buf, "AltiM:000%05d.%02d,",
            (int16_t)(alt), ((uint8_t)(alt * 100) % 100));  // Altitude meters
    Serial.print(buf);

    sprintf(buf, "AirRM:%07d.%03d\n",
            (int16_t)(gas / 100), (uint8_t)(gas % 100));  // Resistance milliohms
    Serial.print(buf);

    delay(DELAY_TIME);
  }
}
