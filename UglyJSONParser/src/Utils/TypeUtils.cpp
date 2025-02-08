#include "..\..\Include\UglyJSONParser\Utils\TypeUtils.hpp"

std::string UglyJSONParser::TypeUtils::ConvertBoolToString(bool data)
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
    else if (IsItJsonBool(token))
    {
        return NodeType::Bool;
    }
    else if (IsItJsonString(token))
    {
        return NodeType::String;
    }
    else if ((StringUtils::IsItDigit(token.front()) || StringUtils::IsItSign(token.front())) && StringUtils::IsItDigit(token.back()))
    {
        return NodeType::Number;
    }
    else
    {
        return NodeType::Error;
    }
}