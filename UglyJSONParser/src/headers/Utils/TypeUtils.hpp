#ifndef UGLY_JSON_PARSER_TYPE_UTILS_HEADER

#include <string>


namespace UglyJSONParser
{
    namespace TypeUtils
    {
        bool StrToBool(const std::string& data);

        std::string BoolToString(bool data);
    }
}

#endif // !UGLY_JSON_PARSER_TYPE_UTILS_HEADER
