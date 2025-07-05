#pragma once

#include "Prerequisites.h"

class
  DES {
public:
  DES() = default;
  DES(const std::bitset<64>& key) {
    generateSubkeys();
  }

  ~DES() = default;

  /* * Función para generar las subclaves a partir de la clave principal.
   * La clave debe ser de 64 bits, pero solo se utilizan 56 bits efectivos.
   * Las subclaves se generan para cada ronda del algoritmo DES.
   *
   * Ejemplo:
   * std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");
   * DES des(key);
   * des.generateSubkeys();
  */
  void
  generateSubkeys() {
    for (int i = 0; i < 16; i++) {
      std::bitset<48> subkey((key.to_ullong() >> i) & 0xFFFFFFFFFFFF);
      subkeys.push_back(subkey);
    }
  }


  /* * Función de permutación inicial (IP) que reorganiza los bits del bloque de entrada.
   * @param input: El bloque de entrada de 64 bits.
   * @return El bloque permutado de 64 bits.
   *
   * Ejemplo:
   * std::bitset<64> input("0001001100110100010101110111100110011011101111001101111111110001");
   * std::bitset<64> output = iPermutation(input);
   */
  std::bitset<64>
  iPermutation(const std::bitset<64>& input) {
    std::bitset<64> output;
    for (int i = 0; i < 64; i++) {
      output[i] = input[i];
    }
    return output;
  }


  /* * Función de expansión que toma un bloque de 32 bits y lo expande a 48 bits.
   * Utiliza una tabla de expansión para reorganizar los bits.
   * @param halfBlock: El bloque de 32 bits a expandir.
   * @return El bloque expandido de 48 bits.
   *
   * Ejemplo:
   * std::bitset<32> halfBlock("00010011001101000101011101111000");
   * std::bitset<48> expanded = expand(halfBlock);
  */
  std::bitset<48>
  expand(const std::bitset<32>& halfBlock) {
    std::bitset<48> output;

    for (int i = 0; i < 48; i++) {
      output[i] = halfBlock[32 - EXPANSION_TABLE[i]];
    }

    return output;
  }


  /* * Función de sustitución que toma un bloque de 48 bits y lo reduce a 32 bits
   * utilizando una serie de S-Boxes.
   * @param input: El bloque de 48 bits a sustituir.
   * @return El bloque sustituido de 32 bits.
   *
   * Ejemplo:
   * std::bitset<48> input("000100110011010001010111011110001001101010111100");
   * std::bitset<32> substituted = substitute(input);
   */
  std::bitset<32>
  substitute(const std::bitset<48>& input) {
    std::bitset<32> output;
    for (int i = 0; i < 8; i++)
    {
      int row = (input[i * 6] << 1) | input[i * 6 + 5];
      int col = (input[i * 6 + 1] << 3) | (input[i * 6 + 2] << 2) |
        (input[i * 6 + 3] << 1) | input[i * 6 + 4];

      int sboxValue = SBOX[row % 4][col % 16];

      for (int j = 0; j < 4; j++) {
        output[i * 4 + j] = (sboxValue >> (3 - j)) & 1;
      }
    }
    return output;
  }


  /* * Función de permutación P que reorganiza los bits de un bloque de 32 bits.
   * @param input: El bloque de 32 bits a permutar.
   * @return El bloque permutado de 32 bits.
   *
   * Ejemplo:
   * std::bitset<32> input("00010011001101000101011101111000");
   * std::bitset<32> permuted = permutedP(input);
   */
  std::bitset<32>
  permutedP(const std::bitset<32>& input) {
    std::bitset<32> output;
    for (int i = 0; i < 32; i++) {
      output[i] = input[32 - P_TABLE[i]];
    }
    return output;
  }


  /* * Función Feistel que realiza la operación de feistel en un bloque de 32 bits
     * utilizando una subclave de 48 bits.
     * @param right: El bloque de 32 bits derecho.
     * @param subkey: La subclave de 48 bits.
     * @return El resultado de la función Feistel, un bloque de 32 bits.
     *
     * Ejemplo:
     * std::bitset<32> right("00010011001101000101011101111000");
     * std::bitset<48> subkey("000100110011010001010111011110001001101010111100");
     * std::bitset<32> result = feistel(right, subkey);
     */
  std::bitset<32>
  feistel(const std::bitset<32>& right, const std::bitset<48>& subkey) {
    auto expandend = expand(right);
    auto xored = expandend ^ subkey;
    auto substituted = substitute(xored);
    auto pemuted = permutedP(substituted);
    return pemuted;
  }


  /* * Función de permutación final (IP-1) que reorganiza los bits del bloque de salida.
   * @param input: El bloque de entrada de 64 bits.
   * @return El bloque permutado de 64 bits.
   *
   * Ejemplo:
   * std::bitset<64> input("0001001100110100010101110111100110011011101111001101111111110001");
   * std::bitset<64> output = fPermutation(input);
   */
  std::bitset<64>
  fPermutation(const std::bitset<64>& input)
  {
    std::bitset<64> output;
    for (int i = 0; i < 64; i++) {
      output[i] = input[i];
    }
    return output;
  }


  /* * Función de codificación que toma un bloque de 64 bits y lo cifra utilizando el algoritmo DES.
   * @param plaintext: El bloque de texto plano de 64 bits a cifrar.
   * @return El bloque cifrado de 64 bits.
   *
   * Ejemplo:
   * std::bitset<64> plaintext("0001001100110100010101110111100110011011101111001101111111110001");
   * std::bitset<64> ciphertext = encode(plaintext);
   */
  std::bitset<64> 
  encode(const std::bitset<64>& plaintext) {
    auto data = iPermutation(plaintext);
    std::bitset<32> left(data.to_ullong() >> 32);
    std::bitset<32> right(data.to_ullong());

    for (int round = 0; round < 15; round++) {
      auto newRight = left ^ feistel(right, subkeys[round]);
      left = right;
      right = newRight;
    }
    uint64_t combined = (static_cast<uint64_t>(right.to_ullong()) << 32) | left.to_ullong();
    return fPermutation(std::bitset<64>(combined));
  }


  /* * Función para convertir un bloque de texto a un bitset de 64 bits.
   * @param block: El bloque de texto de 8 caracteres (64 bits).
   * @return Un bitset de 64 bits representando el bloque.
   *
   * Ejemplo:
   * std::string block = "Garfield";
   * std::bitset<64> bits = stringToBitset64(block);
   */
  std::bitset<64> 
  stringToBitset64(const std::string& block) {
    uint64_t bits = 0;
    for (int i = 0; i < block.size(); i++) {
      bits |= (uint64_t)(unsigned char)block[i] << ((7 - i) * 8);
    }
    return std::bitset<64>(bits);
  }


  /* * Función para convertir un bitset de 64 bits a una cadena de texto.
   * @param bits: El bitset de 64 bits a convertir.
   * @return Una cadena de texto representando el bloque.
   *
   * Ejemplo:
   * std::bitset<64> bits("0001001100110100010101110111100110011011101111001101111111110001");
   * std::string block = bitset64ToString(bits);
   */
  std::string 
  bitset64ToString(const std::bitset<64>& bits) {
    std::string result(8, '\0');
    uint64_t val = bits.to_ullong();

    for (int i = 0; i < 8; i++) {
      result[7 - i] = (val >> (i * 8)) & 0xFF;
    }

    return result;
  }


  /* * Función de decodificación que toma un bloque cifrado de 64 bits y lo descifra utilizando el algoritmo DES.
   * @param plaintext: El bloque cifrado de 64 bits a descifrar.
   * @return El bloque descifrado de 64 bits.
   *
   * Ejemplo:
   * std::bitset<64> ciphertext("0001001100110100010101110111100110011011101111001101111111110001");
   * std::bitset<64> decrypted = decode(ciphertext);
   */
  std::bitset<64> 
  decode(const std::bitset<64>& plaintext) {
    auto data = iPermutation(plaintext);
    std::bitset<32> left(data.to_ullong() >> 32);
    std::bitset<32> right(data.to_ullong());

    for (int round = 15; round >= 0; --round) {
      auto newRight = left ^ feistel(right, subkeys[round]);
      left = right;
      right = newRight;
    }
    uint64_t combined = (static_cast<uint64_t>(right.to_ullong()) << 32) | left.to_ullong();
    return fPermutation(std::bitset<64>(combined));
  }


private:
  std::bitset<64> key; // Clave de 64 bits (56 bits efectivos)
  std::vector<std::bitset<48>> subkeys; // Subclaves de 48 bits generadas a partir de la clave principal

  // Tabla de expansión simplificada (E)
  const int EXPANSION_TABLE[48] = {
      32, 1, 2, 3, 4, 5,
      4, 5, 6, 7, 8, 9,
      8, 9,10,11,12,13,
     12,13,14,15,16,17,
     16,17,18,19,20,21,
     20,21,22,23,24,25,
     24,25,26,27,28,29,
     28,29,30,31,32,1
  };

  // Permutación P simplificada (usar tabla real si se desea)
  const int P_TABLE[32] = {
      16, 7, 20, 21,29,12,28,17,
       1,15,23,26, 5,18,31,10,
       2, 8,24,14,32,27, 3, 9,
      19,13,30, 6,22,11, 4,25
  };

  // S-Box 1 (ejemplo simplificado)
  const int SBOX[4][16] = {
      {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
  };
};
