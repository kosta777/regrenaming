#ifndef _BATCH_PARSER_ARGUMENTS_H_
#define _BATCH_PARSER_ARGUMENTS_H_

#include <string>
#include "batchparser.h"
#include <vector>

class BatchParserArguments : public BatchParser
{
private:
	std::vector<std::string> renamedInstructions;
	std::vector<std::string> foundArguments;
	int argumentsAccessCount = 0;
	int argumentsSize = 0;

public:
	BatchParserArguments(int _size);

	bool Feed(std::string) override;
	int CollectResult() override;
	double CollectResultPercentage();

};

#endif
