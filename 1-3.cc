#include <iostream>
#include <cmath>
#include "encoding.h"
#include "crypto.h"

bool is_english_character(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int english_text_score(std::vector<BYTE> bytes) {
  float score = 0;
  for (int i=0; i <= bytes.size(); i++) {
    if (is_english_character(bytes[i])) {
      score+=1;
    }
  }

  return score;
}

void print(std::vector<BYTE> message) {
  std::string answer;
  for(int i=0; i < message.size(); i++) {
    answer.push_back((char)message[i]);
  }

  std::cout << "ANSWER: " << answer << "\n";

}

int main(int argc, char** argv) {
  std::string secret = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  std::vector<BYTE> message, winner;
  std::string answer;
  int score=0, top_score = 0;

  std::vector<BYTE> secret_bytes = hex_decode(secret);

  for(int i=0; i < 256; i++) {
    message = xor_char((char)i, secret_bytes);
    score = english_text_score(message);
    if (score >= top_score) {
      top_score = score;
      winner = message;
    }
  }

  print(winner);

  return 0;
}
