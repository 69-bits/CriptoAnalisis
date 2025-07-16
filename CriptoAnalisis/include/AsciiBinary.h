#include "Prerequisites.h"

class
    AsciiBinary {
public:
    AsciiBinary() = default;
    ~AsciiBinary() = default;


    /* * Convierte una cadena de texto a su representaci�n binaria.
   * Cada car�cter se convierte a un string de 8 bits.
   * @param input: La cadena de texto a convertir.
   * @return La representaci�n binaria de la cadena.
   *
   * Ejemplo:
   * std::string mensaje = "Garfield";
   * std::string mensajeBinario = stringToBinary(mensaje);
   * // Resultado: "01000111 01100001 01110010 01100110 01101001 01100101 01101100 01100100 "
  */
    std::string
    stringToBinary(const std::string& input) {
        std::ostringstream oss;
        for (char c : input) {
            oss << bitset(c) << " ";
        }
        return oss.str();
    }


    /* * Convierte una cadena binaria a su representaci�n de texto.
   * Cada grupo de 8 bits se convierte a un car�cter.
   * @param binaryInput: La cadena binaria a convertir.
   * @return La representaci�n de texto de la cadena binaria.
   *
   * Ejemplo:
   * std::string mensajeBinario = "01000111 01100001 01110010 01100110 01101001 01100101 01101100 01100100 ";
   * std::string mensajeDecodificado = binaryToString(mensajeBinario);
   * // Resultado: "Garfield"
  */
    char
    binaryToChar(const std::string& binary) {
        int value = 0;
        for (char bit : binary) {
            value = value * 2 + (bit - '0');
        }
        return static_cast<char>(value);
    }


    /* * Convierte una cadena binaria a su representaci�n de texto.
   * Cada grupo de 8 bits se convierte a un car�cter.
   * @param binaryInput: La cadena binaria a convertir.
   * @return La representaci�n de texto de la cadena binaria.
   *
   * Ejemplo:
   * std::string mensajeBinario = "01000111 01100001 01110010 01100110 01101001 01100101 01101100 01100100 ";
   * std::string mensajeDecodificado = binaryToString(mensajeBinario);
   * // Resultado: "Garfield"
  */
    std::string
    binaryToString(const std::string& binaryInput) {
        std::istringstream iss(binaryInput);
        std::string result;
        std::string binary;
        while (iss >> binary) {
            result += binaryToChar(binary);
        }
        return result;
    }

private:

    /* * Convierte un car�cter a su representaci�n binaria de 8 bits.
   * @param c: El car�cter a convertir.
   * @return Un string de 8 bits representando el car�cter.
   *
   * Ejemplo:
   * char c = 'A';
   * std::string binary = bitset(c);
   * // Resultado: "01000001"
  */
    std::string
    bitset(char c) {
        std::string result(8, '0');
        int value = static_cast<unsigned char>(c);
        for (int i = 7; i >= 0; --i) {
            if (value % 2 == 1) {
                result[i] = '1';
            }
            value /= 2;
        }
        return result;
    }
};
