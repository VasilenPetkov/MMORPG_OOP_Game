#include "Utils.h"
#include <iostream>
#pragma warning (disable : 4996)
 char* copyStr(const char* str)
{
	if (!str || *str)
		throw std::invalid_argument("Invalid string");

	char* temp = new char[strlen(str) + 1];
	strcpy(temp, str);

	return temp;
}
