#include "../../Include/UglyJSONParser/JSONTree/NodeBase.hpp"

UglyJSONParser::BaseNode::BaseNode(string name, NodeType nodeType) : _nodeName(std::move(name)), _nodeType(nodeType) {}

UglyJSONParser::BaseNode::~BaseNode()
{

}