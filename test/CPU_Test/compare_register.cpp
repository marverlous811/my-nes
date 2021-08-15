//
// Created by Ows on 15/08/2021.
//

#include <gtest/gtest.h>
#include "nes/cpu.h"
#include "nes/ram.h"
#include "nes/nes_const.h"

class CPUCompareRegisterTest : public testing::Test {
public:
    CPU *cpu;
    Ram *ram;

    virtual void SetUp(){
        ram = new Ram(64*1024);
        cpu = new CPU(ram);
    }

    virtual void TearDown(){ }

    void ExpectUnaffectedRegisters(CPU before) {
        EXPECT_EQ(cpu->get_flag(CPU::I), before.get_flag(CPU::I));
        EXPECT_EQ(cpu->get_flag(CPU::D), before.get_flag(CPU::D));
        EXPECT_EQ(cpu->get_flag(CPU::B), before.get_flag(CPU::B));
        EXPECT_EQ(cpu->get_flag(CPU::V), before.get_flag(CPU::V));
    }

    enum Register {
        A, X, Y
    };

    struct TestData {
        uint8_t register_value;
        uint8_t operand;

        bool expect_c;
        bool expect_z;
        bool expect_n;
    };

    TestData CompareTwoIdenticalValues(){
        TestData retval;
        retval.register_value = 26;
        retval.operand = 26;
        retval.expect_z = true;
        retval.expect_n = false;
        retval.expect_c = true;
        return retval;
    }

    TestData CompareALargePositiveToASmallPositive(){
        TestData retval;
        retval.register_value = 48;
        retval.operand = 26;
        retval.expect_z = false;
        retval.expect_n = false;
        retval.expect_c = true;
        return retval;
    }

    TestData CompareANegativeNumberToAPositive(){
        TestData retval;
        retval.register_value = 130;
        retval.operand = 26;
        retval.expect_z = false;
        retval.expect_n = false;
        retval.expect_c = true;
        return retval;
    }

    TestData CompareTwoValuesThatResultInANegativeFlagSet(){
        TestData retval;
        retval.register_value = 8;
        retval.operand = 26;
        retval.expect_z = false;
        retval.expect_n = true;
        retval.expect_c = false;
        return retval;
    }

    void CompareImmediate(TestData data, Register _register2Compare) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        uint8_t* _register = &cpu->a;
        uint8_t opcode = INS_CMP;
        switch (_register2Compare) {
            case Register::X:
                _register = &cpu->x;
                opcode = INS_CPX;
                break;
            case Register::Y:
                _register = &cpu->y;
                opcode = INS_CPY;
                break;
        }

        *_register = data.register_value;

