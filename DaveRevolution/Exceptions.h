#pragma once
#include <exception>
#include <string>
using namespace std;
//A project specific exception implementations
class BadCastException : public exception {
private:
	std::string function_name;
public:
	BadCastException(const char* name) {
		function_name.append( name);
	}
	virtual const char* what() const throw() {
		std::string s;
		s.append("BadCastException -> ").append(function_name);
		return s.c_str();
	}

};

class FileNotFoundException : public exception {
private:
	 std::string filename;
public:
	FileNotFoundException(const char* name)
	{
		filename.append(name);
	}
	const char* what() const throw() {
		std::string s;
		s.append("FileNotFoundException -> ").append(filename);
		return s.c_str();
	}
};
