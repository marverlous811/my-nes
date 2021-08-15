//
// Created by Ows on 14/08/2021.
//

#include <gtest/gtest.h>
#include "nes/nes_const.h"
#include "nes/ram.h"
#include "nes/cpu.h"
#include "helper/string_helper.h"

TEST(CPUBrachTests, BEQCanBranchForwardsWhenZeroIsSet) {
    auto ram = new Ram(64 * 1024);
    auto cpu = new CPU(ram);

    cpu->set_flag(CPU::Z, true);
    ram->write(0xFF00, INS_BEQ);
    ram->write(0xFF01, 0x1);

    cpu->exec(0xFF00);


    EXPECT_EQ(cpu->pc, 0xFF03);
}

TEST(CPUBrachTests, BEQDoesNotBranchForwardsWhenZeroIsNotSet) {
    auto ram = new Ram(64 * 1024);
    auto cpu = new CPU(ram);

    cpu->set_flag(CPU::Z, false);
    ram->write(0xFF00, INS_BEQ);
    ram->write(0xFF01, 0x1);

    cpu->exec(0xFF00);


    EXPECT_EQ(cpu->pc, 0xFF02);
}

TEST(CPUBrachTests, BEQCanBranchForwardsIntoANewPageWhenZeroIsSet) {
    auto ram = new Ram(64 * 1024);
    auto cpu = new CPU(ram);

    cpu->set_flag(CPU::Z, true);
    ram->write(0xFEFD, INS_BEQ);
    ram->write(0xFEFE, 0x1);

    cpu->exec(0xFEFD);


    EXPECT_EQ(cpu->pc, 0xFF00);
}

TEST(CPUBrachTests, BEQCanBranchBackwardsWhenZeroIsSet) {
    auto ram = new Ram(64 * 1024);
    auto cpu = new CPU(ram);

    cpu->set_flag(CPU::Z, true);
    ram->write(0xFFCC, INS_BEQ);
    ram->write(0xFFCD, -0x2);

    cpu->exec(0xFFCC);


    EXPECT_EQ(cpu->pc, 0xFFCC);
}

TEST(CPUBrachTests, BEQCanBranchBackwardsWhenZeroIsSetFromAssembleCode) {
    auto ram = new Ram(64 * 1024);
    auto cpu = new CPU(ram);
    int expected_cycles = 2 + 3;

    cpu->set_flag(CPU::Z, true);
    /*
	loop
	lda #0
	beq loop
	*/
    ram->write(0xFFCC, 0xA9);
    ram->write(0xFFCC + 1, 0x00);
    ram->write(0xFFCC + 2, 0xF0);
    ram->write(0xFFCC + 3, 0xFC);

    ram->printRam(0xFFCC, 2 ,2);
    cpu->request_exec(0xFFCC, expected_cycles);

    EXPECT_EQ(cpu->pc, 0xFFCC);
}

