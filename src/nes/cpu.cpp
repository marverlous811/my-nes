//
// Created by Ows on 14/08/2021.
//

#include "nes/cpu.h"
#include "helper/string_helper.h"

CPU::CPU(Memory *ram) {
    this->ram = ram;
    using a = CPU;
    lookup =
    {
        { "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
        { "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
        { "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
        { "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
        { "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
        { "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
        { "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
    };
}

CPU::~CPU() {

}

void CPU::write(uint16_t address, uint8_t d) {
    ram->write(address, d);
}

uint8_t CPU::read(uint16_t address) {
    return ram->read(address, false);
}

uint8_t CPU::get_flag(FLAG f) {
    return ((status & f) > 0 ) ? 1 : 0;
}

void CPU::set_flag(FLAG f, bool v) {
    if(v) {
        status |= f;
        return;
    }

    status &= ~f;
}

void CPU::clock() {
    if(cycles == 0) {
        opcode = read(pc);
        set_flag(U, true);
        auto instruction = lookup[opcode];
//        printf("pc: %s, operate: %s, \n", hex2str(pc, 4).c_str(), instruction.name.c_str());
        pc++;

        // get starting number of cyles
        cycles = lookup[opcode].cycles;
        uint8_t additional_cycles_1 = (this->*lookup[opcode].addrmode)();
        uint8_t additional_cycles_2 = (this->*lookup[opcode].operate)();

        cycles += (additional_cycles_1 & additional_cycles_2);

        set_flag(U, true);
    }

    clock_count++;
    cycles--;
}

void CPU::reset() {
    a = 0;
    x = 0;
    y = 0;
    stkp = 0xFD;
    status = 0x00 | U;

    addr_abs = 0xFFFC;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);

    pc = (hi << 8) | lo;
    addr_rel = 0x0000;
    addr_abs = 0x0000;
    fetched = 0x00;
    cycles = 8;
}

void CPU::irq() {
    if(get_flag(I) == 0) {
        write(0x0100 + stkp, (pc >> 8) & 0x00FF);
        stkp--;
        write(0x0100 + stkp, pc & 0x00FF);
        stkp--;

        set_flag(B, 0);
        set_flag(U, 1);
        set_flag(I, 1);
        write(0x0100 + stkp, status);
        stkp--;

        addr_abs = 0xFFFE;
        uint16_t lo = read(addr_abs + 0);
        uint16_t hi = read(addr_abs + 1);
        pc = (hi << 8) | lo;

        cycles = 7;
    }
}

void CPU::nmi() {
    write(0x0100 + stkp, (pc >> 8) & 0x00FF);
    stkp--;
    write(0x0100 + stkp, pc & 0x00FF);
    stkp--;

    set_flag(B, 0);
    set_flag(U, 1);
    set_flag(I, 1);
    write(0x0100 + stkp, status);
    stkp--;

    addr_abs = 0xFFFA;
    uint16_t lo = read(addr_abs + 0);
    uint16_t hi = read(addr_abs + 1);
    pc = (hi << 8) | lo;

    cycles = 8;
}

/**
 * ADDRESSING MODE
 */
uint8_t CPU::IMP() {
    fetched = a;
    return 0;
}

uint8_t CPU::IMM() {
    addr_abs = pc++;
    return 0;
}

uint8_t CPU::ZP0() {
    addr_abs = read(pc);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ZPX() {
    addr_abs = (read(pc) + x);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::ZPY() {
    addr_abs = (read(pc) + y);
    pc++;
    addr_abs &= 0x00FF;
    return 0;
}

uint8_t CPU::REL() {
    addr_rel = read(pc);
    pc++;
    if(addr_rel & 0x80)
        addr_rel |= 0xFF00;

    return 0;
}

uint8_t CPU::ABS() {
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    return 0;
}

uint8_t CPU::ABX() {
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    addr_abs += x;

    if((addr_abs & 0xFF00) != (hi << 8)) {
        return 1;
    }
    return 0;
}

uint8_t CPU::ABY() {
    uint16_t lo = read(pc);
    pc++;
    uint16_t hi = read(pc);
    pc++;

    addr_abs = (hi << 8) | lo;
    addr_abs += y;

    if((addr_abs & 0xFF00) != (hi << 8)) {
        return 1;
    }
    return 0;
}

uint8_t CPU::IND() {
    uint16_t ptr_lo = read(pc);
    pc++;
    uint16_t ptr_hi = read(pc);
    pc++;

    uint16_t  ptr = (ptr_hi << 8) | ptr_lo;
    if(ptr_lo == 0x00FF) // simulate page boundary handware bug
    {
        addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
    } else { // normally
        addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
    }

    return 0;
}

uint8_t CPU::IZX() {
    uint16_t t = read(pc);
    pc++;

    uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
    uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

    addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t CPU::IZY() {
    uint16_t t = read(pc);
    pc++;

    uint16_t lo = read((uint16_t)(t) & 0x00FF);
    uint16_t hi = read((uint16_t)(t+1) & 0x00FF);

    addr_abs = (hi << 8) | lo;
    addr_abs += y;

    if((addr_abs & 0xFF00) != (hi << 8)){
        return 1;
    }
    return 0;
}

/**
 * Instructions
 */
uint8_t CPU::fetch() {
    if(!(lookup[opcode].addrmode == &CPU::IMP))
        fetched = read(addr_abs);
    return fetched;
}

uint8_t CPU::AND() {
    fetch();
    a = a & fetched;
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 1;
}

uint8_t CPU::BCS() {
    if(get_flag(C) == 0) {
        cycles++;
        addr_abs = pc + addr_rel;

        if((addr_abs & 0xFF00) != (pc & 0xFF00)) cycles++;
        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BCC() {
    if(get_flag(C) == 1) {
        cycles++;
        addr_abs = pc + addr_rel;

        if((addr_abs & 0xFF00) != (pc & 0xFF00)) cycles++;
        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BEQ() {
    if (get_flag(Z) == 1)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BMI() {
    if (get_flag(N) == 1)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BNE() {
    if (get_flag(Z) == 0)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BPL() {
    if (get_flag(N) == 1)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BVC() {
    if (get_flag(V) == 0)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::BVS() {
    if (get_flag(V) == 1)
    {
        cycles++;
        addr_abs = pc + addr_rel;

        if ((addr_abs & 0xFF00) != (pc & 0xFF00))
            cycles++;

        pc = addr_abs;
    }
    return 0;
}

uint8_t CPU::CLC() {
    set_flag(C, false);
    return 0;
}

uint8_t CPU::CLD() {
    set_flag(D, false);
    return 0;
}

uint8_t CPU::ADC() {
    fetch();
    uint16_t  temp = (uint16_t)a + (uint16_t)fetched + (uint16_t) get_flag(C);
    set_flag(C, temp > 255);
    set_flag(Z, (temp & 0x00FF) == 0);
    set_flag(N, temp & 0x80);
    set_flag(V, (~((uint16_t) a ^ (uint16_t) fetched) & ((uint16_t)a ^ (uint16_t)fetched)) & 0x0080);

    a = temp & 0x00FF;
    return 1;
}

uint8_t CPU::SBC() {
    fetch();

    uint16_t  value = ((uint16_t)fetched ) ^ 0x00FF;

    uint16_t  temp = (uint16_t)a + (uint16_t)value + (uint16_t) get_flag(C);
    set_flag(C, temp > 255);
    set_flag(Z, (temp & 0x00FF) == 0);
    set_flag(N, temp & 0x80);
    set_flag(V, (~((uint16_t) a ^ (uint16_t) fetched) & ((uint16_t)a ^ (uint16_t)fetched)) & 0x0080);

    a = temp & 0x00FF;
    return 1;
}

uint8_t CPU::PHA() {
    write(0x0100 + stkp, a);
    stkp--;
    return 0;
}

uint8_t CPU::PLA() {
    stkp++;
    a = read(0x0100 + stkp);
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 0;
}

uint8_t CPU::RTI() {
    stkp++;
    status = read(0x0100 + stkp);
    status &= ~B;
    status &= ~U;

    stkp++;
    pc = (uint16_t) read(0x0100 + stkp);
    stkp++;
    pc |= (uint16_t) read(0x0100 + stkp) << 8;
    return 0;
}

uint8_t CPU::ASL() {
    fetch();
    temp = (uint16_t)fetched << 1;
    set_flag(C, (temp & 0xFF00) > 0);
    set_flag(Z, (temp & 0x00FF) == 0x00);
    set_flag(N, temp & 0x80);
    if (lookup[opcode].addrmode == &CPU::IMP)
        a = temp & 0x00FF;
    else
        write(addr_abs, temp & 0x00FF);
    return 0;
}

uint8_t CPU::BIT()
{
    fetch();
    temp = a & fetched;
    set_flag(Z, (temp & 0x00FF) == 0x00);
    set_flag(N, fetched & (1 << 7));
    set_flag(V, fetched & (1 << 6));
    return 0;
}

uint8_t CPU::BRK()
{
    pc++;

    set_flag(I, 1);
    write(0x0100 + stkp, (pc >> 8) & 0x00FF);
    stkp--;
    write(0x0100 + stkp, pc & 0x00FF);
    stkp--;

    set_flag(B, 1);
    write(0x0100 + stkp, status);
    stkp--;
    set_flag(B, 0);

    pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
    return 0;
}

uint8_t CPU::CLI() {
    set_flag(I, false);
    return 0;
}

uint8_t CPU::CLV() {
    set_flag(V, false);
    return 0;
}

uint8_t CPU::CMP() {
    fetch();
    temp = (uint16_t)a - (uint16_t)fetched;
    set_flag(C, a >= fetched);
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    return 1;
}

uint8_t CPU::CPX() {
    fetch();
    temp = (uint16_t)x - (uint16_t)fetched;
    set_flag(C, x >= fetched);
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    return 0;
}

uint8_t CPU::CPY() {
    fetch();
    temp = (uint16_t)y - (uint16_t)fetched;
    set_flag(C, y >= fetched);
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    return 0;
}

uint8_t CPU::DEC()
{
    fetch();
    temp = fetched - 1;
    write(addr_abs, temp & 0x00FF);
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    return 0;
}

uint8_t CPU::DEX() {
    x--;
    set_flag(Z, x == 0x00);
    set_flag(N, x & 0x80);
    return 0;
}

uint8_t CPU::DEY() {
    y--;
    set_flag(Z, y == 0x00);
    set_flag(N, y & 0x80);
    return 0;
}

uint8_t CPU::EOR() {
    fetch();
    a = a ^ fetched;
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 1;
}

uint8_t CPU::INC() {
    fetch();
    temp = fetched + 1;
    write(addr_abs, temp & 0x00FF);
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    return 0;
}

uint8_t CPU::INX() {
    x++;
    set_flag(Z, x == 0x00);
    set_flag(N, x & 0x80);
    return 0;
}

uint8_t CPU::INY() {
    y++;
    set_flag(Z, y == 0x00);
    set_flag(N, y & 0x80);
    return 0;
}

uint8_t CPU::JMP() {
    pc = addr_abs;
    return 0;
}

uint8_t CPU::JSR() {
    pc--;
    write(0x0100 + stkp, (pc >> 8) & 0x00FF);
    stkp--;
    write(0x0100 + stkp, pc & 0x00FF);
    stkp--;

    pc = addr_abs;
    return 0;
}

uint8_t CPU::LDA() {
    fetch();
    a = fetched;
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 1;
}

uint8_t CPU::LDX() {
    fetch();
    x = fetched;
    set_flag(Z, x == 0x00);
    set_flag(N, x & 0x80);
    return 1;
}

uint8_t CPU::LDY() {
    fetch();
    y = fetched;
    set_flag(Z, y == 0x00);
    set_flag(N, y & 0x80);
    return 1;
}

uint8_t CPU::LSR() {
    fetch();
    set_flag(C, fetched & 0x0001);
    temp = fetched >> 1;
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    if(lookup[opcode].addrmode == &CPU::IMP) {
        a = temp & 0x00FF;
    } else {
        write(addr_abs, temp & 0x00FF);
    }
    return 0;
}

uint8_t CPU::NOP() {
    switch (opcode) {
        case 0x1C:
        case 0x3C:
        case 0x5C:
        case 0x7C:
        case 0xDC:
        case 0xFC:
            return 1;
        default: return 0;
    }
}

uint8_t CPU::ORA() {
    fetch();
    a = a | fetched;
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 1;
}

uint8_t CPU::PHP() {
    write(0x0100 + stkp, status | B | U);
    set_flag(B, 0);
    set_flag(U, 0);
    stkp--;
    return 0;
}

uint8_t CPU::PLP() {
    stkp++;
    status = read(0x0100 + stkp);
    set_flag(U, 1);
    return  0;
}

uint8_t CPU::ROL() {
    fetch();
    temp = (uint16_t)(fetched << 1) | get_flag(C);
    set_flag(C, temp & 0xFF00);
    set_flag(Z, (temp & 0x00FF) == 0x0000);
    set_flag(N, temp & 0x0080);
    if(lookup[opcode].addrmode == &CPU::IMP) {
        a = temp & 0x00FF;
    } else {
        write(addr_abs, temp & 0x00FF);
    }
    return 0;
}

uint8_t CPU::ROR() {
    fetch();
    temp = (uint16_t)(get_flag(C) << 7) | (fetched >> 1);
    set_flag(C, fetched & 0x01);
    set_flag(Z, (temp & 0x00FF) == 0x00);
    set_flag(N, temp & 0x0080);
    if (lookup[opcode].addrmode == &CPU::IMP)
        a = temp & 0x00FF;
    else
        write(addr_abs, temp & 0x00FF);
    return 0;
}

uint8_t CPU::RTS() {
    stkp++;
    pc = (uint16_t) read(0x0100 + stkp);
    stkp++;
    pc |= (uint16_t)read (0x0100 + stkp) << 8;
    pc++;
    return 0;
}

uint8_t CPU::SEC() {
    set_flag(C, true);
    return 0;
}

uint8_t CPU::SEI() {
    set_flag(I, true);
    return 0;
}

uint8_t CPU::SED() {
    set_flag(D, true);
    return 0;
}

uint8_t CPU::STA() {
    write(addr_abs, a);
    return 0;
}

uint8_t CPU::STY() {
    write(addr_abs, y);
    return 0;
}

uint8_t CPU::STX() {
    write(addr_abs, x);
    return 0;
}

uint8_t CPU::TAX() {
    x = a;
    set_flag(Z, x == 0x00);
    set_flag(N, x & 0x80);
    return 0;
}

uint8_t CPU::TAY() {
    y = a;
    set_flag(Z, y == 0x00);
    set_flag(N, y & 0x80);
    return 0;
}

uint8_t CPU::TSX() {
    x = stkp;
    set_flag(Z, x == 0x00);
    set_flag(N, x & 0x80);
    return 0;
}

uint8_t CPU::TXA() {
    a = x;
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 0;
}

uint8_t CPU::TXS() {
    stkp = x;
    return 0;
}

uint8_t CPU::TYA() {
    a = y;
    set_flag(Z, a == 0x00);
    set_flag(N, a & 0x80);
    return 0;
}

uint8_t CPU::XXX() {
    return 0;
}

// Helper
void CPU::exec(uint16_t from) {
    pc = from;
    do {
//        printf("cycles %d\n", cycles);
        this->clock();
    } while (!this->complete());
}

void CPU::request_exec(uint16_t from, uint8_t req_cycle){
    pc = from;
    do {
//        printf("cycles %d, clock: clock_count: %d\n", cycles, clock_count);
        this->clock();
    } while ((clock_count - req_cycle) != 0);
}

bool CPU::complete() {
    return cycles == 0;
}

void CPU::printfStatus() {
    printf("STATUS: ");
    printf(this->status & CPU::N ? GRN " N " RESET : RED " N " RESET);
    printf(this->status & CPU::V ? GRN " V " RESET : RED " V " RESET);
    printf(this->status & CPU::U ? GRN " - " RESET : RED " - " RESET);
    printf(this->status & CPU::B ? GRN " B " RESET : RED " B " RESET);
    printf(this->status & CPU::D ? GRN " D " RESET : RED " D " RESET);
    printf(this->status & CPU::I ? GRN " I " RESET : RED " I " RESET);
    printf(this->status & CPU::Z ? GRN " Z " RESET : RED " Z " RESET);
    printf(this->status & CPU::C ? GRN " C " RESET : RED " C " RESET);
    printf("\n");
    printf("PC: $%s\n", hex2str(this->pc, 4).c_str());
    printf("A: $%s [%s]\n", hex2str(this->a, 2).c_str(), std::to_string(this->a).c_str());
    printf("X: $%s [%s]\n", hex2str(this->x, 2).c_str(), std::to_string(this->x).c_str());
    printf("Y: $%s [%s]\n", hex2str(this->y, 2).c_str(), std::to_string(this->y).c_str());
    printf("Stack P: $%s\n", hex2str(this->stkp, 4).c_str());
}

std::map<uint16_t, std::string> CPU::disassemble(uint16_t n_start, uint16_t n_stop) {
    uint32_t  addr = n_start;
    uint8_t  value = 0x00, lo = 0x00, hi = 0x00;
    std::map<uint16_t, std::string> map_line;
    uint16_t line_addr = 0;

    while(addr <= (uint32_t)n_stop) {
        line_addr = addr;
        std::string  sInst = "$" + hex2str(addr, 4) + ": ";

        uint8_t opcode = ram->read(addr, true); addr++;
        sInst += lookup[opcode].name + " ";
        if (lookup[opcode].addrmode == &CPU::IMP)
        {
            sInst += " {IMP}";
        }
        else if (lookup[opcode].addrmode == &CPU::IMM)
        {
            value = ram->read(addr, true); addr++;
            sInst += "#$" + hex2str(value, 2) + " {IMM}";
        }
        else if (lookup[opcode].addrmode == &CPU::ZP0)
        {
            lo = ram->read(addr, true); addr++;
            hi = 0x00;
            sInst += "$" + hex2str(lo, 2) + " {ZP0}";
        }
        else if (lookup[opcode].addrmode == &CPU::ZPX)
        {
            lo = ram->read(addr, true); addr++;
            hi = 0x00;
            sInst += "$" + hex2str(lo, 2) + ", X {ZPX}";
        }
        else if (lookup[opcode].addrmode == &CPU::ZPY)
        {
            lo = ram->read(addr, true); addr++;
            hi = 0x00;
            sInst += "$" + hex2str(lo, 2) + ", Y {ZPY}";
        }
        else if (lookup[opcode].addrmode == &CPU::IZX)
        {
            lo = ram->read(addr, true); addr++;
            hi = 0x00;
            sInst += "($" + hex2str(lo, 2) + ", X) {IZX}";
        }
        else if (lookup[opcode].addrmode == &CPU::IZY)
        {
            lo = ram->read(addr, true); addr++;
            hi = 0x00;
            sInst += "($" + hex2str(lo, 2) + "), Y {IZY}";
        }
        else if (lookup[opcode].addrmode == &CPU::ABS)
        {
            lo = ram->read(addr, true); addr++;
            hi = ram->read(addr, true); addr++;
            sInst += "$" + hex2str((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
        }
        else if (lookup[opcode].addrmode == &CPU::ABX)
        {
            lo = ram->read(addr, true); addr++;
            hi = ram->read(addr, true); addr++;
            sInst += "$" + hex2str((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
        }
        else if (lookup[opcode].addrmode == &CPU::ABY)
        {
            lo = ram->read(addr, true); addr++;
            hi = ram->read(addr, true); addr++;
            sInst += "$" + hex2str((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
        }
        else if (lookup[opcode].addrmode == &CPU::IND)
        {
            lo = ram->read(addr, true); addr++;
            hi = ram->read(addr, true); addr++;
            sInst += "($" + hex2str((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
        }
        else if (lookup[opcode].addrmode == &CPU::REL)
        {
            value = ram->read(addr, true); addr++;
            sInst += "$" + hex2str(value, 2) + " [$" + hex2str(addr + value, 4) + "] {REL}";
        }
    }

    return map_line;
}