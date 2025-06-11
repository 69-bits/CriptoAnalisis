#include "Prerequisites.h"
#include "XOREncoder.h"
#include "AsciiBinary.h"
#include "DES.h"

int
main() {
  //std::bitset<64> ciphertext("0001001000110100010101100111100010011010101111001101111011110001");
  std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");

  std::string mensaje = "Garfield SOS";

  while (mensaje.size() % 8 != 0) {
    mensaje += '\0';
  }

  std::vector<std::bitset<64>> cipherBlocks;
  std::cout << "Mensaje original: " << mensaje << std::endl;
  std::cout << "Cifrado en hexadecimal:\n";

  DES des(key);
  for (size_t i = 0; i < mensaje.size(); i += 8) {
    std::string block = mensaje.substr(i, 8);
    auto blockBits = des.stringToBitset64(block);
    auto encryptedBlock = des.encode(blockBits);
    cipherBlocks.push_back(encryptedBlock);
    std::cout << std::uppercase << std::setw(16) << std::setfill('0')
      << encryptedBlock.to_ullong() << " ";

  }

  std::string decryptedMessage;
  for (const auto& block : cipherBlocks) {
    auto decryptedBlock = des.decode(block);
    decryptedMessage += des.bitset64ToString(decryptedBlock);
  }

  std::cout << "\nMensaje descifrado: " << decryptedMessage << std::endl;
}

