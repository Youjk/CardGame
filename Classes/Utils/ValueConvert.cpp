#include "..\Utils\ValueConvert.h"


const std::string ValueConvert::intTostring(const int var)
{
	std::string s;
	char temp[10];
	sprintf(temp, "%d", var);
	s = temp;
	return s;
}
