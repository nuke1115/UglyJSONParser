#include "../../Include/UglyJSONParser/Utils/TypeUtils.hpp"

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

const char* UglyJSONParser::TypeUtils::GetNodeTypeName(NodeType nodeType)
{
    switch (nodeType)
    {
    case NodeType::Null:
        return "Null";
    case NodeType::Object:
        return "Object";
    case NodeType::Array:
        return "Array";
    case NodeType::String:
        return "String";
    case NodeType::Number:
        return "Number";
    case NodeType::Bool:
        return "Bool";
    case NodeType::Root:
        return "Root";
    case NodeType::Error:
        return "Error";
    default:
        return "Invalid";
    }
}

const char* UglyJSONParser::TypeUtils::GetDataTypeName(DataTypes dataType)
{
    switch (dataType)
    {
    case DataTypes::FALSE_BIT:
        return "";
    case DataTypes::BOOL:
        return "bool";
    case DataTypes::INT:
        return "int(long long)";
    case DataTypes::DOUBLE:
        return "double(float)";
    case DataTypes::STRING:
        return "string";
    case DataTypes::NODE:
        return "node";
    case DataTypes::NODE_VECTOR:
        return "node vector";
    case DataTypes::NODE_EXISTENCE:
        return "node existence";
    case DataTypes::NODE_COUNT:
        return "node count";
    default:
        return "Invalid";
    }
}

const char* UglyJSONParser::TypeUtils::GetAccessTypeName(AccessTypes accessType)
{
    switch (accessType)
    {
    case AccessTypes::FALSE_BIT:
        return "";
    case AccessTypes::BY_INT:
        return "int";
    case AccessTypes::BY_STRING:
        return "string";
    default:
        return "Invalid";
    }
}

const char* UglyJSONParser::TypeUtils::GetOperationTypeName(OperationTypes opType)
{
    switch (opType)
    {
    case OperationTypes::FALSE_BIT:
        return "";
    case OperationTypes::INSERT:
        return "insert";
    case OperationTypes::GET:
        return "get";
    case OperationTypes::DELETE:
        return "delete";
    case OperationTypes::CREATE:
        return "create";
    default:
        return "Invalid";
    }
}
