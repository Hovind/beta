#pragma once

#include <string>

namespace Engine{
	class Exception : public std::exception {
	public:
		Exception(std::string str);
		~Exception() throw();
		const char* what () const throw();
	private:
		std::string str;
	};
}
