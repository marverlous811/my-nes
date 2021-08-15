//
// Created by Ows on 14/08/2021.
//

#ifndef NES_CLOUD_RAM_H
#define NES_CLOUD_RAM_H

#include "helper/buffer.h"

class Ram: public Memory {
public:
    Ram(uint32_t max_size);
    ~Ram();

public:
    void reset();
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool read_only);

    void printRam(uint16_t addr, int n_row, int n_column);

private:
    uint8_t *_data = nullptr;
    uint32_t _size;
};

#endif //NES_CLOUD_RAM_H
