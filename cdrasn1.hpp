#ifndef CDRASN1_BLOCK
#define CDRASN1_BLOCK

#include <stdexcept>
#include <string>
#include <vector>

#include <cstdio>

#ifdef DEBUG
#include <iostream>
#endif

namespace cdrasn1
{
enum tagtype
{
	implicit_type,
	explicit_type,
	automatic_type
};
enum asn1type
{
	boolean,
	integer,
	enumerated,
	real,
	bitstring,
	octetstring,
	null,
	sequence,
	sequence_of,
	set,
	set_of,
	choice,
	identifier,
	undefined
};
struct definition_variable
{
	std::string parameter;
	asn1type type;
};
asn1type parse_type(const std::string&);
class definitions
{
public:
	definitions();
	definitions(const char*) 			throw(const std::runtime_error&);
	void load_file(const char*)			throw(const std::runtime_error&);
protected:
	std::string root_name;
	tagtype cdrtype;
	//Methods
	std::string readword(FILE *);
	void gotoendline(FILE *);
	void preambule(FILE *, const std::string&)	throw(const std::runtime_error&);
	void main_options(FILE *)			throw(const std::runtime_error&);
	definition_variable readvariable(FILE *)	throw(const std::runtime_error&);
};
}
#endif
