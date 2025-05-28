#pragma once
#include "Prerequisites.h"

class XOREncoder
{
public:
  XOREncoder() = default;
  ~XOREncoder() = default;

  std::string
    encode(const std::string& input, const std::string& key)
  {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
      output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
  }

  std::vector<unsigned char>
    HexToBytes(const std::string& input) {
    std::vector<unsigned char> bytes;
    std::istringstream iss(input);
    std::string hexValue;

    while (iss >> hexValue) {
      if (hexValue.size() == 1) {
        hexValue = "0" + hexValue;
      }
      unsigned int byte;
      std::stringstream ss;
      ss << std::hex << hexValue;
      bytes.push_back(static_cast<unsigned char>(byte));
    }
    return bytes;

  }

  void
    printHex(const std::string& input) {
    for (unsigned char c : input) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    }
  }

  bool
    isValidText(const std::string& data) {
    return std::all_of(data.begin(), data.end(), [](unsigned char c) {
      return std::isprint(c) || std::isspace(c) || c == '\n' || c == ' ';
      });
  }

  void
    bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
    for (int clave = 0; clave < 256; clave++) {
      std::string result;

      for (unsigned char c : cifrado) {
        result += c ^ clave;
      }
      if (isValidText(result)) {
        std::cout << "=======================\n" << std::endl;
        std::cout << "Clave 1 byte: " << static_cast<char>(clave)
          << " (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
        std::cout << "Texto decifrado por fuerza bruta 1 byte: " << result << std::endl;
        printHex(result);
        std::cout << "\n=======================\n" << std::endl;
      }
    }
  }
  void
  bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {
    for (int b1 = 0; b1 < 256; b1++) {
      for (int b2 = 0; b2 < 256; b2++) {
        std::string result;
        unsigned char key[2] = { static_cast<unsigned char>(b1), static_cast<unsigned char>(b2) };
        for (int i = 0; i < cifrado.size(); i++) {
          result += cifrado[i] ^ key[i % 2];

        }
        if (isValidText(result)) {
          std::cout << "=======================\n" << std::endl;
          std::cout << "Clave 2 bytes: " << static_cast<char>(b1) << static_cast<char>(b2) << 
            " (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
          << " 0x" << std::hex << std::setw(2) << std::setfill('0') << b2 << ")\n";

          std::cout << "Texto decifrado por fuerza bruta 2 byte: " << result << std::endl;
        }
      }
    }
  }

  void
    bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
    std::vector<std::string> diccionario = {
      "clave", "password", "123456", "qwerty", "abc123", "letmein",
      "monkey", "dragon", "111111", "baseball", "iloveyou", "trustno1"
    };

    for (const auto& clave : diccionario) {
      std::string result;
      for (int i = 0; i < cifrado.size(); i++) {
        result += static_cast<unsigned char>( cifrado[i] ^ clave[i % clave.size()]);
      }
      if (isValidText(result)) {
        std::cout << "=======================\n" << std::endl;
        std::cout << "Clave: " << clave << "\n";
        std::cout << "Texto decifrado: " << result << std::endl;
        std::cout << "\n=======================\n" << std::endl;
      }
    }
  }

private:

};
