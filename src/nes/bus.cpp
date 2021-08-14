//
// Created by Ows on 14/08/2021.
//

#include "nes/bus.h"

Bus::Bus() {
    this->ram = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
}

Bus::~Bus() {}

uint8_t Bus::read(uint16_t addr, bool read_only) {
    if(addr >= 0x0000 && addr <= 0xFFFF) {
        return this->ram[addr];
    }

    return 0x00;
}

void Bus::write(uint16_t addr, uint8_t data) {
    if(addr >= 0x0000 && addr <= 0xFFFF) {
        this->ram[addr] = data;
    }
}