        ram->write(0xFF00, opcode);
        ram->write(0xFF01, data.operand);
        int expected_cycles = 2;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(*_register, data.register_value);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }

    void CompareZeroPage(TestData data, Register _register2Compare) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        uint8_t* _register = &cpu->a;
        uint8_t opcode = INS_CMP_ZP;
        switch (_register2Compare) {
            case Register::X:
                _register = &cpu->x;
                opcode = INS_CPX_ZP;
                break;
            case Register::Y:
                _register = &cpu->y;
                opcode = INS_CPY_ZP;
                break;
        }

        *_register = data.register_value;

        ram->write(0xFF00, opcode);
        ram->write(0xFF01, 0x42);
        ram->write(0x0042, data.operand);
        int expected_cycles = 3;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(*_register, data.register_value);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }

    void CompareAbsolute(TestData data, Register _register2Compare) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        uint8_t* _register = &cpu->a;
        uint8_t opcode = INS_CMP_ABS;
        switch (_register2Compare) {
            case Register::X:
                _register = &cpu->x;
                opcode = INS_CPX_ABS;
                break;
            case Register::Y:
                _register = &cpu->y;
                opcode = INS_CPY_ABS;
                break;
        }

        *_register = data.register_value;

        ram->write(0xFF00, opcode);
        ram->write(0xFF01, 0x00);
        ram->write(0xFF02, 0x80);
        ram->write(0x8000, data.operand);
        int expected_cycles = 4;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(*_register, data.register_value);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }

    void CMPAbsoluteX(TestData data) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        cpu->a = data.register_value;
        cpu->x = 4;

        ram->write(0xFF00, INS_CMP_ABSX);
        ram->write(0xFF01, 0x00);
        ram->write(0xFF02, 0x80);
        ram->write(0x8000 + 4, data.operand);

        int expected_cycles = 4;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(cpu->a, data.register_value);
        EXPECT_EQ(cpu->x , 4);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }

    void CMPAbsoluteY(TestData data) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        cpu->a = data.register_value;
        cpu->y = 4;

        ram->write(0xFF00, INS_CMP_ABSY);
        ram->write(0xFF01, 0x00);
        ram->write(0xFF02, 0x80);
        ram->write(0x8000 + 4, data.operand);

        int expected_cycles = 4;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(cpu->a, data.register_value);
        EXPECT_EQ(cpu->y , 4);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }

    void CMPIndirectX(TestData data) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        cpu->a = data.register_value;
        cpu->x = 4;

        ram->write(0xFF00, INS_CMP_INDX);
        ram->write(0xFF01, 0x42);
        ram->write(0x42+4, 0x00);
        ram->write(0x42+5, 0x80);
        ram->write(0x8000, data.operand);

        int expected_cycles = 6;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(cpu->a, data.register_value);
        EXPECT_EQ(cpu->x , 4);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }

    void CMPIndirectY(TestData data) {
        cpu->set_flag(CPU::C, !data.expect_c);
        cpu->set_flag(CPU::Z, !data.expect_z);
        cpu->set_flag(CPU::N, !data.expect_n);
        cpu->a = data.register_value;
        cpu->y = 4;

        ram->write(0xFF00, INS_CMP_INDY);
        ram->write(0xFF01, 0x42);
        ram->write(0x42, 0x00);
        ram->write(0x43, 0x80);
        ram->write(0x8000 + 4, data.operand);

        int expected_cycles = 5;
        CPU clonedCpu = *cpu;

        cpu->request_exec(0xFF00, expected_cycles);

        EXPECT_EQ(cpu->get_clock_count(), expected_cycles);
        EXPECT_EQ(cpu->a, data.register_value);
        EXPECT_EQ(cpu->y , 4);
        EXPECT_EQ(cpu->get_flag(CPU::Z), data.expect_z);
        EXPECT_EQ(cpu->get_flag(CPU::N), data.expect_n);
        EXPECT_EQ(cpu->get_flag(CPU::C), data.expect_c);
        ExpectUnaffectedRegisters(clonedCpu);
    }
};

