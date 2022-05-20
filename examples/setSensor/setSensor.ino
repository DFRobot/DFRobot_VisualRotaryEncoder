/*!
 * @file        setSensor.ino
 * @brief       This demo shows how to set gain factor of the encoder，
 * @n           and set the encoder value to zero when the detection button is pressed
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [qsjhyy](yihuan.huang@dfrobot.com)
 * @version     V1.0
 * @date        2021-09-15
 * @url         https://github.com/DFRobot/DFRobot_VisualRotaryEncoder
 */
#include <DFRobot_VisualRotaryEncoder.h>

/**
 * Instantiate an object to drive our sensor;
 * Set address according to encoder DIP switch CH1 and CH2
 * (the setting takes effect after encoder power fail and restart):
 * | 1 | 2 | ADDR |
 * |---|---|------|
 * | 0 | 0 | 0x54 |
 * | 0 | 1 | 0x55 |
 * | 1 | 0 | 0x56 |
 * | 1 | 1 | 0x57 |
 */
DFRobot_VisualRotaryEncoder_I2C sensor(/*i2cAddr = */0x54, /*i2cBus = */&Wire);

void setup()
{
  Serial.begin(115200);

  // initialize the sensor
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * set the current gain factor of the encoder, and the numerical accuracy of turning one step
   * accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
   * gainValue range[1, 51], the setting is invalid when out of range, tip: small amplitude adjustment of gain factor has little effect on LED change
   */
  sensor.setGainCoefficient(50);

  /**
   * get the current gain factor of the encoder, and the numerical accuracy of turning one step
   * accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
   * return value range： 1-51
   */
  uint8_t gainCoefficient = sensor.getGainCoefficient();
  Serial.print("Encoder current gain coefficient: ");
  Serial.println(gainCoefficient);

  Serial.println();
  delay(1000);
}

void loop()
{
  /**
   * Detect if the button is pressed
   * return true when the button pressed，otherwise, return false
   */
  if(sensor.detectButtonDown()){
    /**
     * set the encoder count value
     * value range[0, 1023], the setting is invalid when out of range
     * In this example, set the encoder value to zero when detecting the button pressed, and you can see all the LEDs that light up before turning off
     */
    sensor.setEncoderValue(0);
  }

  /**
   * get the encoder current count 
   * return value range： 0-1023
   */
  uint16_t encoderValue = sensor.getEncoderValue();
  Serial.print("The encoder current counts: ");
  Serial.println(encoderValue);

  Serial.println();
  delay(1000);
}
