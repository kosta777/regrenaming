#ifndef _TEXT_PARSER_
#define _TEXT_PARSER_

#include <string>
#include <fstream>
#include <iostream>

class TextParser
{
private:
	std::ifstream *file;
	bool valid;
public:
	TextParser(std::string file_name);
	~TextParser();

	std::string GetNextLine();
	bool IsValid();

};

#endif