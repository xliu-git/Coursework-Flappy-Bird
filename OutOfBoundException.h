//CPS 400 final project
//File Name: OutOfBoundException.h
//description: This class define an out of bound exception.
//				if the object is out of game window, it will throw an exception

#include <stdexcept>

class OutOfBoundException : public std::domain_error
{
public:
	OutOfBoundException()
		:std::domain_error("Object position out of domain") {}
};


