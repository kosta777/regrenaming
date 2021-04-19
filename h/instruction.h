#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <string>

class Instruction
{
private:
	int opnum;
	std::string name;
	Instruction *op1, *op2, *op3;

public:
	Instruction(std::string, int);
	int GetOperandsNumber() const;
};

#endif