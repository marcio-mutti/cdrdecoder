#include "asn1.hpp"

#include <cerrno>
#include <cstdio>
#include <cstring>

using namespace std;

asn1::asn1Mask::asn1Mask() {}
asn1::asn1Mask::asn1Mask(const char *fileName) throw(const runtime_error&){
  try {
    loadFileDefinitions(fileName);
  } catch (const runtime_error &error) {
    throw;
  }
}
asn1::asn1Mask::~asn1Mask() {}
void loadFileDefinitions(const char * fileName) throw(const runtime_error&) {
	FILE * defOrigin(nullptr);
	
	defOrigin=fopen(fileName,"r");
	if (defOrigin == nullptr) throw(runtime_error(strerror(errno))); //Initial error handling

	
}
