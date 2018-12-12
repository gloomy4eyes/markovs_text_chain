#include <iostream>

#include "markovs_chain/MarkovsChain.h"
#include <tokenizer/Tokenizer.h>



int main(int argc, char *argv[]) {

  MarkovsChain mc(5);
  mc.riseDump("");
//  std::cout << mc.generate("", 100) << std::endl;

  return 0;
}