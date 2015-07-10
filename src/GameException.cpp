#include "GameException.h"

GameException::GameException(std::string str)
: m_str(str) {}

GameException::~GameException() throw() {}

const char* GameException::what () const throw() {
	return m_str.c_str();
}
