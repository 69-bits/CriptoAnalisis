#pragma once
#include "Prerequisites.h"

class
CaesarEncryption {
public:

  CaesarEncryption() = default;
  ~CaesarEncryption() = default;

  /* * Función para cifrar un texto utilizando el cifrado César.
   * @param texto: El texto a cifrar.
   * @param desplazamiento: El número de posiciones a desplazar cada carácter.
   * @return El texto cifrado.
   *
   * Ejemplo:
   * std::string texto = "Hola Mundo";
   * int desplazamiento = 3;
   * std::string cifrado = EncryptionCaesar(texto, desplazamiento);
   * // Resultado: "Krod Pxqgr"
  */

  std::string
  EncryptionCaesar(const std::string& texto, int desplazamiento) {
    std::string result = "";

    for (char c : texto) {
      if (c >= 'A' && c <= 'Z') {
        result += (char)(((c - 'A' + desplazamiento) % 26) + 'A');
      }
      else if (c >= 'a' && c <= 'z') {
        result += (char)(((c - 'a' + desplazamiento) % 26) + 'a');
      }
      else if (c >= '0' && c <= '9') {
        result += (char)(((c - '0' + desplazamiento) % 10) + '0');
      }
      else {
        result += c;
      }
    }
    return result;
  }

  /* * Función para descifrar un texto cifrado con el cifrado César.
   * @param texto: El texto a descifrar.
   * @param desplazamiento: El número de posiciones a desplazar cada carácter.
   * @return El texto descifrado.
   *
   * Ejemplo:
   * std::string texto = "Krod Pxqgr";
   * int desplazamiento = 3;
   * std::string descifrado = DecodeCaesar(texto, desplazamiento);
   * // Resultado: "Hola Mundo"
  */
  std::string
  DecodeCaesar(const std::string& texto, int desplazamiento) {
    return EncryptionCaesar(texto, 26 - (desplazamiento % 26));
  }

  /* * Función para realizar un ataque de fuerza bruta al cifrado César.
   * @param texto: El texto cifrado a descifrar.
   * Esta función intenta todas las posibles claves (0-25) y muestra los resultados.
   *
   * Ejemplo:
   * std::string texto = "Krod Pxqgr";
   * bruteForce(texto);
   */
  void
  bruteForce(const std::string& texto) {
    for (int i = 0; i < 26; i++) {
      std::string attempt = EncryptionCaesar(texto, 26 - i);
      std::cout << "Inteto: " << i << ": " << attempt << std::endl;
    }
  }

  /* * Función para evaluar una posible clave del cifrado César.
   * @param texto: El texto cifrado a evaluar.
   * @return La clave posible (0-25) basada en la frecuencia de letras.
   *
   * Ejemplo:
   * std::string texto = "Krod Pxqgr";
   * int clave = evaluatePossibleKey(texto);
   * // Resultado: 3 (si 'e' es la letra más frecuente)
  */
  int
  evaluatePossibleKey(const std::string& texto) {
    int frecuencias[26] = { 0 };


    for (char c : texto) {
      if (c >= 'A' && c <= 'Z') {
        frecuencias[c - 'A']++;
      }
      else if (c >= 'a' && c <= 'z') {

        frecuencias[c - 'a']++;
      }

    }

    /* Encuentra el índice de la letra más frecuente.
     * Asumimos que la letra 'e' es la más frecuente en inglés.
     * Calculamos la clave posible basándonos en esa suposición.
    */
    int indexMax = 0;
    for (int i = 0; i < 26; i++) {
      if (frecuencias[i] > frecuencias[0]) {
        indexMax = i;
      }
    }

    /* Calcula la clave posible restando el índice de 'e' (4) del índice máximo encontrado.
     * Ajustamos el resultado para que esté en el rango de 0 a 25.
     */
    int possibleKey = (indexMax - ('e' - 'a') + 26) % 26;
    return possibleKey;
  }

private:

};
