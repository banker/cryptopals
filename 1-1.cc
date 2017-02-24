#include <iostream>
#include "encoding.h"

int main(int argc, char **argv) {
    std::string s = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string b = base64_encode(hex_decode(s));

    std::cout << s << " is equal to\n  " << b << " in base64\n";

    return 0;
}
