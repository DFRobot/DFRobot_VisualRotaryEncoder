/*!
 * @file  DFRobot_VisualRotaryEncoder.h
 * @brief  Define infrastructure of DFRobot_VisualRotaryEncoder class
 * @details  DFRobot_VisualRotaryEncoder.h define the device information register and device function register, declare the sensor function api
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-14
 * @url  https://github.com/DFRobot/DFRobot_VisualRotaryEncoder
 */
#ifndef __DFROBOT_VISUAL_ROTARY_ENCODER_H__
#define __DFROBOT_VISUAL_ROTARY_ENCODER_H__

#include <Arduino.h>
#include <Wire.h>

// #define ENABLE_DBG   //!< open this macro and you can see the details of the program
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif

#define VISUAL_ROTARY_ENCODER_DEFAULT_I2C_ADDR   uint8_t(0x54)      ///< default I2C communication address 
#define VISUAL_ROTARY_ENCODER_PID                uint16_t(0x01F6)   ///< module PID (SEN0502)(the highest two of 16-bit data are used to determine SKU type: 00：SEN, 01：DFR, 10：TEL. The next 14 are numbers)

// VISUAL_ROTARY_ENCODER register address
#define VISUAL_ROTARY_ENCODER_PID_MSB_REG                 uint8_t(0x00)   ///< module PID memory register，default value is 0x01F6 (the highest two of 16-bit data are used to determine SKU type: 00：SEN, 01：DFR, 10：TEL. The next 14 are numbers)
#define VISUAL_ROTARY_ENCODER_PID_LSB_REG                 uint8_t(0x01)
#define VISUAL_ROTARY_ENCODER_VID_MSB_REG                 uint8_t(0x02)   ///< module VID memory register，default value is 0x3343（for manufacturer DFRobot）
#define VISUAL_ROTARY_ENCODER_VID_LSB_REG                 uint8_t(0x03)
#define VISUAL_ROTARY_ENCODER_VERSION_MSB_REG             uint8_t(0x04)   ///< memory register of firmware revision number：0x0100 represents V0.1.0.0
#define VISUAL_ROTARY_ENCODER_VERSION_LSB_REG             uint8_t(0x05)
#define VISUAL_ROTARY_ENCODER_ADDR_REG                    uint8_t(0x07)   ///< memory register of module communication address，default value is 0x54，module device address (1~127)
#define VISUAL_ROTARY_ENCODER_COUNT_MSB_REG               uint8_t(0x08)   ///< encoder count，range 0-1023
#define VISUAL_ROTARY_ENCODER_COUNT_LSB_REG               uint8_t(0x09)
#define VISUAL_ROTARY_ENCODER_KEY_STATUS_REG              uint8_t(0x0A)   ///< encoder button status
#define VISUAL_ROTARY_ENCODER_GAIN_REG                    uint8_t(0x0B)   ///< encoder incremental factor


class DFRobot_VisualRotaryEncoder
{
public:
  #define NO_ERR             0     ///< No error
  #define ERR_DATA_BUS      (-1)   ///< data bus error
  #define ERR_IC_VERSION    (-2)   ///< the chip version isn't suitable 

  /**
   * @struct sBasicInfo_t
   * @brief  Device basic information storage structure 
   */
  typedef struct
  {
    uint16_t PID;   /**< module PID, default value is 0x01F6 (the highest two of 16-bit data are used to determine SKU type: 00：SEN, 01：DFR, 10：TEL. The next 14 are numbers)(SEN0502) */
    uint16_t VID;   /**< module VID, default value is 0x3343(for manufacturer DFRobot) */
    uint16_t version;   /**< firmware revision number: 0x0100 represents V0.1.0.0 */
    uint8_t i2cAddr;   /**< module communication address, default value is 0x54, module device address(0x54~0x57) */
  }sBasicInfo_t;

public:
  /**
   * @fn DFRobot_VisualRotaryEncoder
   * @brief constructor
   * @return None
   */
  DFRobot_VisualRotaryEncoder();

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
   * @brief get the encoder current count
   * @return return value range： 0-1023
   */
  uint16_t getEncoderValue(void);

  /**
   * @fn setEncoderValue
   * @brief set the encoder count
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
   * @retval   true  Button pressed
   * @retval   false Button not pressed
   */
  bool detectButtonDown(void);

protected:
/***************** Register read/write interface ******************************/

  /**
   * @fn writeReg
   * @brief Write register function, design it as a pure virtual function, implemented by a derived class
   * @param reg  Register address 8bits
   * @param pBuf  Buffer for data to be to written
   * @param size  Length of data to written 
   * @return None
   */
  virtual void writeReg(uint8_t reg, const void* pBuf, size_t size)=0;

  /**
   * @fn readReg
   * @brief Read register function, design it as a pure virtual function, implemented by a derived class
   * @param reg  Register address 8bits
   * @param pBuf  Buffer for data to be read 
   * @param size  Length of data to be read
   * @return return data length, returning 0 means length reading failed
   */
  virtual size_t readReg(uint8_t reg, void* pBuf, size_t size)=0;

public:
  // structure for storing sensor basic information
  sBasicInfo_t basicInfo;

};

/***************** I2C initialization, read and write ******************************/

class DFRobot_VisualRotaryEncoder_I2C:public DFRobot_VisualRotaryEncoder
{
public:
  /**
   * @fn DFRobot_VisualRotaryEncoder_I2C
   * @brief constructor, configure sensor I2C communication address according to module DIP switch status
   * @param i2cAddr RotaryEncoder I2C communication address
   * @param pWire  Wire object is defined in Wire.h, so just use &Wire and the methods in Wire can be pointed to and used
   * @return None
   */
  DFRobot_VisualRotaryEncoder_I2C(uint8_t i2cAddr=VISUAL_ROTARY_ENCODER_DEFAULT_I2C_ADDR, TwoWire *pWire = &Wire);

  /**
   * @fn begin
   * @brief subclass initialization function
   * @return int type, means returning initialization status
   * @retval 0 NO_ERROR
   * @retval -1 ERR_DATA_BUS
   * @retval -2 ERR_IC_VERSION
   */
  virtual int begin(void);

protected:

  /**
   * @fn writeReg
   * @brief Write register values through I2C bus
   * @param reg  Register address 8bits
   * @param pBuf Buffer for data to be to written 
   * @param size Length of data to be written 
   * @return None
   */
  virtual void writeReg(uint8_t reg, const void* pBuf, size_t size);

  /**
   * @fn readReg
   * @brief Read register values through I2C bus
   * @param reg  Register address 8bits
   * @param pBuf Buffer for data to be read
   * @param size Length of data to be read 
   * @return return data length, returning 0 means reading failed
   */
  virtual size_t readReg(uint8_t reg, void* pBuf, size_t size);

private:
  TwoWire *_pWire;   // pointer to I2C communication method
  uint8_t _deviceAddr;   // I2C communication device address
};

#endif
