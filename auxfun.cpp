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
