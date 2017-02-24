#ifndef _CRYPTO_HELPERS_H_
#define _CRYPTO_HELPERS_H_

#include "encoding.h"

std::vector<BYTE> fixed_xor(std::vector<BYTE> v1, std::vector<BYTE> v2);
std::vector<BYTE> xor_char(unsigned char c, std::vector<BYTE> v);

#endif
