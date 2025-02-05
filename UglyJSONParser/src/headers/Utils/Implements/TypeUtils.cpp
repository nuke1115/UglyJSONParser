#include "..\TypeUtils.hpp"

std::string UglyJSONParser::TypeUtils::BoolToString(bool data)
{
    if (data)
    {
        return Tokens::TokenTrue;
    }
    else
    {
        return Tokens::TokenFalse;
    }
}

UglyJSONParser::NodeType UglyJSONParser::TypeUtils::GetNodeTypeOfToken(const std::string& token)
{
    if (token.front() == Tokens::TokenObjectStart)
    {
        return NodeType::Object;
    }
    else if (token.front() == Tokens::TokenArrayStart)
    {
        return NodeType::Array;
    }
    else if (!token.compare(Tokens::TokenNull))
    {
        return NodeType::Null;
    }
    else if (IsItSingleJsonValue(token) && token.compare(Tokens::TokenNull))
    {
        return NodeType::SingleValue;
    }
    else
    {
        return NodeType::Error;
    }
}