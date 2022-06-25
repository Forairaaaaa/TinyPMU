#include "AXP173.h"


/* Private functions */
inline uint16_t AXP173::_getMin(uint16_t a, uint16_t b) {
    return ((a)<(b)?(a):(b));
}

inline uint16_t AXP173::_getMax(uint16_t a, uint16_t b) {
    return ((a)>(b)?(a):(b));
}

uint16_t AXP173::_getMid(uint16_t input, uint16_t min, uint16_t max) {
    return _getMax(_getMin(input, max), min);
}


/* Public functions */
#ifdef ARDUINO
/**
 * @brief AXP173 init
 * 
 * @param wire I2C wire pointer
 * @return true Init failed
 * @return false Init successful
 */
bool AXP173::begin(TwoWire * wire) {
    _I2C_init(wire, AXP173_ADDR);
    return _I2C_checkDevAvl();
}
#else
void AXP173::begin() {
}
#endif

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

/**
 * @brief Get bat current direction
 * 
 * @return true Bat charging
 * @return false Bat discharging
 */
bool AXP173::getBatCurrentDir() {
    return ( _I2C_read8Bit(0x00) & 0B00000100 ) ? true : false;
}

bool AXP173::isAXP173OverTemp() {
    return ( _I2C_read8Bit(0x01) & 0B10000000 ) ? true : false;
}

/**
 * @brief Get bat charging state
 * 
 * @return true Charging
 * @return false Charge finished or not charging
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

/**
 * @brief Set channels' output enable or disable
 * 
 * @param channel Output channel
 * @param state true:Enable, false:Disable
 */
void AXP173::setOutputEnable(OUTPUT_CHANNEL channel, bool state) {
    uint8_t buff = _I2C_read8Bit(0x12);
    switch (channel) {
        case DCDC1:
            buff = state ? (buff | (1U)) : (buff & ~(1U));
            break;
        case DCDC2:
            buff = state ? (buff | (1U << 4)) : (buff & ~(1U << 4));
            break;
        case LDO2:
            buff = state ? (buff | (1U << 2)) : (buff & ~(1U << 2));
            break;
        case LDO3:
            buff = state ? (buff | (1U << 3)) : (buff & ~(1U << 3));
            break;
        case LDO4:
            buff = state ? (buff | (1U << 1)) : (buff & ~(1U << 1));
            break;
        case ALL:
            buff = state ? (buff | 0B00001111) : (buff & 0B11110000);
            break;
        default:
            break;
    }
    _I2C_write1Byte(0x12, buff);
}

/**
 * @brief Set channels' output voltage
 * 
 * @param channel Output channel
 * @param voltage DCDC1 & LDO4: 700~3500(mV), DCDC2: 700~2275(mV), LDO2 & LDO3: 1800~3300{mV}
 */
void AXP173::setOutputVoltage(OUTPUT_CHANNEL channel, uint16_t voltage) {
    uint8_t buff = 0;
    switch (channel) {
        case DCDC1:
            voltage = (_getMid(voltage, 700, 3500) - 700) / 25;
            buff = _I2C_read8Bit(0x26);
            buff = (buff & 0B10000000) | (voltage & 0B01111111);
            _I2C_write1Byte(0x26, buff);
            break;
        case DCDC2:
            voltage = (_getMid(voltage, 700, 2275) - 700) / 25;
            buff = _I2C_read8Bit(0x23);
            buff = (buff & 0B11000000) | (voltage & 0B00111111);
            _I2C_write1Byte(0x23, buff);
            break;
        case LDO2:
            voltage = (_getMid(voltage, 1800, 3300) - 1800) / 100;
            buff = _I2C_read8Bit(0x28);
            buff = (buff & 0B00001111) | (voltage << 4);
            _I2C_write1Byte(0x28, buff);
            break;
        case LDO3:
            voltage = (_getMid(voltage, 1800, 3300) - 1800) / 100;
            buff = _I2C_read8Bit(0x28);
            buff = (buff & 0B11110000) | (voltage);
            _I2C_write1Byte(0x28, buff);
            break;
        case LDO4:
            voltage = (_getMid(voltage, 700, 3500) - 700) / 25;
            buff = _I2C_read8Bit(0x27);
            buff = (buff & 0B10000000) | (voltage & 0B01111111);
            _I2C_write1Byte(0x27, buff);
            break;
        default:
            break;
    }
}

void AXP173::powerOFF() {
    _I2C_write1Byte(0x32, (_I2C_read8Bit(0x32) | 0B10000000));
}

/**
 * @brief Set charge enable or disable
 * 
 * @param state true:Enable, false:Disable
 */
void AXP173::setChargeEnable(bool state) {
    if (state)
        _I2C_write1Byte(0x33, ((_I2C_read8Bit(0x33) | 0B10000000)));
    else
        _I2C_write1Byte(0x33, ((_I2C_read8Bit(0x33) & 0B01111111)));
}

void AXP173::setChargeCurrent(CHARGE_CURRENT current) {
    _I2C_write1Byte(0x33, ((_I2C_read8Bit(0x33) & 0B11110000) | current));
}

