#ifndef ENF_H
#define ENF_H

#include <iostream>
#include <exception>
#include <string>

class EntityNotFound : public std::exception
{
	std::string errStr;
public:
	EntityNotFound(std::string a)
	{
		errStr = a;
	}
	const char* what() const throw()
	{
		std::string wad = errStr + " Entity Not Found!";
		return wad.c_str();
	}
};

#endif