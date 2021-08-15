//
// Created by Ows on 14/08/2021.
//

#include <stdio.h>
#include "nes/nes.h"
#include "helper/string_helper.h"

Nes::Nes() {
    cpuRam = new Ram(1024);
    cpu = new CPU(cpuRam);
}

Nes::~Nes() {}

void Nes::printCPU() {
    std::string status = "STATUS: ";
    printf("STATUS: ");
    printf(cpu->status & CPU::N ? GRN " N " RESET : RED " N " RESET);
    printf(cpu->status & CPU::V ? GRN " V " RESET : RED " V " RESET);
    printf(cpu->status & CPU::U ? GRN " - " RESET : RED " - " RESET);
    printf(cpu->status & CPU::B ? GRN " B " RESET : RED " B " RESET);
    printf(cpu->status & CPU::D ? GRN " D " RESET : RED " D " RESET);
    printf(cpu->status & CPU::I ? GRN " I " RESET : RED " I " RESET);
    printf(cpu->status & CPU::Z ? GRN " Z " RESET : RED " Z " RESET);
    printf(cpu->status & CPU::C ? GRN " C " RESET : RED " C " RESET);
    printf("\n");
    printf("PC: $%s\n", hex2str(cpu->pc, 4).c_str());
    printf("A: $%s [%s]\n", hex2str(cpu->a, 2).c_str(), std::to_string(cpu->a).c_str());
    printf("X: $%s [%s]\n", hex2str(cpu->x, 2).c_str(), std::to_string(cpu->x).c_str());
    printf("Y: $%s [%s]\n", hex2str(cpu->y, 2).c_str(), std::to_string(cpu->y).c_str());
    printf("Stack P: $%s\n", hex2str(cpu->stkp, 4).c_str());
}