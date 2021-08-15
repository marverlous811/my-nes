//
// Created by Ows on 14/08/2021.
//

#ifndef NES_CLOUD_NES_H
#define NES_CLOUD_NES_H

#include "nes/cpu.h"
#include "nes/ram.h"

class Nes {
public:
    Nes();
    ~Nes();

public:
    Ram *cpuRam = nullptr;
    CPU *cpu = nullptr;
    std::map<uint16_t, std::string> mapAsm;

public:
    //DEBUG function
    void printCPU();
    void printRam(uint16_t nAddr, int nRows, int nColumns);
};

#endif //NES_CLOUD_NES_H
