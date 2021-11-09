/*!
 * @file        getData.ino
 * @brief       This demo shows how to get basic encoder information, the current count and rotation gain
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
 * Set address according to encoder DIP switch CH1 and CH2:
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

  // initialize sensor
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * Retrieve basic information from the sensor and buffer it into basicInfo, the structure that stores information
   * Members of basicInfo structure: PID, VID, version, i2cAddr
   */
  sensor.refreshBasicInfo();

  /* Module PID, default value 0x01F6 (the highest two of the 16-bits data are used to judge SKU type: 00: SEN, 01: DFR, 10: TEL; The next 14 numbers are used as num)(SEN0502) */
  Serial.print("PID: 0x0");
  Serial.println(sensor.basicInfo.PID, HEX);

  /* Module VID, default value 0x3343(for manufacturer DFRobot) */
  Serial.print("VID: 0x");
  Serial.println(sensor.basicInfo.VID, HEX);

  /* Firmware version number: 0x0100 represents V0.1.0.0 */
  Serial.print("versions: 0x0");
  Serial.println(sensor.basicInfo.version, HEX);

  /* Module communication address, default value 0x54, module device address (0x54~0x57) */
  Serial.print("communication address:  0x");
  Serial.println(sensor.basicInfo.i2cAddr, HEX);

  /**
   * Get the encoder current gain factor, and the numerical accuracy for turning one step
   * Accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
   * Return value range： 1-51
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
   * Get the encoder current count
   * Return value range： 0-1023
   */
  uint16_t encoderValue = sensor.getEncoderValue();
  Serial.print("The encoder current counts: ");
  Serial.println(encoderValue);

  Serial.println();
  delay(1000);
}
