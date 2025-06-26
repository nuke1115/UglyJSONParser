#include "../../Include/UglyJSONParser/JSONTree/NodeBase.hpp"

UglyJSONParser::BaseNode::BaseNode(string name, NodeType nodeType) : _nodeName(std::move(name)), _nodeType(nodeType) {}

UglyJSONParser::BaseNode::~BaseNode()
{

}


const std::string& UglyJSONParser::BaseNode::AsString() const
{
    throw std::logic_error(std::format("tried to get string data in {}",TypeUtils::GetNodeTypeName(_nodeType)));
}



long long UglyJSONParser::BaseNode::AsInt() const
{
    throw std::logic_error(std::format("tried to get int(long long) data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


bool UglyJSONParser::BaseNode::AsBool() const
{
    throw std::logic_error(std::format("tried to get bool data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


double UglyJSONParser::BaseNode::AsDouble() const
{
    throw std::logic_error(std::format("tried to get double(float) data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}

UglyJSONParser::BaseNode& UglyJSONParser::BaseNode::operator[](const std::string& strKey)
{
    if (_nodeType == NodeType::Array)
    {
        throw std::logic_error("tried to get child node by string index in ArrayNode");
    }
    else
    {
        throw std::logic_error(std::format("tried to get child node in {}", TypeUtils::GetNodeTypeName(_nodeType)));
    }
}

UglyJSONParser::BaseNode& UglyJSONParser::BaseNode::operator[](const size_t intKey)
{
    if (_nodeType == NodeType::Object)
    {
        throw std::logic_error("tried to get child node by int index in ObjectNode");
    }
    else
    {
        throw std::logic_error(std::format("tried to get child node in {}", TypeUtils::GetNodeTypeName(_nodeType)));
    }
}

void UglyJSONParser::BaseNode::operator=(const std::string& strData)
{
    throw std::logic_error(std::format("tried to insert string data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}

void UglyJSONParser::BaseNode::operator=(const char* strData)
{
    throw std::logic_error(std::format("tried to insert string data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}

void UglyJSONParser::BaseNode::operator=(const long long intData)
{
    throw std::logic_error(std::format("tried to insert int(long long) data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}

void UglyJSONParser::BaseNode::operator=(const bool boolData)
{
    throw std::logic_error(std::format("tried to insert bool data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}

void UglyJSONParser::BaseNode::operator=(const double doubleData)
{
    throw std::logic_error(std::format("tried to insert double(float) data in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::BaseNode::GetChildNodeVector()
{
    throw std::logic_error(std::format("tried to get child node vector in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


void UglyJSONParser::BaseNode::Clear()
{
    throw std::logic_error(std::format("tried to clear child nodes in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


void UglyJSONParser::BaseNode::DeleteChildNode(const std::string& strKey)
{
    if (_nodeType == NodeType::Array)
    {
        throw std::logic_error("tried to delete child node by string index in ArrayNode");
    }
    else
    {
        throw std::logic_error(std::format("tried to delete child node in {}", TypeUtils::GetNodeTypeName(_nodeType)));
    }
}


void UglyJSONParser::BaseNode::DeleteChildNode(size_t intKey)
{
    if (_nodeType == NodeType::Object)
    {
        throw std::logic_error("tried to delete child node by int index in ObjectNode");
    }
    else
    {
        throw std::logic_error(std::format("tried to delete child node in {}", TypeUtils::GetNodeTypeName(_nodeType)));
    }
}


bool UglyJSONParser::BaseNode::CreateNewNode(NodeType type, string strKey)
{
    throw std::logic_error(std::format("tried to create child node in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


bool UglyJSONParser::BaseNode::CreateNewNode(NodeType type)
{
    throw std::logic_error(std::format("tried to create child node in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


size_t UglyJSONParser::BaseNode::GetChildNodeCount() const
{
    throw std::logic_error(std::format("tried to get child node count in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}


bool UglyJSONParser::BaseNode::Contains(const string& key) const
{
    throw std::logic_error(std::format("tried to  in {}", TypeUtils::GetNodeTypeName(_nodeType)));
}