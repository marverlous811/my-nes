//
// Created by Ows on 14/08/2021.
//

#ifndef NES_CLOUD_BUS_H
#define NES_CLOUD_BUS_H

#include <stdlib.h>
#include <array>

class Bus {
public:
    Bus();
    ~Bus();

public:
    uint8_t *ram;
public:
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool read_only = false);
};

#endif //NES_CLOUD_BUS_H
