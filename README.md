# DFRobot_VisualRotaryEncoder
* [中文版](./README_CN.md)

This easy-to-use Rotary Encoder outputs data via Gravity-I2C interface. In contrast to general potentiometers, it comes with better texture and higher accuracy, and the rotary stepping accuracy is settable. Besides, the equipped LED ring can display the data in real time.

It can be used to adjust volume, firepower, revolving speed, and to adjust output status of the RGB light when cascading three rotary encoders.

![Product Photo Show](./resources/images/VisualRotaryEncoder.png)


## Product Link (https://www.dfrobot.com/product-2575.html)
    SKU: SEN0502


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary

* I2C data output, plus 1 for forward rotation and minus 1 for backward rotation, easy to use <br>
* The circular LED displays the current values, aesthetic and intuitive <br>
* Output data via 2 I2C interfaces, can be used with cascade devices <br>


## Installation

There two methods:

1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_VisualRotaryEncoder library from the Arduino Software Library Manager and download it.


## Methods

```C++

  /**
   * @fn begin
   * @brief initialization function
   * @return int type, means returning initialization status
   * @retval 0 NO_ERROR
   * @retval -1 ERR_DATA_BUS
   * @retval -2 ERR_IC_VERSION
   */
  virtual int begin(void);

  /**
   * @fn refreshBasicInfo
   * @brief retrieve basic information from the sensor and buffer it into basicInfo, the structure that stores information
   * @n     members of basicInfo structure: PID, VID, version, i2cAddr
   * @return None
   */
  void refreshBasicInfo(void);

  /**
   * @fn getEncoderValue
   * @brief get the encoder current count value
   * @return return value range： 0-1023
   */
  uint16_t getEncoderValue(void);

  /**
   * @fn setEncoderValue
   * @brief set the encoder value
   * @param value range[0, 1023], the setting is invalid when out of range
   * @return None
   */
  void setEncoderValue(uint16_t value);

  /**
   * @fn getGainCoefficient
   * @brief get the current gain factor of the encoder, and the numerical accuracy of turning one step 
   * @n     accuracy range：1~51, the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
   * @return return value range： 1-51
   */
  uint8_t getGainCoefficient(void);

  /**
   * @fn setGainCoefficient
   * @brief set the current gain factor of the encoder, and the numerical accuracy of turning one step 
   * @n     accuracy range：1~51，the minimum is 1 (light up one LED about every 2.5 turns), the maximum is 51 (light up one LED every one step rotation)
   * @param gainValue range[1, 51], the setting is invalid when out of range
   * @return None
   */
  void setGainCoefficient(uint8_t gainValue);

  /**
   * @fn detectButtonDown
   * @brief detect if the button is pressed
   * @return return button status
   * @retval   true Button pressed
   * @retval   false Button not pressed
   */
  bool detectButtonDown(void);

```


## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | :----:
Arduino Uno        |      √       |              |             |
Arduino MEGA2560   |      √       |              |             |
Arduino Leonardo   |      √       |              |             |
FireBeetle-ESP8266 |      √       |              |             |
FireBeetle-ESP32   |      √       |              |             |
FireBeetle-M0      |      √       |              |             |
Micro:bit          |      √       |              |             |


## History

- 2021/09/17 - Version 1.0.0 released.
- 2022/05/20 - Version 1.0.1 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2022. (Welcome to our [website](https://www.dfrobot.com/))

