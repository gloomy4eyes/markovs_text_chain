//
// Created by front on 30.11.2018.
//

#ifndef MARKOVS_TEXT_CHAIN_MISC_H
#define MARKOVS_TEXT_CHAIN_MISC_H

#include <array>
#include <algorithm>

//std::array<char, 56> UPPER_LET {'A', 'B', 'C', 'D', 'E','F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
//                            'А', 'Б' , 'В', 'Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я'};
//
//std::array<char, 56> LOWER_LET {'a', 'b', 'c', 'd', 'e','f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
//                            'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я'};
//
//
//void toLower(std::string & str) {
//  for (auto & s : str) {
//    for (int i = 0; i < UPPER_LET.size(); ++i) {
//      if (s == UPPER_LET[i]) {
//        s = LOWER_LET[i];
//        break;
//      }
//    }
//  }
//}
//
//void toUpper(std::string& str) {
//  for (auto & s : str) {
//    for (int i = 0; i < LOWER_LET.size(); ++i) {
//      if (s == LOWER_LET[i]) {
//        s = UPPER_LET[i];
//        break;
//      }
//    }
//  }
//}

#endif //MARKOVS_TEXT_CHAIN_MISC_H
