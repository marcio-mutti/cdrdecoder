#include "cdrasn1.hpp"

#include <cstdio>

using namespace std;
using namespace cdrasn1;

cdrasn1::definitions::definitions() {}

cdrasn1::definitions::definitions(const char* filename) throw(const runtime_error&) {
	try {
		load_file(filename);
	} catch (const runtime_error& err) {
		throw(err);
	}
	return;
}

void cdrasn1::definitions::load_file(const char* filename) throw(
    const runtime_error&) {
	FILE* definitions_file(nullptr);
	string workword;
	definitions_file = fopen(filename, "r");
	while (!feof(definitions_file)) {
		workword = readword(definitions_file);
		if (workword.empty()) continue;
		if (root_name.empty()) {
			preambule(definitions_file, workword);
			continue;
		}
	}
	fclose(definitions_file);
}

string cdrasn1::definitions::readword(FILE* definitions_file) {
	char byte(0);
	string result;
	bool commenttrigger;
	while (!feof(definitions_file)) {
		fread(&byte, 1, 1, definitions_file);
		switch (byte) {
			case '-':
				if (commenttrigger) {
					result.pop_back();
					gotoendline(definitions_file);
					return result;

				} else {
					commenttrigger = true;
				}
				break;
			case ' ':
			case '\n':
				if (result.size() == 0) continue;
				return result;
		}
		result.push_back(byte);
	}
	return result;
}

void cdrasn1::definitions::gotoendline(FILE* definitions_file) {
	char byte(0);
	while (!feof(definitions_file)) {
		fread(&byte, 1, 1, definitions_file);
		if (byte == '\n') return;
	}
	return;
}

void cdrasn1::definitions::preambule(
    FILE* definitions_file,
    const string& root_name_found) throw(const runtime_error&) {
	string workword;
	root_name = root_name_found;
	workword = readword(definitions_file);
	if (workword != "DEFINITIONS") {
		string message(
		    "The expected DEFINITIONS statement after the root "
		    "identification (");
		message += root_name + ") wasn't found. Found " + workword +
			   "instead.";
		throw(runtime_error(message));
	}
	workword = readword(definitions_file);
	if (workword == "IMPLICIT") {
		cdrtype = tagtype::implicit_type;
	} else if (workword == "EXPLICIT") {
		cdrtype = tagtype::explicit_type;
	} else {
		string message(
		    "The expected type of tags statement after the DEFINITIONS "
		    "statement wasn't found. "
		    "Found ");
		message += workword + " instead.";
		throw(runtime_error(message));
	}
	workword = readword(definitions_file);
	if (workword != "TAGS") {
		string message(
		    "The expected TAGS statement after the type wasn't found. "
		    "Found ");
		message += workword + " instead.";
		throw(runtime_error(message));
	}
	workword = readword(definitions_file);
	if (workword != "::=") {
		string message(
		    "The expected attribution symbol after the TAGS statement "
		    "wan't found.Found ");
		message += workword + " instead.";
		throw(runtime_error(message));
	}
	workword = readword(definitions_file);
	if (workword != "BEGIN") {
		string message(
		    "The expected BEGIN statement after the attribution symbol "
		    "wasn't found. Found ");
		message += workword + " instead.";
		throw(runtime_error(message));
	}
}
