//
// Created by Ows on 15/08/2021.
//

#include <gtest/gtest.h>
#include "nes/cpu.h"
#include "nes/ram.h"
#include "nes/nes_const.h"


class CPUIncrementDecrementTest : public testing::Test {
public:
    CPU* cpu;
    Ram* ram;

    virtual void SetUp(){
        ram = new Ram(64*1024);
        cpu = new CPU(ram);
    }

    virtual void TearDown(){ }
    void ExpectUnaffectedFlags(CPU before) {
        EXPECT_EQ(cpu->get_flag(CPU::C), before.get_flag(CPU::C));
        EXPECT_EQ(cpu->get_flag(CPU::I), before.get_flag(CPU::I));
        EXPECT_EQ(cpu->get_flag(CPU::D), before.get_flag(CPU::D));
        EXPECT_EQ(cpu->get_flag(CPU::B), before.get_flag(CPU::B));
        EXPECT_EQ(cpu->get_flag(CPU::V), before.get_flag(CPU::V));
    }
};

TEST_F(CPUIncrementDecrementTest, INXCanIncrementAZeroValue) {
    cpu->x = 0x0;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_INX);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->x, 0x1);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INXCanIncrement255) {
    cpu->x = 0xFF;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_INX);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->x, 0x0);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_TRUE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INXCanIncrementANegativeValue) {
    cpu->x = 0b10001000;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_INX);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->x, 0b10001001);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INYCanIncrementAZeroValue) {
    cpu->y = 0x0;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_INY);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->y, 0x1);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INYCanIncrement255) {
    cpu->y = 0xFF;
    cpu->set_flag(CPU::Z, false);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_INY);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->y, 0x0);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_TRUE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INYCanIncrementANegativeValue) {
    cpu->y = 0b10001000;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_INY);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->y, 0b10001001);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DEYCanDecrementAZeroValue) {
    cpu->y  = 0x00;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_DEY);
    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->y, 0xFF);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DEYCanDecrement255) {
    cpu->y  = 0xFF;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_DEY);
    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->y, 0xFE);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DEYCanDecrementANegativeValue) {
    cpu->y  = 0b10001001;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_DEY);
    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->y, 0b10001000);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DEXCanDecrementAZeroValue) {
    cpu->x  = 0x00;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_DEX);
    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->x, 0xFF);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DEXCanDecrement255) {
    cpu->x  = 0xFF;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_DEX);
    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->x, 0xFE);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DEXCanDecrementANegativeValue) {
    cpu->x  = 0b10001001;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, false);

    ram->write(0xFF00, INS_DEX);
    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);

    EXPECT_EQ(cpu->x, 0b10001000);
    EXPECT_EQ(cpu->get_clock_count(), 2);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_TRUE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DECCanDecrementAValueInTheZeroPage) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);
    ram->write(0xFF00, INS_DEC_ZP);
    ram->write(0xFF01, 0x42);
    ram->write(0x0042, 0x57);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x0042, true), 0x56);
    EXPECT_EQ(cpu->get_clock_count(), 5);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DECCanDecrementAValueInTheZeroPageX) {
    cpu->x = 0x10;
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);
    ram->write(0xFF00, INS_DEC_ZPX);
    ram->write(0xFF01, 0x42);
    ram->write(0x0042 + 0x10, 0x57);

    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x0042 + 0x10, true), 0x56);
    EXPECT_EQ(cpu->get_clock_count(), 6);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DECCanDecrementAValueAbsolute) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_DEC_ABS);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000, 0x57);


    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x8000, true), 0x56);
    EXPECT_EQ(cpu->get_clock_count(), 6);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, DECCanDecrementAValueAbsoluteX) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);
    cpu->x = 0x10;

    ram->write(0xFF00, INS_DEC_ABSX);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000 + 0x10, 0x57);


    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x8000 + 0x10, true), 0x56);
    EXPECT_EQ(cpu->get_clock_count(), 7);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INCCanIncrementAValueInTheZeroPage) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_INC_ZP);
    ram->write(0xFF01, 0x42);
    ram->write(0x0042, 0x57);


    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x0042, true), 0x58);
    EXPECT_EQ(cpu->get_clock_count(), 5);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INCCanIncrementAValueInTheZeroPageX) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);
    cpu->x = 0x10;

    ram->write(0xFF00, INS_INC_ZPX);
    ram->write(0xFF01, 0x42);
    ram->write(0x0042 + 0x10, 0x57);


    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x0042 + 0x10, true), 0x58);
    EXPECT_EQ(cpu->get_clock_count(), 6);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INCCanIncrementAValueAbsolute) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);

    ram->write(0xFF00, INS_INC_ABS);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000, 0x57);


    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x8000, true), 0x58);
    EXPECT_EQ(cpu->get_clock_count(), 6);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}

TEST_F(CPUIncrementDecrementTest, INCCanIncrementAValueAbsoluteX) {
    cpu->set_flag(CPU::Z, true);
    cpu->set_flag(CPU::N, true);
    cpu->x = 0x10;

    ram->write(0xFF00, INS_INC_ABSX);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000 + 0x10, 0x57);


    CPU clonedCpu = *cpu;

    cpu->exec(0xFF00);
    EXPECT_EQ(ram->read(0x8000 + 0x10, true), 0x58);
    EXPECT_EQ(cpu->get_clock_count(), 7);
    EXPECT_FALSE(cpu->get_flag(CPU::Z));
    EXPECT_FALSE(cpu->get_flag(CPU::N));
    ExpectUnaffectedFlags(clonedCpu);
}