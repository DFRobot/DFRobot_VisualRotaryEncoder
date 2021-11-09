# -*- coding: utf-8 -*
'''!
  @file      get_data.py
  @brief     This demo shows how to get basic encoder information, the current count and current rotation gain
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license   The MIT License (MIT)
  @author    [qsjhyy](yihuan.huang@dfrobot.com)
  @version   V1.0
  @date      2021-09-15
  @url       https://github.com/DFRobot/DFRobot_VisualRotaryEncoder
'''
from __future__ import print_function
import sys
sys.path.append('../')
from DFRobot_VisualRotaryEncoder import *

'''
  Instantiate an object to drive our sensor;
  Set address according to encoder DIP switch CH1 and CH2:
  | 1 | 2 | ADDR |
  |---|---|------|
  | 0 | 0 | 0x54 |
  | 0 | 1 | 0x55 |
  | 1 | 0 | 0x56 |
  | 1 | 1 | 0x57 |
'''
sensor = DFRobot_VisualRotaryEncoder(i2c_addr = 0x54, bus = 1)


def setup():
  while (sensor.begin() == False):
    print ('Please check that the device is properly connected')
    time.sleep(3)
  print("sensor begin successfully!!!\n")

  '''
    read the module basic information
    retrieve basic information from the sensor and buffer it into a variable that stores information:
    PID, VID, version, I2C_addr
  '''
  sensor.read_basic_info()

  # module PID，default value 0x01F6 (the highest two of the 16-bits data are used to judge SKU type: 00: SEN, 01: DFR, 10: TEL; The next 14 numbers are used as num)(SEN0502)
  print("PID: 0x0%x" %sensor.PID)

  # module VID，default value 0x3343（for manufacturer is DFRobot）
  print("VID: 0x%x" %sensor.VID)

  # firmware revision number：0x0100 represents V0.1.0.0
  print("mailing address: 0x0%x" %sensor.version)

  # module communication address，default value 0x54，module device address (0x54~0x57)
  print("baudrate: 0x%x" %sensor.I2C_addr)

  '''
    get the current gain factor of the encoder, and the numerical accuracy of turning one step
    accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
    return value range： 1-51
  '''
  gain_coefficient = sensor.get_gain_coefficient()
  print("Encoder current gain coefficient: %d\n" %gain_coefficient)

  time.sleep(1.5)


def loop():
  '''
    get the encoder current count
    return value range： 0-1023
  '''
  encoder_value = sensor.get_encoder_value()
  print("The encoder current counts: %d" %encoder_value)

  time.sleep(1)


if __name__ == "__main__":
  setup()
  while True:
    loop()
