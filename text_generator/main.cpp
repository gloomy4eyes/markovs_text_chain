#include <iostream>

#include "MarkovsChain.h"
#include "Tokenizer.h"



int main(int argc, char *argv[]) {

  MarkovsChain mc(2);
  mc.riseDump("../mcdump.txt");
  std::cout << mc.generate("чтобы точно", 100) << std::endl;

  return 0;
}