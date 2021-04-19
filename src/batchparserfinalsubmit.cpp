#include "batchparserfinalsubmit.h"
#include "util.h"
#include "batchparser.h"
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

BatchParserFinalSubmit::BatchParserFinalSubmit(int _size): BatchParser(_size)
{

}

bool BatchParserFinalSubmit::Feed(std::string line)
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

		std::string instructionName = (*it).substr(0, (*it).find("="));
		Util::LogToSTDOUT("INSTRUCTION FOUND: " + instructionName);

		if (std::find(renamedInstructions.begin(), renamedInstructions.end(), instructionName) != renamedInstructions.end())
			continue;

		renamedInstructions.push_back(instructionName);

		//Increase the amount of accesses to REMAP
		renameCount++;

		Util::LogToSTDOUT("Write found: " + (*it));
	}

	fedCount++;

	return fedCount == size;
}

int BatchParserFinalSubmit::CollectResult()
{
	int cnt = renameCount;
	renameCount = 0;
	fedCount = 0;
	renamedInstructions.clear();

	return cnt;
}

bool BatchParserFinalSubmit::CollectRegisterRenamed(std::string reg) const
{
	return std::find(renamedInstructions.begin(), renamedInstructions.end(), reg) != renamedInstructions.end();
}