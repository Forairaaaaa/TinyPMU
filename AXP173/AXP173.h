#ifndef _AXP173_H_
#define _AXP173_H_

#include "../I2C_PORT/I2C_PORT.h"

/* AXP173 device address */
#define AXP173_ADDR_READ    0x69
#define AXP173_ADDR_WRITE   0x68
#define AXP173_ADDR         0x34
// #define AXP173_ADDR         (AXP173_ADDR_WRITE >> 1)

class AXP173 : public I2C_PORT {
    private:
    public:
        /* AXP173 init */
        #ifdef ARDUINO
        bool begin(TwoWire * wire);
        #else
            void begin();
        #endif
        /* Power info */
        bool isACINExist();                                 /* 0x00 */
        bool isACINAvl();
        bool isVBUSExist();
        bool isVBUSAvl();
        bool getBatCDir();
        bool isAXP173OverTemp();                            /* 0x01 */
        bool isCharging();
        bool isBatExist();
        bool isChargeCsmaller();
        /* Power control */
        void setLDOEnable(uint8_t channel, bool state);     /* 0x12 */
        void setDCDC1Enable(bool state);
};      

#endif