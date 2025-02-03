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
        (StringUtils::IsItDigit(key.front()) || StringUtils::IsItSign(key.front())) ||
        IsItJsonBool(key) ||
        StringUtils::CompareString(key,"null",0)
        );
}

bool UglyJSONParser::TypeUtils::IsItJsonBool(const std::string& key)
{
    return !key.compare("true") || !key.compare("false");
}

UglyJSONParser::NodeType UglyJSONParser::TypeUtils::GetNodeTypeOfToken(const std::string& token)
{
    if (token.front() == '{')
    {
        return NodeType::Object;
    }
    else if (token.front() == '[')
    {
        return NodeType::Array;
    }
    else if (!token.compare("null"))
    {
        return NodeType::Null;
    }
    else if (IsItJsonValue(token) && token.compare("null"))
    {
        return NodeType::SingleValue;
    }
    else
    {
        return NodeType::Error;
    }
}
/*
Null = 0,
Object = 1,
Array = 2,
SingleValue = 3,
Root = 4,
Error = -1
*/