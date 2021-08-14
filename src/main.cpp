#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "nes/nes.h"
#include "helper/time_helper.h"

int main() {
    Nes *nes = new Nes();
    std::stringstream ss;
    ss << "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
    uint16_t  offset = 0x8000;
    while(!ss.eof()){
        std::string b;
        ss >> b;
        nes->bus->ram[offset++] = (uint8_t)std::stoul(b, nullptr, 16);
    }

    nes->bus->ram[0xFFFC] = 0x00;
    nes->bus->ram[0xFFFD] = 0x80;

    nes->mapAsm = nes->cpu->disassemble(0x0000, 0xFFFF);
    nes->cpu->reset();

    while(!nes->cpu->complete()) {
        system("clear");
        delay_ms(1000);
        nes->cpu->clock();

        nes->printCPU();
        nes->printRam(0x0000, 16, 16);
        nes->printRam(0x8000, 16, 16);
    }
    return 0;
}
