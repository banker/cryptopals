#ifndef _CRYPTO_ENCODING_H_
#define _CRYPTO_ENCODING_H_

#include <vector>
#include <string>

typedef unsigned char BYTE;

std::string hex_encode(std::vector<BYTE> bytes);
std::vector<BYTE> hex_decode(std::string hex);
std::vector<BYTE> base64_decode(std::string base64);
std::string base64_encode(std::vector<BYTE> bytes);

#endif
