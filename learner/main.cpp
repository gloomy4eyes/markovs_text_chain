#include <iostream>
#include "Learner.h"

void help();

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  setlocale(LC_CTYPE, "C");

  try {
    Learner learner(argc, argv);
    learner.run();
  } catch (const std::exception &exc) {
    std::cerr << exc.what() << std::endl;
    help();
  }

  return 0;
}

void help() {
  std::cout << "usage:\n\t--urls \'file with urls\' --chaincount \' \' --mcdump \'file for markovs chain dump\'";
}