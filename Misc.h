//
// Created by front on 30.11.2018.
//

#ifndef MARKOVS_TEXT_CHAIN_MISC_H
#define MARKOVS_TEXT_CHAIN_MISC_H

#include <array>
#include <algorithm>

constexpr auto UPPER_LET = {'A', 'B', 'C', 'D'};

constexpr auto LOWER_LET = {'a', 'b', 'c', 'd'};

void toLower(std::string & str) {
  for (auto & s : str) {
    std::find(UPPER_LET.begin(), LOWER_LET.end(), s);
//    if (s == UPPER_LET) {
//
//    }
  }
}

#endif //MARKOVS_TEXT_CHAIN_MISC_H
