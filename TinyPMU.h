#ifndef _TINYPMU_H_
#define _TINYPMU_H_

#ifdef ARDUINO
#include <Arduino.h>
#include "Wire.h"
#endif

/* TinyPMU ABC */
class TinyPMU {
    protected:
        /* PMU I2C address */
        uint8_t _PMU_addr;
    public:
        /* Port interface */
        virtual void    _I2C_init()       = 0;
        virtual void    _I2C_write1Byte() = 0;
        virtual uint8_t _I2C_read8Bit()  = 0;
        virtual void    _I2C_readBuff()   = 0;
        /* Baisc functions */
        virtual void begin();
};

#endif