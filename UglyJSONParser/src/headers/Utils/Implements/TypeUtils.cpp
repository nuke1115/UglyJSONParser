#include "..\TypeUtils.hpp"

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
    else if (IsItSingleJsonValue(token) && token.compare("null"))
    {
        return NodeType::SingleValue;
    }
    else
    {
        return NodeType::Error;
    }
}