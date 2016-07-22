#ifndef CDRASN1_BLOCK
#define CDRASN1_BLOCK

#include <exception>
#include <string>
#include <vector>

#include <cstdio>

#ifdef DEBUG
#include <iostream>
#endif

namespace cdrasn1
{
class definitions
{
public:
	definitions();
	definitions(const char *) 		throw(const std::runtime_error&);
	void load_file(const char*)		throw(const std::runtime_error&);
protected:
	unsigned char * data;
	unsigned int datasize;

	//Methods
	std::vector<std::string> readline(FILE *);
	std::string readword(FILE *);
	void gotoendline(FILE *);
};
}
#endif
