#ifndef _UTIL_H_
#define _UTIL_H_

#include <string>
#include <iostream>

class Util
{
public:
	static void LogToSTDOUT(std::string line)
	{
		std::cout << "[LOG] " << line << std::endl;
	}
};
#endif