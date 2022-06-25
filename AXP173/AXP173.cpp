#include "AXP173.h"



/* AXP173 init */
#ifdef ARDUINO

/*
*   Ture:   Failed
*   False:  Successful
*/
bool AXP173::begin(TwoWire * wire) {
    _I2C_init(wire, AXP173_ADDR);
    return _I2C_checkDevAvl();
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

