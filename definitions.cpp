#include "cdrasn1.hpp"

#include <cstdio>

using namespace std;
using namespace cdrasn1;

cdrasn1::definitions::definitions() {}

cdrasn1::definitions::definitions(const char* filename) throw(
    const runtime_error&) {
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
					int savepoint(ftell(definitions_file));
					result.pop_back();
					gotoendline(definitions_file);
					if (result == "SEQUENCE" ||
					    result == "SET") {
						string lookforward(
						    readword(definitions_file));
						if (lookforward == "OF")
							result += " OF";
						else
							fseek(definitions_file,
							      savepoint,
							      SEEK_SET);
					}
					return result;

				} else {
					commenttrigger = true;
				}
				break;
			case ' ':
			case '\n':
				if (result.size() == 0) continue;
				int savepoint(ftell(definitions_file));
				if (result == "SEQUENCE" || result == "SET") {
					string lookforward(
					    readword(definitions_file));
					if (lookforward == "OF")
						result += " OF";
					else
						fseek(definitions_file,
						      savepoint, SEEK_SET);
				}
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

void cdrasn1::definitions::main_options(FILE* definitions_file) throw(
    const runtime_error&) {
	// TODO: Read the variable title and proceed;
	definition_variable first_option(readvariable(definitions_file));
}
cdrasn1::definition_variable cdrasn1::definitions::readvariable(
    FILE* definitions_file) throw(const runtime_error&) {
	definition_variable result;
	int savepoint(0);
	string variable, definer, type, continuity;
	try {
		variable = readword(definitions_file);
		definer = readword(definitions_file);
		type = readword(definitions_file);
	} catch (const runtime_error& err) {
		string message(
		    "Found an error trying to read a new option in the "
		    "definitions file.\n");
		message += err.what();
		throw(runtime_error(message));
	}
	if (definer != "::=") {
		string message(
		    "The definer statement wasn't correctly found when reading "
		    "variable: ");
		message += variable + "\n Found " + definer + " instead.";
		throw(runtime_error(message));
	}
	result.parameter = variable;
	result.type = parse_type(type);
	savepoint = ftell(definitions_file);
	continuity = readword(definitions_file);  // TODO: There is the case
						  // when the size or the range
						  // is informed
	if (continuity == "{") {
		string workword, nextword;
		while (!feof(definitions_file) &&
		       continuity !=
			   "}") {  // TODO: Read the options of the custom type
			// The fields are separated by commas
			workword = readword(definitions_file);
			nextword = readword(definitions_file);
			if (cdrtype == tagtype::automatic_type)  // TODO:
								 // Implementar
								 // o tipo
								 // automático
			{
			} else {
				if (type == "INTEGER" || type == "ENUMERATED") {
					if (nextword.front() == '(') {
						// Case of enumerated options
						unsigned int value(0);
						try {
							value =
							    extract_number_from_brackets(
								nextword);
						} catch (
						    const runtime_error& err) {
							// TODO: Deal with it
						}
						result.value_options.insert(
						    make_pair(value, workword));
					}
				}
			}
		}
	} else {
		fseek(definitions_file, savepoint, SEEK_SET);
	}
	return result;
}
