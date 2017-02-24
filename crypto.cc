#include <iostream>
#include "encoding.h"
#include "crypto.h"

std::vector<BYTE> fixed_xor(std::vector<BYTE> v1, std::vector<BYTE> v2) {
  std::vector<BYTE> result;

  if (v1.size() != v2.size()) {
    std::cerr << "FATAL: Buffers for fixed xor must be of equal size.";
    exit(1);
  }

  for (int i=0; i < v1.size(); i++) {
    result.push_back(v1[i] ^ v2[i]);
  }

  return result;
}

std::vector<BYTE> xor_char(unsigned char c, std::vector<BYTE> v) {
  std::vector<BYTE> result;
  for (int i=0; i < v.size(); i++) {
    result.push_back(v[i] ^ c);
  }

  return result;
}
