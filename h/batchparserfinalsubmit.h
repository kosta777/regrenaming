#ifndef _BATCH_PARSER_FINAL_SUBMIT_H_
#define _BATCH_PARSER_FINAL_SUBMIT_H_

#include <string>
#include "batchparser.h"
#include <vector>

class BatchParserFinalSubmit : public BatchParser
{
private:
	std::vector<std::string> renamedInstructions;
public:
	BatchParserFinalSubmit(int _size);

	bool Feed(std::string) override;
	int CollectResult() override;
	bool CollectRegisterRenamed(std::string reg) const;
};

#endif
