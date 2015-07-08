#pragma once

#include <string>

namespace Engine{
	class MyException : public std::exception {
	public:
		MyException(std::string str);
		~MyException() throw();
		const char* what () const throw();
	private:
		std::string str;
	};
}