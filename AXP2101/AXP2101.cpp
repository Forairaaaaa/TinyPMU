#include "AXP2101.h"


/* Private functions */
inline uint16_t AXP2101::_getMin(uint16_t a, uint16_t b) {
    return ((a)<(b)?(a):(b));
}

inline uint16_t AXP2101::_getMax(uint16_t a, uint16_t b) {
    return ((a)>(b)?(a):(b));
}

uint16_t AXP2101::_getMid(uint16_t input, uint16_t min, uint16_t max) {
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
bool AXP2101::begin(TwoWire * wire) {
    _I2C_init(wire, AXP173_ADDR);
    return _I2C_checkDevAvl();
}
#else
void AXP173::begin() {
}
#endif

bool AXP2101::isACINExist() {
    return ( _I2C_read8Bit(0x00) & 0B10000000 ) ? true : false;
}

bool AXP2101::isACINAvl() {
    return ( _I2C_read8Bit(0x00) & 0B01000000 ) ? true : false;
}

bool AXP2101::isVBUSExist() {
    return ( _I2C_read8Bit(0x00) & 0B00100000 ) ? true : false;
}

bool AXP2101::isVBUSAvl() {
    return ( _I2C_read8Bit(0x00) & 0B00010000 ) ? true : false;
}

/**
 * @brief Get bat current direction
 * 
 * @return true Bat charging
 * @return false Bat discharging
 */
bool AXP2101::getBatCurrentDir() {
    return ( _I2C_read8Bit(0x00) & 0B00000100 ) ? true : false;
}

bool AXP2101::isAXP173OverTemp() {
    return ( _I2C_read8Bit(0x01) & 0B10000000 ) ? true : false;
}

/**
 * @brief Get bat charging state
 * 
 * @return true Charging
 * @return false Charge finished or not charging
 */
bool AXP2101::isCharging() {
    return ( _I2C_read8Bit(0x01) & 0B01000000 ) ? true : false;
}

bool AXP2101::isBatExist() {
    return ( _I2C_read8Bit(0x01) & 0B00100000 ) ? true : false;
}

bool AXP2101::isChargeCsmaller() {
    return ( _I2C_read8Bit(0x01) & 0B00000100 ) ? true : false;
}

/**
 * @brief Set channels' output enable or disable
 * 
 * @param channel Output channel
 * @param state true:Enable, false:Disable
 */
void AXP2101::setOutputEnable(OUTPUT_CHANNEL channel, bool state) {
    // uint8_t buff = _I2C_read8Bit(0x12);
    // buff = state ? ( buff | (1U << channel) ) : ( buff & ~(1U << channel) );
    // _I2C_write1Byte(0x12, buff);

    uint8_t buff = _I2C_read8Bit(0x90);
    switch (channel) {
    case OP_DLDO1:
        buff = state ? ( buff | (1U << 7) ) : ( buff & ~(1U << 7) );
        _I2C_write1Byte(0x90, buff);
        break;
    default:
        break;
    }
}

/**
 * @brief Set channels' output voltage
 * 
 * @param channel Output channel
 * @param voltage DCDC1 & LDO4: 700~3500(mV), DCDC2: 700~2275(mV), LDO2 & LDO3: 1800~3300{mV}
 */
void AXP2101::setOutputVoltage(OUTPUT_CHANNEL channel, uint16_t voltage) {
    uint8_t buff = 0;
    switch (channel) {
        case OP_DLDO1:
            voltage = (_getMid(voltage, 500, 3300) - 500) / 100;
            buff = _I2C_read8Bit(OP_DLDO1);
            buff = (buff & 0B11100000) | (voltage & 0B00011111);
            _I2C_write1Byte(OP_DLDO1, buff);
            break;
        // case OP_DCDC1:
        //     voltage = (_getMid(voltage, 700, 3500) - 700) / 25;
        //     buff = _I2C_read8Bit(0x26);
        //     buff = (buff & 0B10000000) | (voltage & 0B01111111);
        //     _I2C_write1Byte(0x26, buff);
        //     break;
        // case OP_DCDC2:
        //     voltage = (_getMid(voltage, 700, 2275) - 700) / 25;
        //     buff = _I2C_read8Bit(0x23);
        //     buff = (buff & 0B11000000) | (voltage & 0B00111111);
        //     _I2C_write1Byte(0x23, buff);
        //     break;
        // case OP_LDO2:
        //     voltage = (_getMid(voltage, 1800, 3300) - 1800) / 100;
        //     buff = _I2C_read8Bit(0x28);
        //     buff = (buff & 0B00001111) | (voltage << 4);
        //     _I2C_write1Byte(0x28, buff);
        //     break;
        // case OP_LDO3:
        //     voltage = (_getMid(voltage, 1800, 3300) - 1800) / 100;
        //     buff = _I2C_read8Bit(0x28);
        //     buff = (buff & 0B11110000) | (voltage);
        //     _I2C_write1Byte(0x28, buff);
        //     break;
        // case OP_LDO4:
        //     voltage = (_getMid(voltage, 700, 3500) - 700) / 25;
        //     buff = _I2C_read8Bit(0x27);
        //     buff = (buff & 0B10000000) | (voltage & 0B01111111);
        //     _I2C_write1Byte(0x27, buff);
        //     break;
        default:
            break;
    }
}

void AXP2101::powerOFF() {
    _I2C_write1Byte(0x32, (_I2C_read8Bit(0x32) | 0B10000000));
}

/**
 * @brief Set charge enable or disable
 * 
 * @param state true:Enable, false:Disable
 */
void AXP2101::setChargeEnable(bool state) {
    if (state)
        _I2C_write1Byte(0x33, ((_I2C_read8Bit(0x33) | 0B10000000)));
    else
        _I2C_write1Byte(0x33, ((_I2C_read8Bit(0x33) & 0B01111111)));
}

void AXP2101::setChargeCurrent(CHARGE_CURRENT current) {
    _I2C_write1Byte(0x33, ((_I2C_read8Bit(0x33) & 0B11110000) | current));
}

/**
 * @brief Set ADC channel enable or disable
 * 
 * @param channel ADC channel
 * @param state true:Enable, false:Disable
 */
void AXP2101::setADCEnable(ADC_CHANNEL channel, bool state) {
    uint8_t buff = _I2C_read8Bit(0x82);
    buff = state ? ( buff | (1U << channel) ) : ( buff & ~(1U << channel) );
    _I2C_write1Byte(0x82, buff);
}

void AXP2101::setCoulometer(COULOMETER_CTRL option, bool state) {
    uint8_t buff = _I2C_read8Bit(0xB8);
    buff = state ? ( buff | (1U << option) ) : ( buff & ~(1U << option) );
    _I2C_write1Byte(0xB8, buff);
}

inline uint32_t AXP2101::getCoulometerChargeData() {
    return _I2C_read32Bit(0xB0);
}

inline uint32_t AXP2101::getCoulometerDischargeData() {
    return _I2C_read32Bit(0xB4);
}

float AXP2101::getCoulometerData() {
    uint32_t coin = getCoulometerChargeData();
    uint32_t coout = getCoulometerDischargeData();
    // data = 65536 * current_LSB * (coin - coout) / 3600 / ADC rate
    return 65536 * 0.5 * (int32_t)(coin - coout) / 3600.0 / 25.0;
}

float AXP2101::getBatVoltage() {
    float ADCLSB = 1.1 / 1000.0;
    return _I2C_read12Bit(0x78) * ADCLSB;
}

float AXP2101::getBatCurrent() {
    float ADCLSB = 0.5;
    uint16_t CurrentIn = _I2C_read13Bit(0x7A);
    uint16_t CurrentOut = _I2C_read13Bit(0x7C);
    return (CurrentIn - CurrentOut) * ADCLSB;
}

float AXP2101::getBatLevel() {
    const float batVoltage = getBatVoltage();
    const float batPercentage = (batVoltage < 3.248088) ? (0) : (batVoltage - 3.120712) * 100;       
    return (batPercentage <= 100) ? batPercentage : 100;    
}

float AXP2101::getBatPower() {
    float VoltageLSB = 1.1;
    float CurrentLCS = 0.5;
    uint32_t ReData = _I2C_read24Bit(0x70);
    return VoltageLSB * CurrentLCS * ReData / 1000.0;    
}

float AXP2101::getVBUSVoltage() {
    float ADCLSB = 1.7 / 1000.0;
    uint16_t ReData = _I2C_read12Bit(0x5A);
    return ReData * ADCLSB;
}

float AXP2101::getVBUSCurrent() {
    float ADCLSB = 0.375;
    uint16_t ReData = _I2C_read12Bit(0x5C);
    return ReData * ADCLSB;
}

float AXP2101::getAXP173Temp() {
    float ADCLSB = 0.1;
    const float OFFSET_DEG_C = -144.7;
    uint16_t ReData = _I2C_read12Bit(0x5E);
    return OFFSET_DEG_C + ReData * ADCLSB;
}

float AXP2101::getTSTemp() {
    float ADCLSB = 0.1;
    const float OFFSET_DEG_C = -144.7;
    uint16_t ReData = _I2C_read12Bit(0x62);
    return OFFSET_DEG_C + ReData * ADCLSB;
}