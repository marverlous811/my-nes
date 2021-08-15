//
// Created by Ows on 14/08/2021.
//

#ifndef NES_CLOUD_BUFFER_H
#define NES_CLOUD_BUFFER_H

#include "stdlib.h"

class Memory {
public:
    virtual void write(uint16_t addr, uint8_t data) = 0;
    virtual uint8_t read(uint16_t addr, bool read_only) = 0;
};

#endif //NES_CLOUD_BUFFER_H
