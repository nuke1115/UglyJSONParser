#ifndef UGLY_JSON_PARSER_STRING_UTILS_HEADER

#include <string>
#include <xstring>

namespace UglyJSONParser
{
    namespace StringUtils
    {
        bool CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex);

        bool IsItDigit(const char token);

        bool IsItOpeningToken(const char token);

        bool IsItClosingToken(const char token);

        bool IsItSign(const char token);

        bool Contains(const std::string& source, const char key);
    }
}

#endif // !UGLY_JSON_PARSER_STRING_UTILS_HEADER
