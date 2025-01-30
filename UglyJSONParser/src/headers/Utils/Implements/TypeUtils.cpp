#include "..\TypeUtils.hpp"


bool UglyJSONParser::TypeUtils::StrToBool(const std::string& data)
{
    return !data.compare("true");
}

std::string UglyJSONParser::TypeUtils::BoolToString(bool data)
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