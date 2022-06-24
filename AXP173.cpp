#include "AXP173.h"


/* Port interface */
void AXP173::_I2C_init() {
    #ifdef ARDUINO
    #endif
}

void AXP173::_I2C_write1Byte(uint8_t addr, uint8_t data) {
    #ifdef ARDUINO
    _wire->beginTransmission(AXP173_ADDR);
    _wire->write(addr);
    _wire->write(data);
    _wire->endTransmission();
    #endif
}

uint8_t AXP173::_I2C_read8Bit(uint8_t addr) {
    #ifdef ARDUINO
    _wire->beginTransmission(AXP173_ADDR);
    _wire->write(addr);
    _wire->endTransmission();
    _wire->requestFrom(AXP173_ADDR, 1);
    return _wire->read();
    #endif
}

void AXP173::_I2C_readBuff(uint8_t addr, uint8_t size, uint8_t buff[]) {
    #ifdef ARDUINO
    _wire->beginTransmission(AXP173_ADDR);
    _wire->write(addr);
    _wire->endTransmission();
    _wire->requestFrom(AXP173_ADDR, (int)size);
    for (int i = 0; i < size; i++) {
        buff[i] = _wire->read();
    }
    #endif
}


/* AXP173 init */
#ifdef ARDUINO
void AXP173::begin(TwoWire * wire) {
    _wire = wire;
}
#else
void AXP173::begin() {
}
#endif


/* Power info */
bool AXP173::isACINExist() {
    return ( _I2C_read8Bit(0x00) & 0B10000000 ) ? true : false;
}

bool AXP173::isACINAvl() {
    return ( _I2C_read8Bit(0x00) & 0B01000000 ) ? true : false;
}

bool AXP173::isVBUSExist() {
    return ( _I2C_read8Bit(0x00) & 0B00100000 ) ? true : false;
}

bool AXP173::isVBUSAvl() {
    return ( _I2C_read8Bit(0x00) & 0B00010000 ) ? true : false;
}

/*
* True: Charge
* False: Discharge
*/
bool AXP173::getBatCDir() {
    return ( _I2C_read8Bit(0x00) & 0B00000100 ) ? true : false;
}

bool AXP173::isAXP173OverTemp() {
    return ( _I2C_read8Bit(0x01) & 0B10000000 ) ? true : false;
}

/*
* True: Charging
* False: Not charging or charge finished
*/
bool AXP173::isCharging() {
    return ( _I2C_read8Bit(0x01) & 0B01000000 ) ? true : false;
}

bool AXP173::isBatExist() {
    return ( _I2C_read8Bit(0x01) & 0B00100000 ) ? true : false;
}

bool AXP173::isChargeCsmaller() {
    return ( _I2C_read8Bit(0x01) & 0B00000100 ) ? true : false;
}

