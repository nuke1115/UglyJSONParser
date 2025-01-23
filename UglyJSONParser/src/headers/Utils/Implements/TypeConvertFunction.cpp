#include "..\TypeConvertFunction.hpp"

bool UglyJSONParser::StrToBool(const std::string& data)
{
    return !data.compare("true");
}

std::string UglyJSONParser::BoolToString(bool data)
{
    if (data)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}