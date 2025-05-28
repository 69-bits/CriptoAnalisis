#include "Prerequisites.h"
#include "XOREncoder.h"
#include "AsciiBinary.h"

int main() {
  /*XOREncoder encoder;

  std::string mensaje = "Garfield";
  std::string clave = "clave";

  std::cout << "Mensaje original: " << mensaje << std::endl;
  std::string mensajeCodificado = encoder.encode(mensaje, clave);

  std::cout << "Mensaje codificado: " << mensajeCodificado << std::endl;
  std::string decodificado = encoder.encode(mensajeCodificado, clave);

  std::cout << "Mensaje decodificado: " << decodificado << std::endl;

  std::vector<unsigned char> bytesCifrados(mensaje.begin(), mensaje.end());

  std::cout << "\n--- Fuerza bruta 1 byte con filtro ---\n";
  encoder.bruteForce_1Byte(bytesCifrados);

  std::cout << "\n--- Fuerza bruta 2 byte con filtro ---\n";
  encoder.bruteForce_2Byte(bytesCifrados);

  encoder.printHex(mensajeCodificado);
  return 0;*/

  AsciiBinary asciiBinary;
  std::string mensaje = "Garfield";
  std::string mensajeBinario = asciiBinary.stringToBinary(mensaje);
  std::cout << "Mensaje Binario: " << mensajeBinario << std::endl;
  std::string mensajeDecodificado = asciiBinary.binaryToString(mensajeBinario);
  std::cout << "Mensaje Decodificado: " << mensajeDecodificado << std::endl;

  return 0;
}

