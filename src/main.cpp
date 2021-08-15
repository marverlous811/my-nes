#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "nes/nes.h"
#include "nes/nes_const.h"
#include "helper/time_helper.h"

int main() {
    auto ram = new Ram(64*1024);
    auto cpu = new CPU(ram);

    ram->write(0xFF00, INS_JSR);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000, INS_RTS);
    ram->write(0xFF03, INS_LDA_IM);
    ram->write(0xFF04, 0x42);

    CPU clonedCpu = *cpu;
    cpu->request_exec(0xFF00, 6 + 6 + 2);
    return 0;
}