TEST_F( CPUCompareRegisterTest, CMPImmediateCanCompareTwoIdenticalValues  )
{
    auto Test = CompareTwoIdenticalValues();
    CompareImmediate( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPImmediateCanCompareALargePositiveToASmallPositive  )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CompareImmediate( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPImmediateCanCompareANegativeNumberToAPositive  )
{
    auto Test = CompareANegativeNumberToAPositive();
    CompareImmediate( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPImmediateCanCompareTwoValuesThatResultInANegativeFlagSet  )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CompareImmediate( Test, Register::A );
}


// Zero page
TEST_F( CPUCompareRegisterTest, CMPZeroPageCanCompareTwoIdenticalValues  )
{
    auto Test = CompareTwoIdenticalValues();
    CompareZeroPage( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPZeroPageCanCompareALargePositiveToASmallPositive  )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CompareZeroPage( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPZeroPageCanCompareANegativeNumberToAPositive  )
{
    auto Test = CompareANegativeNumberToAPositive();
    CompareZeroPage( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPZeroPageCanCompareTwoValuesThatResultInANegativeFlagSet  )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CompareZeroPage( Test, Register::A );
}

// Zero page X
TEST_F( CPUCompareRegisterTest, CMPZeroPageXCanCompareTwoIdenticalValues  )
{
    auto Test = CompareTwoIdenticalValues();
    CompareZeroPage( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CMPZeroPageXCanCompareALargePositiveToASmallPositive  )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CompareZeroPage( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CMPZeroPageXCanCompareANegativeNumberToAPositive  )
{
    auto Test = CompareANegativeNumberToAPositive();
    CompareZeroPage( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CMPZeroPageXCanCompareTwoValuesThatResultInANegativeFlagSet  )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CompareZeroPage( Test, Register::X );
}

// Absolute
TEST_F( CPUCompareRegisterTest, CMPAbsoluteCanCompareTwoIdenticalValues )
{
    auto Test = CompareTwoIdenticalValues();
    CompareAbsolute( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteCanCompareALargePositiveToASmallPositive )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CompareAbsolute( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteCanCompareANegativeNumberToAPositive )
{
    auto Test = CompareANegativeNumberToAPositive();
    CompareAbsolute( Test, Register::A );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteCanCompareTwoValuesThatResultInANegativeFlagSet )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CompareAbsolute( Test, Register::A );
}

//-- Absolute X
TEST_F( CPUCompareRegisterTest, CMPAbsoluteXCanCompareTwoIdenticalValues )
{
    auto Test = CompareTwoIdenticalValues();
    CMPAbsoluteX( Test );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteXCanCompareALargePositiveToASmallPositive )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CMPAbsoluteX( Test );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteXCanCompareANegativeNumberToAPositive )
{
    auto Test = CompareANegativeNumberToAPositive();
    CMPAbsoluteX( Test );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteXCanCompareTwoValuesThatResultInANegativeFlagSet )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CMPAbsoluteX( Test );
}

//-- Absolute Y
TEST_F( CPUCompareRegisterTest, CMPAbsoluteYCanCompareTwoIdenticalValues )
{
    auto Test = CompareTwoIdenticalValues();
    CMPAbsoluteY( Test );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteYCanCompareALargePositiveToASmallPositive )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CMPAbsoluteY( Test );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteYCanCompareANegativeNumberToAPositive )
{
    auto Test = CompareANegativeNumberToAPositive();
    CMPAbsoluteY( Test );
}

TEST_F( CPUCompareRegisterTest, CMPAbsoluteYCanCompareTwoValuesThatResultInANegativeFlagSet )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CMPAbsoluteY( Test );
}


//-- Indirect X
TEST_F( CPUCompareRegisterTest, CMPIndirectXCanCompareTwoIdenticalValues )
{
    auto Test = CompareTwoIdenticalValues();
    CMPIndirectX( Test );
}

TEST_F( CPUCompareRegisterTest, CMPIndirectXCanCompareALargePositiveToASmallPositive )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CMPIndirectX( Test );
}

TEST_F( CPUCompareRegisterTest, CMPIndirectXCanCompareANegativeNumberToAPositive )
{
    auto Test = CompareANegativeNumberToAPositive();
    CMPIndirectX( Test );
}

TEST_F( CPUCompareRegisterTest, CMPIndirectXCanCompareTwoValuesThatResultInANegativeFlagSet )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CMPIndirectX( Test );
}

//-- Indirect Y
TEST_F( CPUCompareRegisterTest, CMPIndirectYCanCompareTwoIdenticalValues )
{
    auto Test = CompareTwoIdenticalValues();
    CMPIndirectY( Test );
}

TEST_F( CPUCompareRegisterTest, CMPIndirectYCanCompareALargePositiveToASmallPositive )
{
    auto Test = CompareALargePositiveToASmallPositive();
    CMPIndirectY( Test );
}

TEST_F( CPUCompareRegisterTest, CMPIndirectYCanCompareANegativeNumberToAPositive )
{
    auto Test = CompareANegativeNumberToAPositive();
    CMPIndirectY( Test );
}

TEST_F( CPUCompareRegisterTest, CMPIndirectYCanCompareTwoValuesThatResultInANegativeFlagSet )
{
    auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
    CMPIndirectY( Test );
}

