#include "textparser.h"
#include <string>
#include <fstream>

TextParser::TextParser(std::string file_name)
{
	file = new std::ifstream;
	file->open(file_name);
	if (!(*file))
	{
		std::cout << "Invalid file: " << file_name<<";" << std::endl;
		valid = false;
	}
	else
	{
		valid = true;
	}
}

std::string TextParser::GetNextLine()
{
	if (IsValid())
	{
		std::string line = "test";
		if (std::getline(*file, line))
		{
			return line;
		}
		else
		{
			valid = false;
			return "";
		}
	}
	
	return "";
}

bool TextParser::IsValid()
{
	return valid;
}

TextParser::~TextParser()
{
	if (file != NULL)
		file->close();
	delete file;
}
