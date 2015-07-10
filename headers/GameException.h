#pragma once

#include <string>

class GameException : public std::exception {
public:
	GameException(std::string str);
	~GameException() throw();
	const char* what () const throw();
private:
	std::string m_str;
};
