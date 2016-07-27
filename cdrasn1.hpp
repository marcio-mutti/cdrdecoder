#ifndef CDRASN1_BLOCK
#define CDRASN1_BLOCK

#include <map>
#include <set>
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
	custom,
	undefined
};
struct definition_variable
{
	std::string parameter;
	asn1type type;
	std::map<unsigned int,std::string> refered_tags;
	std::map<unsigned int,std::string> value_options;
	const bool operator==(const definition_variable&) const;
};
struct tagdeflink
{
	unsigned int tag;
	definition_variable * def;
};
struct tags
{
	unsigned int tag;
	std::map<unsigned int, tagdeflink> children;
	const bool operator<(const tags&) const;
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
	std::set<tags> available_tags;
	//Methods
	std::string readword(FILE *);
	void gotoendline(FILE *);
	void preambule(FILE *, const std::string&)	throw(const std::runtime_error&);
	void main_options(FILE *)			throw(const std::runtime_error&);
	definition_variable readvariable(FILE *)	throw(const std::runtime_error&);
};
}
#endif
