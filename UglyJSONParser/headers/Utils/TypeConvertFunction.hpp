#ifndef UGLY_JSON_PARSER_TYPE_CONVERT_FUNCTION_HEADER
#define UGLY_JSON_PARSER_TYPE_CONVERT_FUNCTION_HEADER

#include <string>


namespace UglyJSONParser
{
    bool StrToBool(const std::string& data);

    std::string BoolToString(bool data);
}

#endif // !UGLY_JSON_PARSER_TYPE_CONVERT_FUNCTION_HEADER
