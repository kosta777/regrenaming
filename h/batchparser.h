#ifndef _BATCH_PARSER_H_
#define _BATCH_PARSER_H_

#include <string>


class BatchParser
{
protected:
	int size;
	int renameCount;
	int fedCount;

	bool FindSourceRegisterInInstruction(std::string line, std::string reg);
public:
	BatchParser(int _size);
	virtual bool Feed(std::string);
	virtual int CollectResult();
	
	static bool CheckIfInstruction(std::string line);
};

#endif
