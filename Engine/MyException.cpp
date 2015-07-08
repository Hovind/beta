#include "MyException.h"

namespace Engine {
	MyException::MyException(std::string str)
	: str(str) {}

	MyException::~MyException() throw() {}

	const char* MyException::what () const throw() {
		return str.c_str();
	}
}