# DFRobot_VisualRotaryEncoder
* [中文版](./README_CN.md)

This Rotary Encoder is easy to use and outputs data via Gravity-I2C interface. In contrast to general potentiometers, it comes with better texture and higher accuracy, and the rotary stepping accuracy is settable. Besides, the equipped LED can display the data in real time.

It can be used to adjust volume, firepower, revolving speed, and to adjust output status of the RGB light when cascading three rotary encoders.

![Product Photo Show](../../resources/images/VisualRotaryEncoder.png)


## Product Link (https://www.dfrobot.com/product-2575.html)
    SKU：SEN0502


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary

* I2C data output, plus 1 for the forward and minus 1 for the reverse, easy to use <br>
* The circular LED displays the current values, aesthetic and intuitive <br>
* Output data via 2 I2C interfaces, can be used with cascade devices <br>


## Installation

Download the library file before use, paste it into the specified directory, then open the Examples folder and run the demo in the folder.

## Methods

```python

    '''!
      @brief Initialize sensor
      @return  return initialization status
      @retval True indicate initialization succeed
      @retval False indicate failed
    '''
    def begin(self):

    '''!
      @brief read the module basic information
      @n     retrieve basic information from the sensor and buffer it into a variable that stores information:
      @n     PID, VID, version, I2C_addr
    '''
    def read_basic_info(self):

    '''!
      @brief get the current value of the encoder
      @return return value range： 0-1023
    '''
    def get_encoder_value(self):

    '''!
      @brief set the encoder value
      @param value range[0, 1023], the setting is invalid when out of range
    '''
    def set_encoder_value(self, value):

    '''!
      @brief get the current gain factor of the encoder, and the numerical accuracy of turning one marker
      @n     accuracy range：1~51，the minimum is 1 (LED goes on every 2.5 turns), the maximum is 51 (LED goes on every one marker turn)
      @return return value range： 1-51
    '''
    def get_gain_coefficient(self):

    '''!
      @brief set the current gain factor of the encoder, and the numerical accuracy of turning one marker
      @n     accuracy range：1~51，the minimum is 1 (LED goes on every 2.5 turns), the maximum is 51 (LED goes on every one marker turn)
      @param gainValue range[1, 51], the setting is invalid when out of range
    '''
    def set_gain_coefficient(self, gain_value):

    '''!
      @brief detect if the button is pressed
      @return return true detect the button pressed，return false not detect the button pressed
    '''
    def detect_button_down(self):

```


## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2021/09/15 - Version 1.0.0 released.
- 2022/05/20 - Version 1.0.1 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

