//
// Created by Ows on 14/08/2021.
//

#include <stdio.h>
#include <string>
#include "helper/string_helper.h"
#include "nes/ram.h"

Ram::Ram(uint32_t max_size) {
    _size = max_size;
    if(max_size > 0xFFFF + 1) {
        _size = 0xFFFF + 1;
    }

    _data = (uint8_t*) malloc(sizeof (uint8_t) * max_size);
    for(uint32_t addr = 0; addr < _size; addr++) {
        _data[addr] = 0x00;
    }
}

Ram::~Ram() {
    _size = 0;
    free(_data);
}

uint8_t Ram::read(uint16_t addr, bool read_only) {
    if(addr >= 0x0000 && addr < _size){
        return _data[addr];
    }

    return 0x00;
}

void Ram::write(uint16_t addr, uint8_t data) {
    if(addr >= 0x0000 && addr < _size){
         _data[addr] = data;
    }
}

void Ram::reset() {
    for(uint32_t addr = 0; addr < _size; addr++) {
        _data[addr] = 0x00;
    }
}

void Ram::printRam(uint16_t addr, int n_row, int n_column) {
    for(int row = 0; row < n_row; row++){
        std::string offset = "$" + hex2str(addr, 4) +  ":";
        for(int column = 0; column < n_column; column++) {
            offset += " " + hex2str(this->read(addr, true), 2);
            addr++;
        }
        printf("%s\n", offset.c_str());
    }
}