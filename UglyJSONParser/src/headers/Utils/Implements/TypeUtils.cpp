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

bool UglyJSONParser::TypeUtils::IsItJsonString(const std::string& key)
{
    return (key.front() == '"' && key.back() == '"');
}

bool UglyJSONParser::TypeUtils::IsItJsonValue(const std::string& key)
{
    return (
        IsItJsonString(key) ||
        (StringUtils::IsItNumber(key.front()) || key.front() == '+' || key.front() == '-') ||
        (StringUtils::CompareString(key,"true",0) || StringUtils::CompareString(key,"false",0)) ||
        StringUtils::CompareString(key,"null",0)
        );
}

