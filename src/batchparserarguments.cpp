#include "batchparserarguments.h"
#include "util.h"
#include "batchparser.h"
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

BatchParserArguments::BatchParserArguments(int _size) : BatchParser(_size)
{

}

bool BatchParserArguments::Feed(std::string line)
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

	foundArguments.clear();
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		//discard everything before comments
		if (!writeInstruction && *it != ";")
		{
			if (FindSourceRegisterInInstruction(*it, "EAX"))
			{
				argumentsSize++;
				foundArguments.push_back("EAX");
			}
			if (FindSourceRegisterInInstruction(*it, "EBX"))
			{
				foundArguments.push_back("EBX");
				argumentsSize++;
			}
			if (FindSourceRegisterInInstruction(*it, "ECX"))
			{
				foundArguments.push_back("ECX");
				argumentsSize++;
			}
			if (FindSourceRegisterInInstruction(*it, "EDX"))
			{
				foundArguments.push_back("EDX");
				argumentsSize++;
			}
			if (FindSourceRegisterInInstruction(*it, "EBP"))
			{				
				foundArguments.push_back("EBP");
				argumentsSize++;
			}
			if (FindSourceRegisterInInstruction(*it, "EDI"))
			{
				foundArguments.push_back("EDI");
				argumentsSize++;
			}
			if (FindSourceRegisterInInstruction(*it, "ESI"))
			{
				foundArguments.push_back("ESI");
				argumentsSize++;
			}

			continue;
		}
			
		writeInstruction = true;

		if (writeInstruction && *it == ";")
			continue;

		std::string instructionName = (*it).substr(0, (*it).find("="));
		Util::LogToSTDOUT("INSTRUCTION FOUND: " + instructionName);

		//For each argument used in this batch, check if it is in remap file
		for (std::string arg : foundArguments)
		{
			if (std::find(renamedInstructions.begin(), renamedInstructions.end(), arg) != renamedInstructions.end())
			{
				argumentsAccessCount++;
			}
		}

		//refresh remap file for this round
		renamedInstructions.clear();

		if (std::find(renamedInstructions.begin(), renamedInstructions.end(), instructionName) != renamedInstructions.end())
		{
			//did not perform a rename
		}
		else
		{

			renamedInstructions.push_back(instructionName);

			//Increase the amount of accesses to REMAP
			renameCount++;

			Util::LogToSTDOUT("Write found: " + (*it));
		}

	}

	fedCount++;

	return fedCount == size;
}


int BatchParserArguments::CollectResult()
{
	int cnt = renameCount;
	renameCount = 0;
	fedCount = 0;
	//renamedInstructions.clear();

	return cnt;
}

double BatchParserArguments::CollectResultPercentage()
{
	double value = 0;
	if (argumentsSize == 0)
		return 0;

	value = (double)argumentsAccessCount / argumentsSize;
	argumentsAccessCount = 0;
	argumentsSize = 0;
	foundArguments.clear();

	return value;
}