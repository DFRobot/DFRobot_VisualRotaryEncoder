# -*- coding: utf-8 -*
'''
  @file      get_data.py
  @brief     This demo shows how to set gain factor of the encoder，
  @n         and set the encoder value to zero when the detection button is pressed.
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license   The MIT License (MIT)
  @author    [qsjhyy](yihuan.huang@dfrobot.com)
  @version   V1.0
  @date      2021-09-15
  @url       https://github.com/DFRobot/DFRobot_VisualRotaryEncoder
'''
from __future__ import print_function
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))))

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
    set the current gain factor of the encoder, and the numerical accuracy of turning one step
    accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
    gainValue range[1, 51], the setting is invalid when out of range, tip: small amplitude adjustment of gain factor has little effect on LED change
  '''
  sensor.set_gain_coefficient(50)

  '''
    get the current gain factor of the encoder, and the numerical accuracy of turning one step
    accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
    return value range： 1-51
  '''
  gain_coefficient = sensor.get_gain_coefficient()
  print("Encoder current gain coefficient: %d\n" %gain_coefficient)

  time.sleep(1)


def loop():
  '''
    detect if the button is pressed
    return true when the button pressed，otherwise, return false
  '''
  if(sensor.detect_button_down()):
    '''
      set the encoder value
      value range[0, 1023], the setting is invalid when out of range
      in this example, set the encoder value to zero when detecting the button pressed, and you can see all the LEDs that light up before turning off
    '''
    sensor.set_encoder_value(0)

  '''
    get the current encoder count
    return value range： 0-1023
  '''
  encoder_value = sensor.get_encoder_value()
  print("The encoder current counts: %d\n" %encoder_value)

  time.sleep(1)


if __name__ == "__main__":
  setup()
  while True:
    loop()
