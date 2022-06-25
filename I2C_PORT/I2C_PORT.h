#ifndef _I2C_PORT_H_
#define _I2C_PORT_H_

#ifdef ARDUINO
#include <Arduino.h>
#include "Wire.h"
#endif

/* I2C_PORT ABC */
class I2C_PORT {
    private:
        uint8_t _dev_addr;
        #ifdef ARDUINO
        TwoWire * _wire;
        #endif
    protected:
        /* Port interface */
        #ifdef ARDUINO
        void    _I2C_init(TwoWire * wire, uint8_t dev_addr);
        bool    _I2C_checkDevAvl();
        #else
        void    _I2C_init(uint8_t dev_addr);
        void    _I2C_checkDevAvl();
        #endif
        void    _I2C_write1Byte(uint8_t addr, uint8_t data);
        uint8_t _I2C_read8Bit(uint8_t addr);
        void    _I2C_readBuff(uint8_t addr, int size, uint8_t buff[]);
};

#endif