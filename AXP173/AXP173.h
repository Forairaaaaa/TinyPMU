#ifndef _AXP173_H_
#define _AXP173_H_

#include "../I2C_PORT/I2C_PORT.h"


/* AXP173 device address */
#define AXP173_ADDR         0x34
#define AXP173_ADDR_READ    0x69
#define AXP173_ADDR_WRITE   0x68


class AXP173 : public I2C_PORT {
    private:
        uint16_t _getMin(uint16_t a, uint16_t b);
        uint16_t _getMax(uint16_t a, uint16_t b);
        uint16_t _getMid(uint16_t input, uint16_t min, uint16_t max);
    public:
        enum OUTPUT_CHANNEL {
            DCDC1 = 0,
            DCDC2,
            LDO2,
            LDO3,
            LDO4,
            ALL,
        };
        enum ADC_CHANNEL {
            TS = 0,
            APS_V,
            VBUS_C,
            VBUS_V,
            ACIN_C,
            ACIN_V,
            BAT_C,
            BAT_V,
        };
        enum CHARGE_CURRENT {
            CHG_100mA = 0,
            CHG_190mA,
            CHG_280mA,
            CHG_360mA,
            CHG_450mA,
            CHG_550mA,
            CHG_630mA,
            CHG_700mA,
            CHG_780mA,
            CHG_880mA,
            CHG_960mA,
            CHG_1000mA,
            CHG_1080mA,
            CHG_1160mA,
            CHG_1240mA,
            CHG_1320mA,
        };
        /* Init */
        #ifdef ARDUINO
        bool begin(TwoWire * wire);
        #else
            void begin();
        #endif
        /* Power input info */
        bool isACINExist();                                                 /* 0x00 */
        bool isACINAvl();
        bool isVBUSExist();
        bool isVBUSAvl();
        bool getBatCurrentDir();
        bool isAXP173OverTemp();                                            /* 0x01 */
        bool isCharging();
        bool isBatExist();
        bool isChargeCsmaller();
        /* Power output control */
        void setOutputEnable(OUTPUT_CHANNEL channel, bool state);           /* 0x12 */
        void setOutputVoltage(OUTPUT_CHANNEL channel, uint16_t voltage);    /* 0x23, 0x26, 0x27, 0x28 */
        /* Basic control */
        void powerOFF();
        /* Charge control */
        void setChargeEnable(bool state);
        void setChargeCurrent(CHARGE_CURRENT current);
        /* ADC control */
        void setADCEnable(ADC_CHANNEL channel, bool state);
};      

#endif