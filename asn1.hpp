#ifndef BLOCK_ASN1
#define BLOCK_ASN1

#include <map>
#include <stdexcept>
#include <string>

// Namespace definition
namespace asn1 {
enum data_type {
  reserved_0,
  boolean,
  integer,
  bitstring,
  octetstring,
  null,
  obj_identifier,
  obj_descriptor,
  external,
  real,
  enumerated,
  embedded_pdv,
  utf8string,
  relative_obg_identifier,
  time,
  reserved_15,
  seq_seqof,
  set_setof,
  characterstrings,
  utc_time,
  generalized_time,
  date,
  timeofday,
  datetime,
  duration,
  oid_itnl_resource_identifier,
  rel_oid_itnl_resource_identifier
};
const std::map<int, data_type> universal_tags{
    {0, data_type::reserved_0},
    {1, data_type::boolean},
    {2, data_type::integer},
    {3, data_type::bitstring},
    {4, data_type::octetstring},
    {5, data_type::null},
    {6, data_type::obj_identifier},
    {7, data_type::obj_descriptor},
    {8, data_type::external},
    {9, data_type::real},
    {10, data_type::enumerated},
    {11, data_type::embedded_pdv},
    {12, data_type::utf8string},
    {13, data_type::relative_obg_identifier},
    {14, data_type::time},
    {15, data_type::reserved_15},
    {16, data_type::seq_seqof},
    {17, data_type::set_setof},
    {18, data_type::characterstrings},
    {19, data_type::characterstrings},
    {20, data_type::characterstrings},
    {21, data_type::characterstrings},
    {22, data_type::characterstrings},
    {23, data_type::utc_time},
    {24, data_type::generalized_time},
    {25, data_type::characterstrings},
    {26, data_type::characterstrings},
    {27, data_type::characterstrings},
    {28, data_type::characterstrings},
    {29, data_type::characterstrings},
    {30, data_type::characterstrings},
    {31, data_type::date},
    {32, data_type::timeofday},
    {33, data_type::datetime},
    {34, data_type::duration},
    {35, data_type::oid_itnl_resource_identifier},
    {36, data_type::rel_oid_itnl_resource_identifier}};
const std::map<std::string, data_type> parametrization{
    {{"BOOLEAN"}, data_type::boolean},
    {{"INTEGER"}, data_type::integer},
    {{"ENUMERATED"}, data_type::enumerated},
    {{"REAL"}, data_type::real},
    {{"BIT STRING"}, data_type::bitstring},
    {{"OCTET STRING"}, data_type::octetstring},
    {{"NULL"}, data_type::null},
    {{"SEQUENCE"}, data_type::seq_seqof},
    {{"SEQUENCE OF"}, data_type::seq_seqof},
    {{"SET"}, data_type::set_setof},
    {{"SET OF"}, data_type::set_setof}};
class asn1Mask {
public:
  asn1Mask();
  asn1Mask(const char *) throw(const std::runtime_error &);
  virtual ~asn1Mask();
  void loadFileDefinitions(const char *) throw(const std::runtime_error &);

protected:
  data_type asn1_type;
  std::map<int, asn1Mask> definedValues; // This map will hosd the possibilities
                                         // involved for each drill level of the
                                         // asn1 binary file. Being defined as
                                         // <tag number,mask>. Probably wrong
                                         // and wiil need refinning, but this is
                                         // a start.
};
};

#endif
