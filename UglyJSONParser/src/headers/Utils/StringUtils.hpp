#ifndef UGLY_JSON_PARSER_STRING_UTILS_HEADER

#include <string>

namespace UglyJSONParser
{
    namespace StringUtils
    {
        bool CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex);

        bool IsItNumber(const char token);

        bool IsItOpeningToken(const char token);

        bool IsItClosingToken(const char token);

        bool IsItSign(const char token);
    }
}

#endif // !UGLY_JSON_PARSER_STRING_UTILS_HEADER
