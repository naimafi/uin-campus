
#include "uincampus/version.hpp"

#include <iostream>

int main() {
  std::cout << "UIN-Campus - Systeme de gestion academique\n";
  std::cout << "Version " << uin::version() << '\n';

  return 0;
}
