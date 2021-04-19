#include "instruction.h"

Instruction::Instruction(std::string name, int opnum)
{
	this->name = name;
	this->opnum = opnum;
}

int Instruction::GetOperandsNumber() const
{
	return opnum;
}