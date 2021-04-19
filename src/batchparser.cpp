#include "batchparser.h"
#include "util.h"
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

BatchParser::BatchParser(int _size) :size(_size)
{
	renameCount = 0;
	fedCount = 0;
}

bool BatchParser::Feed(std::string line)
{
	//fake exit, replace with exception
	if (fedCount == size)
		return true;

	//Ignore if its not an instruction
	if (!CheckIfInstruction(line))
		return false;

	//Tokenize words in a row with single space as delimeter
	std::vector<std::string> tokens;
	std::istringstream iss(line);
	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter(tokens));

	//Discard first two tokens since they are Address number and Function name
	tokens.erase(tokens.begin());
	tokens.erase(tokens.begin());

	bool writeInstruction = false;
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		//discard everything before comments
		if (!writeInstruction && *it != ";")
			continue;
		writeInstruction = true;

		if (writeInstruction && *it == ";")
			continue;

		//Increase the amount of accesses to REMAP
		renameCount++;

		Util::LogToSTDOUT("Write found: " + (*it));
	}

	fedCount++;

	return fedCount == size;
}

bool BatchParser::CheckIfInstruction(std::string line)
{
	return isdigit(line[0]);
}

int BatchParser::CollectResult()
{
	int cnt = renameCount;
	renameCount = 0;
	fedCount = 0;

	return cnt;
}


bool BatchParser::FindSourceRegisterInInstruction(std::string line, std::string reg)
{
	return line.find(reg) != std::string::npos;
}