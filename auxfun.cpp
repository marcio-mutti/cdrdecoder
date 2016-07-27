#include "cdrasn1.hpp"

using namespace std;
using namespace cdrasn1;

cdrasn1::asn1type cdrasn1::parse_type(const string& TYPE) {
	if (TYPE == "BOOLEAN") return asn1type::boolean;
	if (TYPE == "INTEGER") return asn1type::integer;
	if (TYPE == "ENUMERATED") return asn1type::enumerated;
	if (TYPE == "REAL") return asn1type::real;
	if (TYPE == "BITSTRING") return asn1type::bitstring;
	if (TYPE == "OCTETSRING") return asn1type::octetstring;
	if (TYPE == "NULL") return asn1type::null;
	if (TYPE == "SEQUENCE") return asn1type::sequence;
	if (TYPE == "SEQUENCE OF")
		return asn1type::sequence_of;  // TODO: readwor precisa pegar as
					       // sequences of
	if (TYPE == "SET") return asn1type::set;
	if (TYPE == "SET OF")
		return asn1type::set_of;  // TODO: readword precisa pegar as set
					  // of
	if (TYPE == "CHOICE") return asn1type::choice;
	if (!TYPE.empty()) return asn1type::custom;
	return asn1type::undefined;
}
const unsigned int cdrasn1::extract_number_from_brackets(
    const std::string& bracketed) throw(const runtime_error&) {
	size_t i(0);
	bool nstarted(false);
	string straux;
	while (i != bracketed.size()) {
		if (bracketed.at(i) > 47 && bracketed.at(i) < 57) {
			if (!nstarted) nstarted = true;
			straux.push_back(bracketed.at(i));
		} else {
			if (nstarted) break;
		}
		++i;
	}
	if (straux.empty()) {
		string message("No number was found when parsing the string ");
		message += bracketed + ".";
		throw(runtime_error(message));
	}
	return std::stoul(straux);
}
