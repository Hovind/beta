#include "Exception.h"

namespace Engine {
	Exception::Exception(std::string str)
	: str(str) {}

	Exception::~Exception() throw() {}

	const char* Exception::what () const throw() {
		return str.c_str();
	}
}
