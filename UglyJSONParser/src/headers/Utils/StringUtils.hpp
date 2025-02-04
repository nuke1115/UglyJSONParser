#ifndef UGLY_JSON_PARSER_STRING_UTILS_HEADER
#define UGLY_JSON_PARSER_STRING_UTILS_HEADER

#include <string>
#include <xstring>

namespace UglyJSONParser
{
    namespace StringUtils
    {
        bool CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex);

        inline bool IsItDigit(const char token)
        {
            return '0' <= token && '9' >= token;
        }

        inline bool IsItOpeningToken(const char token)
        {
            return token == '{' || token == '[';
        }

        inline bool IsItClosingToken(const char token)
        {
            return token == '}' || token == ']';
        }

        inline bool IsItSign(const char token)
        {
            return token == '+' || token == '-';
        }

        inline bool Contains(const std::string& source, const char key)
        {
            return source.find(key) != std::string::npos;
        }
    }
}

#endif // !UGLY_JSON_PARSER_STRING_UTILS_HEADER