#pragma once

#include <exception>

class ImpossibleAction : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Impossible Action";
	}
} static impossible;