#include <gtest/gtest.h>
#include "tokenizer/Tokenizer.h"


TEST(test_tokenizer, tolower_test) {
  std::wstring ts(L"ТЕСТ");
  Tokenizer::toLower(ts);
  std::wcout << ts << std::endl;
}

int main (int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}