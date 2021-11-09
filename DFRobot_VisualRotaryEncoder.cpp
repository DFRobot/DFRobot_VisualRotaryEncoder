/*!
 * @file  DFRobot_VisualRotaryEncoder.cpp
 * @brief  DFRobot_VisualRotaryEncoder.cpp Initialize the I2C,
 * @n      get encoder basic information, button trigger condition and the current value, adjust encoder values and rotation gain
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-15
 * @url  https://github.com/DFRobot/DFRobot_VisualRotaryEncoder
 */
#include "DFRobot_VisualRotaryEncoder.h"

DFRobot_VisualRotaryEncoder::DFRobot_VisualRotaryEncoder()
{
}


int DFRobot_VisualRotaryEncoder::begin(void)
{
  uint8_t idBuf[2];
  if(0 == readReg(VISUAL_ROTARY_ENCODER_PID_MSB_REG, idBuf, sizeof(idBuf))){   // Judge whether the data bus is successful
    DBG("ERR_DATA_BUS");
    return ERR_DATA_BUS;
  }

  DBG("real sensor id="); DBG( (uint16_t)idBuf[0] << 8 | (uint16_t)idBuf[1], HEX );
  if( VISUAL_ROTARY_ENCODER_PID != ( (uint16_t)idBuf[0] << 8 | (uint16_t)idBuf[1] ) ){   // Judge whether the chip version matches
    DBG("ERR_IC_VERSION");
    return ERR_IC_VERSION;
  }

  delay(200);
  DBG("begin ok!");
  return NO_ERR;
}

void DFRobot_VisualRotaryEncoder::refreshBasicInfo(void)
{
  uint8_t tempBuf[8] = {0};
  readReg(VISUAL_ROTARY_ENCODER_PID_MSB_REG, tempBuf, sizeof(tempBuf));
  basicInfo.PID = (uint16_t)tempBuf[0] << 8 | (uint16_t)tempBuf[1];   // PID
  basicInfo.VID = (uint16_t)tempBuf[2] << 8 | (uint16_t)tempBuf[3];   // VID
  basicInfo.version = (uint16_t)tempBuf[4] << 8 | (uint16_t)tempBuf[5];   // version
  basicInfo.i2cAddr = (uint16_t)tempBuf[7];   // I2C addr
}

uint16_t DFRobot_VisualRotaryEncoder::getEncoderValue(void)
{
  uint8_t CountValue[2] = {0};
  readReg(VISUAL_ROTARY_ENCODER_COUNT_MSB_REG, CountValue, sizeof(CountValue));

  return (uint16_t)CountValue[0] << 8 | (uint16_t)CountValue[1];
}

void DFRobot_VisualRotaryEncoder::setEncoderValue(uint16_t value)
{
  if(0x3FF >= value){
    uint8_t tempBuf[2] = {0};
    tempBuf[0] = (value & 0xFF00) >> 8;
    tempBuf[1] = value & 0x00FF;
    writeReg(VISUAL_ROTARY_ENCODER_COUNT_MSB_REG, tempBuf, sizeof(tempBuf));
  }
}

uint8_t DFRobot_VisualRotaryEncoder::getGainCoefficient(void) {
  uint8_t RotateGain = 0;
  readReg(VISUAL_ROTARY_ENCODER_GAIN_REG, &RotateGain, sizeof(RotateGain));

  return RotateGain;
}

void DFRobot_VisualRotaryEncoder::setGainCoefficient(uint8_t gainValue) {
  if((0x01 <= gainValue) && (0x33 >= gainValue)){
    writeReg(VISUAL_ROTARY_ENCODER_GAIN_REG, &gainValue, sizeof(gainValue));
  }
}

bool DFRobot_VisualRotaryEncoder::detectButtonDown(void) {
  bool ret = false;
  uint8_t buttonStatus, clearStatus=0x00;

  readReg(VISUAL_ROTARY_ENCODER_KEY_STATUS_REG, &buttonStatus, sizeof(buttonStatus));

  if( 0 != (buttonStatus & 0x01) ){
    writeReg(VISUAL_ROTARY_ENCODER_KEY_STATUS_REG, &clearStatus, sizeof(clearStatus));
    ret = true;
  }

  return ret;
}

/************ Initialization of I2C interfaces reading and writing ***********/

DFRobot_VisualRotaryEncoder_I2C::DFRobot_VisualRotaryEncoder_I2C(uint8_t i2cAddr, TwoWire *pWire)
{
  _deviceAddr = i2cAddr;
  _pWire = pWire;
}

int DFRobot_VisualRotaryEncoder_I2C::begin(void)
{
  _pWire->begin();   // Wire.h（I2C）library function initialize wire library
  delay(50);

  return DFRobot_VisualRotaryEncoder::begin();   // Use the initialization function of the parent class
}

void DFRobot_VisualRotaryEncoder_I2C::writeReg(uint8_t reg, const void* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);

  for(size_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }

  _pWire->endTransmission();
}

size_t DFRobot_VisualRotaryEncoder_I2C::readReg(uint8_t reg, void* pBuf, size_t size)
{
  size_t count = 0;
  if(NULL == pBuf){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t*)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire -> write(reg);
  if(0 != _pWire->endTransmission()){
    // Used Wire.endTransmission() to end a slave transmission started by beginTransmission() and arranged by write().
    DBG("endTransmission ERROR!!");
  }else{
    // Master device requests size bytes from slave device, which can be accepted by master device with read() or available()
    _pWire->requestFrom( _deviceAddr, (uint8_t)size );

    while (_pWire->available()){
      _pBuf[count++] = _pWire->read();   // Use read() to receive and put into buf
      // DBG(_pBuf[count-1], HEX);
    }
  }

  return count;
}
