#ifndef UGLY_JSON_PARSER_STRING_UTILS_HEADER
#define UGLY_JSON_PARSER_STRING_UTILS_HEADER

#include <string>
#include <xstring>
#include "..\Tokenizer\Tokens.hpp"

namespace UglyJSONParser
{
    namespace StringUtils
    {
        bool CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex);

        inline bool IsItDigit(const char token)
        {
            return Tokens::NumRangeStart <= token && Tokens::NumRangeEnd >= token;
        }

        inline bool IsItOpeningToken(const char token)
        {
            return token == Tokens::TokenObjectStart || token == Tokens::TokenArrayStart;
        }

        inline bool IsItClosingToken(const char token)
        {
            return token == Tokens::TokenObjectEnd || token == Tokens::TokenArrayEnd;
        }

        inline bool IsItSign(const char token)
        {
            return token == Tokens::TokenPlus || token == Tokens::TokenMinus;
        }

        inline bool Contains(const std::string& source, const char key)
        {
            return source.find(key) != std::string::npos;
        }
    }
}

#endif // !UGLY_JSON_PARSER_STRING_UTILS_HEADER