#include <iostream>
#include "crypto.h"

int main(int argc, char** argv) {
  std::vector<BYTE> v1 = hex_decode("1c0111001f010100061a024b53535009181c");
  std::vector<BYTE> v2 = hex_decode("686974207468652062756c6c277320657965");
  std::vector<BYTE> result = fixed_xor(v1, v2);

  std::cout << "XOR of " << hex_encode(v1) << " and " << hex_encode(v2) <<
    " is\n  " << hex_encode(result) << "\n";

  return 0;
}
