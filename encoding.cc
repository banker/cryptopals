#include <iostream>
#include "encoding.h"

const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char *hex_chars = "0123456789abcdef";

void inline load_chars(BYTE trio[3], BYTE index[4]) {
  index[0] = (trio[0] & 0xfc) >> 2;
  index[1] = ((trio[0] & 0x03) << 4) | ((trio[1] & 0xf0) >> 4);
  index[2] = ((trio[1] & 0x0f) << 2) | ((trio[1] & 0xc0) >> 6);
  index[3] = trio[2] & 0x3f;
}

void inline load_b64(BYTE index[4], BYTE trio[3]) {
  trio[0] = (index[0] << 2) | ((index[1] & 0x30) >> 4);
  trio[1] = ((index[1] & 0xf) << 4) | ((index[2] & 0x3c) >> 2);
  trio[2] = ((index[2] & 0x3) << 6) | index[3];
}

int base64_value(char c) {
  if (c <= '9' && c >= '0') {
    return 52 + (c - 48);
  } else if (c <= 'Z' && c >= 'A') {
    return c - 65;
  } else if (c <= 'z' && c >= 'a') {
    return c - 71;
  } else if (c == '+') {
    return 62;
  } else if (c == '/') {
    return 63;
  }

  return 0;
}


std::string base64_encode(std::vector<BYTE> bytes) {
  std::string base64;
  BYTE trio[3], index[4];
  int i = 0;

  for (BYTE byte : bytes) {
    trio[i++] = byte;
    if (i == 3) {
      load_chars(trio, index);
      for (int j = 0; j < 4; j++) { base64.push_back(base64_chars[index[j]]); }
      i = 0;
    }
  }

  if (i > 0) {
    for (int j = i; j < i + 1; j++) {
      trio[j] = 0;
    }

    load_chars(trio, index);

    for (int j = 0; j < i + 1; j++) {
      base64.push_back(base64_chars[index[j]]);
    }

    while (i++ < 3) {
      base64.push_back('=');
    }
  }

  return base64;
}

std::vector<BYTE> base64_decode(std::string base64) {
  std::vector<BYTE> bytes;
  BYTE trio[3], index[4];
  int c = 0;
  int j = 0;

  for (int i = 0; i < base64.size(); i++) {
    if(base64[i] == '=') break;

    index[c++] = base64[i];
    if (c == 4) {
      for (j = 0; j < 4; j++) {
        index[j] = base64_value(index[j]);
      }
      load_b64(index, trio);

      for (j=0; j < 3; j++) {
        bytes.push_back(trio[j]);
      }
      c = 0;
    }
  }

  if (c > 0) {
    for (j = c; j < 4; j++) {
      index[j] = 0;
    }

    for (j = 0; j < 4; j++) {
      index[j] = base64_value(index[j]);
    }

    load_b64(index, trio);

    for (j = 0; j < (c - 1); j++) {
      bytes.push_back(trio[j]);
    }
  }

  return bytes;
}

std::string hex_encode(std::vector<BYTE> bytes) {
  std::string hex;

  for (BYTE byte : bytes) {
    hex.push_back(hex_chars[byte / 16]);
    hex.push_back(hex_chars[byte % 16]);
  }

  return hex;
}

unsigned char hex_value_of_char(char c) {
  if (c <= 'F' && c >= 'A') {
    return c - 65 + 10;
  } else if (c <= 'f' && c >= 'a') {
    return c - 97 + 10;
  } else if (c >= '0' && c <= '9') {
    return c - 48;
  } else {
    std::cerr << "ERROR! Invalid hex value: " << c << "\n";
    exit(1);
  }
}

std::vector<BYTE> hex_decode(std::string hex) {
  std::vector<BYTE> result;

  for (int i=0; i < (hex.size() - 1); i+=2) {
    result.push_back(hex_value_of_char(hex[i]) * 16 +
                     hex_value_of_char(hex[i + 1]));
  }

  return result;
}

