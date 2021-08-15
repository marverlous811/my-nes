//
// Created by Ows on 15/08/2021.
//

#include <gtest/gtest.h>
#include "nes/cpu.h"
#include "nes/ram.h"
#include "nes/nes_const.h"

TEST(CPUJumpsAndCallTest, CanJumpToASubroutineAndJumpBackAgain) {
    auto ram = new Ram(64*1024);
    auto cpu = new CPU(ram);

    ram->write(0xFF00, INS_JSR);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000, INS_RTS);
    ram->write(0xFF03, INS_LDA_IM);
    ram->write(0xFF04, 0x42);
    int expected_cycles = 6 + 6 + 2;

    CPU clonedCpu = *cpu;
    cpu->request_exec(0xFF00, expected_cycles);

    EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
    EXPECT_EQ(cpu->a, 0x42);
}

TEST(CPUJumpsAndCallTest, JSRDoesNotAffectTheProcessorStatus) {
    auto ram = new Ram(64*1024);
    auto cpu = new CPU(ram);

    ram->write(0xFF00, INS_JSR);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    int expected_cycles = 6;

    CPU clonedCpu = *cpu;
    cpu->request_exec(0xFF00, expected_cycles);

    EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
    EXPECT_EQ(cpu->pc, 0x8000);
}

TEST(CPUJumpsAndCallTest, RTSDoesNotAffectTheProcessorStatus) {
    auto ram = new Ram(64*1024);
    auto cpu = new CPU(ram);

    ram->write(0xFF00, INS_JSR);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000, INS_RTS);
    int expected_cycles = 6 + 6;

    CPU clonedCpu = *cpu;
    cpu->request_exec(0xFF00, expected_cycles);

    EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
    EXPECT_EQ(cpu->pc, 0xFF03);
}

TEST(CPUJumpsAndCallTest, JumpAbsoluteCanJumpToAnNewLocationInTheProgram) {
    auto ram = new Ram(64*1024);
    auto cpu = new CPU(ram);

    ram->write(0xFF00, INS_JSR);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    int expected_cycles = 3;

    CPU clonedCpu = *cpu;
    cpu->request_exec(0xFF00, expected_cycles);

    EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
    EXPECT_EQ(cpu->pc, 0x8000);
}

TEST(CPUJumpsAndCallTest, JumpIndirectCanJumpToAnNewLocationInTheProgram) {
    auto ram = new Ram(64*1024);
    auto cpu = new CPU(ram);

    ram->write(0xFF00, INS_JMP_IND);
    ram->write(0xFF01, 0x00);
    ram->write(0xFF02, 0x80);
    ram->write(0x8000, 0x00);
    ram->write(0x8001, 0x90);
    int expected_cycles = 5;

    CPU clonedCpu = *cpu;
    cpu->request_exec(0xFF00, expected_cycles);

    EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
    EXPECT_EQ(cpu->pc, 0x9000);
}