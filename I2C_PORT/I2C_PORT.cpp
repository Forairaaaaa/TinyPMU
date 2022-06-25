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

void I2C_PORT::_I2C_write1Byte(uint8_t addr, uint8_t data) {
    _wire->beginTransmission(_dev_addr);
    _wire->write(addr);
    _wire->write(data);
    _wire->endTransmission();
}

uint8_t I2C_PORT::_I2C_read8Bit(uint8_t addr) {
    _wire->beginTransmission(_dev_addr);
    _wire->write(addr);
    _wire->endTransmission();
    _wire->requestFrom(_dev_addr, (size_t)1);
    return _wire->read();
}

uint16_t I2C_PORT::_I2C_read12Bit(uint8_t addr) {
    uint8_t buff[2];
    _I2C_readBuff(addr, 2, buff);
    return (buff[0] << 4) + buff[1];
}

uint16_t I2C_PORT::_I2C_read13Bit(uint8_t addr) {
    uint8_t buff[2];
    _I2C_readBuff(addr, 2, buff);
    return (buff[0] << 5) + buff[1];
}

uint16_t I2C_PORT::_I2C_read16Bit(uint8_t addr) {
    uint8_t buff[2];
    _I2C_readBuff(addr, 2, buff);
    return (buff[0] << 8) + buff[1];
}

uint32_t I2C_PORT::_I2C_read24Bit(uint8_t addr) {
    uint8_t buff[4];
    _I2C_readBuff(addr, 3, buff);
    return (buff[0] << 16) + (buff[1] << 8) + buff[2];
}

uint32_t I2C_PORT::_I2C_read32Bit(uint8_t addr) {
    uint8_t buff[4];
    _I2C_readBuff(addr, 4, buff);
    return (buff[0] << 24) + (buff[1] << 16) + (buff[2] << 8) + buff[3];
}

void I2C_PORT::_I2C_readBuff(uint8_t addr, int size, uint8_t buff[]) {
    _wire->beginTransmission(_dev_addr);
    _wire->write(addr);
    _wire->endTransmission();
    _wire->requestFrom(_dev_addr, (size_t)size);
    for (int i = 0; i < size; i++) {
        buff[i] = _wire->read();
    }
}

#else
void I2C_PORT::_I2C_init(uint8_t dev_addr) { }
void I2C_PORT::_I2C_checkDevAvl() { }
#endif

