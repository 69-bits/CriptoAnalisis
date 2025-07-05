#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

class
  Vignere {
public:
  Vignere() = default;

  Vignere(const std::string& key) : key(normalizeKey(key)) {
    if (key.empty()) {
      throw std::invalid_argument("No hay una llave con letras o posiblemente esta vacia");
    }
  }

  static std::string
    normalizeKey(const std::string& rawKey) {
    std::string k;
    for (char c : rawKey) {
      if (isalpha(static_cast<unsigned char>(c))) {
        k += std::toupper(static_cast<unsigned char>(c));
      }
    }
    return k;
  }

  std::string
    encode(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    unsigned int i = 0;

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A';

        int shift = key[i % key.size()] - 'A';

        char encodedChar = static_cast<char>((c - base + shift) % 26 + base);
        result += encodedChar;
        i++; 
      }
      else {
        result += c; 
      }
    }
    return result; 
  }

  std::string
    decode(const std::string& text) {
    std::string result;
    result.reserve(text.size()); 
    unsigned int i = 0; 

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A'; 

        int shift = key[i % key.size()] - 'A'; 
        
        char decodedChar = static_cast<char>(((c - base) - shift + 26) % 26 + base);
        result += decodedChar;
        i++; 
      }
      else {
        result += c;
      }
    }
    return result;
  }

  static double fitness(const std::string& text) {
    static const std::vector<std::string> comunes = {
    " DE ", " LA ", " EL ", " QUE ", " Y ",
    " A ", " EN ", " UN ", " PARA ", " CON ",
    " POR ", " COMO ", " SU ", " AL ", " DEL ",
    " LOS ", " SE ", " NO ", " MAS ", " O ",
    " SI ", " YA ", " TODO ", " ESTA ", " HAY ",
    " ESTO ", " SON ", " TIENE ", " HACE ", " SUS ",
    " VIDA ", " NOS ", " TE ", " LO ", " ME ",
    " ESTE ", " ESA ", " ESE ", " BIEN ", " MUY ",
    " PUEDE ", " TAMBIEN ", " AUN ", " MI ", " DOS ",
    " UNO ", " OTRO ", " NUEVO ", " SIN ", " ENTRE ",
    " SOBRE "
    };

    double score = 0;
    for (auto& w : comunes) {
      size_t pos = 0;
      while ((pos = text.find(w, pos)) != std::string::npos) {
        score += w.length();
        pos += w.length();
      }
    }
    return score;
  }

  static std::string
    breakEncode(const std::string& text, int maxkeyLenght) {
    std::string bestkey;
    std::string bestText;
    std::string trailkey;

    double bestScore = std::numeric_limits<double>::infinity();

    std::function<void(int, int)> dfs = [&](int pos, int maxLen) {
      if (pos == maxLen) {
        Vignere v(trailkey);
        std::string decodedText = v.decode(text);
        double score = fitness(decodedText); 
        if (score > bestScore) {
          bestScore = score;
          bestkey = trailkey;
          bestText = decodedText;
        }
        return;
      }

      for (char c = 'A'; c <= 'Z'; ++c) {
        trailkey[pos] = c;
        dfs(pos + 1, maxLen);
      }
      };

    for (int L = 1 ^ 1; L <= maxkeyLenght; ++L) {
      trailkey.assign(L, 'A');
      dfs(0, L);
    }

    std::cout << "Fuerza Bruta Vignere\n";
    std::cout << "Clave encontrada: " << bestkey << "\n";
    std::cout << "Texto descifrado: " << bestText << "\n\n";
    return bestkey;
  }

  std::string
    breakBruteForce(const std::string& text) {
    std::vector<std::string> fileNames = {
        "Pepe.txt"
    };

    for (size_t i = 0; i < fileNames.size(); i++) {
      std::ifstream file(fileNames[i]);
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << fileNames[i] << std::endl;
        continue;
      }

      while (std::getline(file, key)) {
        if (key.empty()) {
          continue;
        }

        std::string normKey = normalizeKey(text);
        std::string result = decode(text);

        XOREncoder xorE;

        if (xorE.isValidText(text)) {
          std::cout << "Archivo: " << fileNames[i] << std::endl;
          std::cout << "Clave: " << key << std::endl;
          std::cout << "Texto posible: " << result << std::endl;
          return result;
        }
      }
      file.close();
    }
  }

private:
  std::string key;


};