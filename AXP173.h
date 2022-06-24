#ifndef _AXP173_H_
#define _AXP173_H_

#include "TinyPMU.h"

/* Address map */
#define ADDR_AXP173 0x23


class AXP173 : public TinyPMU {
    private:
        #ifdef ARDUINO
            TwoWire * _wire;
        #endif

        /* Port interface */
        void    _I2C_init();
        void    _I2C_write1Byte(uint8_t addr, uint8_t data);
        uint8_t _I2C_read1Byte(uint8_t addr);
        void    _I2C_readBuff(uint8_t addr, uint8_t size, uint8_t * buff);
    public:
        #ifdef ARDUINO
            /* AXP173 init */
            void begin(TwoWire * wire);
        #else
            void begin();
        #endif
};      

#endif