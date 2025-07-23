#include "../../Include/UglyJSONParser/JSONTree/NodeBase.hpp"

UglyJSONParser::BaseNode::BaseNode(string name, NodeType nodeType) : _nodeName(std::move(name)), _nodeType(nodeType) {}

UglyJSONParser::BaseNode::~BaseNode()
{

}


UglyJSONParser::UglyConstRefResult<std::string> UglyJSONParser::BaseNode::AsString() const
{
    return UglyConstRefResult<std::string>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::STRING,
        AccessTypes::FALSE_BIT,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}



UglyJSONParser::UglyNonRefResult<long long> UglyJSONParser::BaseNode::AsInt() const
{
    return UglyNonRefResult<long long>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::INT,
        AccessTypes::FALSE_BIT,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::AsBool() const
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::BOOL,
        AccessTypes::FALSE_BIT,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<double> UglyJSONParser::BaseNode::AsDouble() const
{
    return UglyNonRefResult<double>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::DOUBLE,
        AccessTypes::FALSE_BIT,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}

UglyJSONParser::UglyRefResult<UglyJSONParser::BaseNode> UglyJSONParser::BaseNode::operator[](const std::string& strKey)
{
    if (_nodeType == NodeType::Array)
    {
        return UglyRefResult<UglyJSONParser::BaseNode>(ResultUtils::MakeErrorBitmask(
            NodeType::Array,
            DataTypes::NODE,
            AccessTypes::BY_STRING,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    else
    {
        return UglyRefResult<UglyJSONParser::BaseNode>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
}

UglyJSONParser::UglyRefResult<UglyJSONParser::BaseNode> UglyJSONParser::BaseNode::operator[](const size_t intKey)
{
    if (_nodeType == NodeType::Object)
    {
        return UglyRefResult<UglyJSONParser::BaseNode>(ResultUtils::MakeErrorBitmask(
            NodeType::Object,
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    else
    {
        return UglyRefResult<UglyJSONParser::BaseNode>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::operator=(const std::string& strData)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::STRING,
        AccessTypes::FALSE_BIT,
        OperationTypes::INSERT,
        ErrorDescriptions::WRONG_TYPE
    ));
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::operator=(const char* strData)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::STRING,
        AccessTypes::FALSE_BIT,
        OperationTypes::INSERT,
        ErrorDescriptions::WRONG_TYPE
    ));
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::operator=(const long long intData)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::INT,
        AccessTypes::FALSE_BIT,
        OperationTypes::INSERT,
        ErrorDescriptions::WRONG_TYPE
    ));
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::operator=(const bool boolData)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::BOOL,
        AccessTypes::FALSE_BIT,
        OperationTypes::INSERT,
        ErrorDescriptions::WRONG_TYPE
    ));
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::operator=(const double doubleData)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::DOUBLE,
        AccessTypes::FALSE_BIT,
        OperationTypes::INSERT,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyRefResult<std::vector<UglyJSONParser::BaseNode*>> UglyJSONParser::BaseNode::GetChildNodeVector()
{
    return UglyRefResult<std::vector<UglyJSONParser::BaseNode*>>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE_VECTOR,
        AccessTypes::FALSE_BIT,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::Clear()
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE_VECTOR,
        AccessTypes::FALSE_BIT,
        OperationTypes::DELETE,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::DeleteChildNode(const std::string& strKey)
{
    if (_nodeType == NodeType::Array)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::Array,
            DataTypes::NODE,
            AccessTypes::BY_STRING,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    else
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::FALSE_BIT,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::DeleteChildNode(size_t intKey)
{
    if (_nodeType == NodeType::Object)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::Object,
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    else
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::FALSE_BIT,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::CreateNewNode(NodeType type, string strKey)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE,
        AccessTypes::BY_STRING,
        OperationTypes::CREATE,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::CreateNewNode(NodeType type)
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE,
        AccessTypes::BY_INT,
        OperationTypes::CREATE,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<size_t> UglyJSONParser::BaseNode::GetChildNodeCount() const
{
    return UglyNonRefResult<size_t>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE_COUNT,
        AccessTypes::FALSE_BIT,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}


UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BaseNode::Contains(const string& key) const
{
    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE_EXISTENCE,
        AccessTypes::BY_STRING,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}