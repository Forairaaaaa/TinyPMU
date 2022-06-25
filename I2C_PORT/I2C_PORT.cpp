#include "I2C_PORT.h"


/* Port interface */
#ifdef ARDUINO
void I2C_PORT::_I2C_init(TwoWire * wire, uint8_t dev_addr) {
    _wire = wire;
    _dev_addr = dev_addr;
}

bool I2C_PORT::_I2C_checkDevAvl() {
    _wire->beginTransmission(_dev_addr);
    return ( _wire->endTransmission() ? true : false);
}

#else
void I2C_PORT::_I2C_init(uint8_t dev_addr) { }
void I2C_PORT::_I2C_checkDevAvl() { }
#endif

void I2C_PORT::_I2C_write1Byte(uint8_t addr, uint8_t data) {
    #ifdef ARDUINO
    _wire->beginTransmission(_dev_addr);
    _wire->write(addr);
    _wire->write(data);
    _wire->endTransmission();
    #endif
}

uint8_t I2C_PORT::_I2C_read8Bit(uint8_t addr) {
    #ifdef ARDUINO
    _wire->beginTransmission(_dev_addr);
    _wire->write(addr);
    _wire->endTransmission();
    _wire->requestFrom(_dev_addr, 1);
    return _wire->read();
    #endif
}

void I2C_PORT::_I2C_readBuff(uint8_t addr, int size, uint8_t buff[]) {
    #ifdef ARDUINO
    _wire->beginTransmission(_dev_addr);
    _wire->write(addr);
    _wire->endTransmission();
    _wire->requestFrom(_dev_addr, size);
    for (int i = 0; i < size; i++) {
        buff[i] = _wire->read();
    }
    #endif
}