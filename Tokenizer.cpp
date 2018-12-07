#include "Tokenizer.h"
#include <algorithm>
#include <cassert>
#include <cstring>
#include "Misc.h"

using char_t = std::string::value_type;

bool isSym(char sym);
char_t lowcase( char_t ch );

std::vector<std::string> Tokenizer::tokenize(const std::string &string) {
  assert(!string.empty());

  std::string chunk;
  std::vector<std::string> _tokens;
  for (auto & it : string) {
    if (!isSym(it)) {
      chunk.push_back(lowcase(it));
    } else {
      if (!chunk.empty()) {
        _tokens.push_back(chunk);
        chunk.clear();
      }
    }
  }
  if (!chunk.empty()) {
    _tokens.push_back(chunk);
    chunk.clear();
  }
  return _tokens;
}

typedef std::string::value_type char_t;
char_t upcase( char_t ch )
{
  return std::use_facet< std::ctype< char_t > >( std::locale() ).toupper( ch );
}

char_t lowcase( char_t ch )
{
  return std::use_facet< std::ctype< char_t > >( std::locale() ).tolower( ch );
}

void Tokenizer::toLower(std::string &str) {
  std::string result;
  std::transform(str.begin(), str.end(), std::back_inserter(result), lowcase);
  str = result;
}

bool isSym(char sym) {
  switch (sym) {
    case '\a':
    case '\b':
    case '\f':
    case '\n':
    case '\r':
    case '\t':
    case '\v':
    case ' ':
    case '.':
    case ',':
    case '<':
    case '>':
    case ':':
    case ';':
    case '!':
    case '?':
    case '/':
    case '\\':
    case '|':
    case ')':
    case '(':
    case '{':
    case '}':
    case '[':
    case ']':
    case '-':
    case '_':
    case '*':
    case '#':
    case '@':
    case '"':
    case '&':
    case '=':
    case '+':
    case '$':
    case '%':
    case '\'':
//    case '\200':
//    case '\224':
//    case '\342':
      return true;
    default:
      return false;
  }
}