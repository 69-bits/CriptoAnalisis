#include "Prerequisites.h"
#include "CryptoGenerator.h"


int
main() {
  CryptoGenerator cryptoGen;

  auto topPasswords = cryptoGen.getTopPasswords(10, 3);
  std::cout << "Top 3 contraseñas por entropia:\n";

  for (const auto& entry : topPasswords) {
    std::string pass = entry.first;
    double entropy = entry.second;

    std::cout << "- " << pass << " (Entropia: " << entropy << " bits)\n";
  }

  return 0;
}