//-- CPX Immediate
TEST_F( CPUCompareRegisterTest, CPXImmediateCanCompareTwoIdenticalValues )
{
	auto Test = CompareTwoIdenticalValues();
	CompareImmediate( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXImmediateCanCompareALargePositiveToASmallPositive )
{
	auto Test = CompareALargePositiveToASmallPositive();
	CompareImmediate( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXImmediateCanCompareANegativeNumberToAPositive )
{
	auto Test = CompareANegativeNumberToAPositive();
	CompareImmediate( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXImmediateCanCompareTwoValuesThatResultInANegativeFlagSet )
{
	auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
	CompareImmediate( Test, Register::X );
}

//-- CPY Immediate
TEST_F( CPUCompareRegisterTest, CPYImmediateCanCompareTwoIdenticalValues )
{
	auto Test = CompareTwoIdenticalValues();
	CompareImmediate( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYImmediateCanCompareALargePositiveToASmallPositive )
{
	auto Test = CompareALargePositiveToASmallPositive();
	CompareImmediate( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYImmediateCanCompareANegativeNumberToAPositive )
{
	auto Test = CompareANegativeNumberToAPositive();
	CompareImmediate( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYImmediateCanCompareTwoValuesThatResultInANegativeFlagSet )
{
	auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
	CompareImmediate( Test, Register::Y );
}

//-- CPX Zero Page
TEST_F( CPUCompareRegisterTest, CPXZeroPageCanCompareTwoIdenticalValues )
{
	auto Test = CompareTwoIdenticalValues();
	CompareZeroPage( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXZeroPageCanCompareALargePositiveToASmallPositive )
{
	auto Test = CompareALargePositiveToASmallPositive();
	CompareZeroPage( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXZeroPageCanCompareANegativeNumberToAPositive )
{
	auto Test = CompareANegativeNumberToAPositive();
	CompareZeroPage( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXZeroPageCanCompareTwoValuesThatResultInANegativeFlagSet )
{
	auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
	CompareZeroPage( Test, Register::X );
}

//-- CPY Zero Page
TEST_F( CPUCompareRegisterTest, CPYZeroPageCanCompareTwoIdenticalValues )
{
	auto Test = CompareTwoIdenticalValues();
	CompareZeroPage( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYZeroPageCanCompareALargePositiveToASmallPositive )
{
	auto Test = CompareALargePositiveToASmallPositive();
	CompareZeroPage( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYZeroPageCanCompareANegativeNumberToAPositive )
{
	auto Test = CompareANegativeNumberToAPositive();
	CompareZeroPage( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYZeroPageCanCompareTwoValuesThatResultInANegativeFlagSet )
{
	auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
	CompareZeroPage( Test, Register::Y );
}

//-- CPX Absolute
TEST_F( CPUCompareRegisterTest, CPXAbsoluteCanCompareTwoIdenticalValues )
{
	auto Test = CompareTwoIdenticalValues();
	CompareAbsolute( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXAbsoluteCanCompareALargePositiveToASmallPositive )
{
	auto Test = CompareALargePositiveToASmallPositive();
	CompareAbsolute( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXAbsoluteCanCompareANegativeNumberToAPositive )
{
	auto Test = CompareANegativeNumberToAPositive();
	CompareAbsolute( Test, Register::X );
}

TEST_F( CPUCompareRegisterTest, CPXAbsoluteCanCompareTwoValuesThatResultInANegativeFlagSet )
{
	auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
	CompareAbsolute( Test, Register::X );
}

//-- CPY Absolute
TEST_F( CPUCompareRegisterTest, CPYAbsoluteCanCompareTwoIdenticalValues )
{
	auto Test = CompareTwoIdenticalValues();
	CompareAbsolute( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYAbsoluteCanCompareALargePositiveToASmallPositive )
{
	auto Test = CompareALargePositiveToASmallPositive();
	CompareAbsolute( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYAbsoluteCanCompareANegativeNumberToAPositive )
{
	auto Test = CompareANegativeNumberToAPositive();
	CompareAbsolute( Test, Register::Y );
}

TEST_F( CPUCompareRegisterTest, CPYAbsoluteCanCompareTwoValuesThatResultInANegativeFlagSet )
{
	auto Test = CompareTwoValuesThatResultInANegativeFlagSet();
	CompareAbsolute( Test, Register::Y );
}