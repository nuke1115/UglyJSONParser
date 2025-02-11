#include "..\..\Include\UglyJSONParser\JsonTree\Node.hpp"


#pragma region Constructors

UglyJSONParser::StringNode::StringNode(string name) : BaseNode(std::move(name), NodeType::String)
{
}

UglyJSONParser::NumberNode::NumberNode(string name) : BaseNode(std::move(name), NodeType::Number)
{
}

UglyJSONParser::BoolNode::BoolNode(string name) : BaseNode(std::move(name), NodeType::Bool)
{
}

UglyJSONParser::ObjectNode::ObjectNode(string name) : BaseNode(std::move(name), NodeType::Object)
{
}

UglyJSONParser::ArrayNode::ArrayNode(string name) : BaseNode(std::move(name), NodeType::Array)
{
}

UglyJSONParser::NullNode::NullNode(string name) : BaseNode(name, NodeType::Null)
{
}

UglyJSONParser::RootNode::RootNode() : BaseNode("root", NodeType::Root)
{
    _entryPoint = nullptr;
}

#pragma endregion

#pragma region Destructors

UglyJSONParser::StringNode::~StringNode()
{
}

UglyJSONParser::NumberNode::~NumberNode()
{
}

UglyJSONParser::BoolNode::~BoolNode()
{
}

UglyJSONParser::ObjectNode::~ObjectNode()
{
    Clear();
}

UglyJSONParser::ArrayNode::~ArrayNode()
{
    Clear();
}

UglyJSONParser::NullNode::~NullNode()
{
}

UglyJSONParser::RootNode::~RootNode()
{
    if (_entryPoint != nullptr)
    {
        _entryPoint->Clear();
        delete _entryPoint;
        _entryPoint = nullptr;
    }
}
#pragma endregion

#pragma region StringNode

std::string UglyJSONParser::StringNode::GetJsonTreeByString()
{
    std::ostringstream buffer;

    buffer << Tokens::TokenQuotationMark << _stringData << Tokens::TokenQuotationMark;

    return buffer.str();
}

const std::string& UglyJSONParser::StringNode::AsString() const
{
    return _stringData;
}

long long UglyJSONParser::StringNode::AsInt() const
{
    throw std::logic_error("tried to convert string data to number data");
}

bool UglyJSONParser::StringNode::AsBool() const
{
    throw std::logic_error("tried to convert string data to bool data");
}

double UglyJSONParser::StringNode::AsDouble() const
{
    throw std::logic_error("tried to convert string data to number data");
}

UglyJSONParser::BaseNode& UglyJSONParser::StringNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

UglyJSONParser::BaseNode& UglyJSONParser::StringNode::operator[](const size_t intKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

void UglyJSONParser::StringNode::operator=(const char* strData)
{
    _stringData = strData;
}

void UglyJSONParser::StringNode::operator=(const string& strData)
{
    _stringData = strData;
}

void UglyJSONParser::StringNode::operator=(const long long intData)
{
    throw std::logic_error("tried to set number data to string node");
}

void UglyJSONParser::StringNode::operator=(const bool boolData)
{
    throw std::logic_error("tried to set bool data to string node");
}

void UglyJSONParser::StringNode::operator=(const double doubleData)
{
    throw std::logic_error("tried to set number data to string node");
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::StringNode::GetChildNodeVector()
{
    throw std::logic_error("tried to get child node vector in leaf node");
}

void UglyJSONParser::StringNode::Clear()
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::StringNode::DeleteChildNode(const string& strKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::StringNode::DeleteChildNode(size_t intKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

bool UglyJSONParser::StringNode::CreateNewNode(NodeType type, string strKey)
{
    throw std::logic_error("tried to create child node in leaf node");
}

bool UglyJSONParser::StringNode::CreateNewNode(NodeType type)
{
    throw std::logic_error("tried to create child node in leaf node");
}

size_t UglyJSONParser::StringNode::GetChildNodeCount() const
{
    return 0;
}

bool UglyJSONParser::StringNode::Contains(const string& key) const
{
    return false;
}

#pragma endregion

#pragma region NumberNode

std::string UglyJSONParser::NumberNode::GetJsonTreeByString()
{
    if (_isItDouble)
    {
        return std::to_string(_doubleData);
    }
    else
    {
        return std::to_string(_intData);
    }
}

const std::string& UglyJSONParser::NumberNode::AsString() const
{
    throw std::logic_error("tried to convert number data to string data");
}

long long UglyJSONParser::NumberNode::AsInt() const
{
    if (_isItDouble)
    {
        return static_cast<long long>(_doubleData);
    }
    else
    {
        return _intData;
    }
}

bool UglyJSONParser::NumberNode::AsBool() const
{
    throw std::logic_error("tried to convert number data to bool data");
}

double UglyJSONParser::NumberNode::AsDouble() const
{
    if (_isItDouble)
    {
        return _doubleData;
    }
    else
    {
        return static_cast<double>(_intData);
    }
}

UglyJSONParser::BaseNode& UglyJSONParser::NumberNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

UglyJSONParser::BaseNode& UglyJSONParser::NumberNode::operator[](const size_t intKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

void UglyJSONParser::NumberNode::operator=(const char* strData)
{
    throw std::logic_error("tried to set string data to number node");
}

void UglyJSONParser::NumberNode::operator=(const string& strData)
{
    throw std::logic_error("tried to set string data to number node");
}

void UglyJSONParser::NumberNode::operator=(const long long intData)
{
    _isItDouble = false;
    _intData = intData;
}

void UglyJSONParser::NumberNode::operator=(const bool boolData)
{
    throw std::logic_error("tried to set bool data to number node");
}

void UglyJSONParser::NumberNode::operator=(const double doubleData)
{
    _isItDouble = true;
    _doubleData = doubleData;
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::NumberNode::GetChildNodeVector()
{
    throw std::logic_error("tried to get child node vector in leaf node");
}

void UglyJSONParser::NumberNode::Clear()
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::NumberNode::DeleteChildNode(const string& strKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::NumberNode::DeleteChildNode(size_t intKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

bool UglyJSONParser::NumberNode::CreateNewNode(NodeType type, string strKey)
{
    throw std::logic_error("tried to create child node in leaf node");
}

bool UglyJSONParser::NumberNode::CreateNewNode(NodeType type)
{
    throw std::logic_error("tried to create child node in leaf node");
}

size_t UglyJSONParser::NumberNode::GetChildNodeCount() const
{
    return 0;
}

bool UglyJSONParser::NumberNode::Contains(const string& key) const
{
    return false;
}

#pragma endregion

#pragma region BoolNode

std::string UglyJSONParser::BoolNode::GetJsonTreeByString()
{
    return TypeUtils::ConvertBoolToString(_boolData);
}

const std::string& UglyJSONParser::BoolNode::AsString() const
{
    throw std::logic_error("tried to convert bool data to string data");
}

long long UglyJSONParser::BoolNode::AsInt() const
{
    throw std::logic_error("tried to convert bool data to number data");
}

bool UglyJSONParser::BoolNode::AsBool() const
{
    return _boolData;
}

double UglyJSONParser::BoolNode::AsDouble() const
{
    throw std::logic_error("tried to convert bool data to number data");
}

UglyJSONParser::BaseNode& UglyJSONParser::BoolNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

UglyJSONParser::BaseNode& UglyJSONParser::BoolNode::operator[](const size_t intKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

void UglyJSONParser::BoolNode::operator=(const char* strData)
{
    throw std::logic_error("tried to set string data to bool node");
}

void UglyJSONParser::BoolNode::operator=(const string& strData)
{
    throw std::logic_error("tried to set string data to bool node");
}

void UglyJSONParser::BoolNode::operator=(const long long intData)
{
    throw std::logic_error("tried to set number data to bool node");
}

void UglyJSONParser::BoolNode::operator=(const bool boolData)
{
    _boolData = boolData;
}

void UglyJSONParser::BoolNode::operator=(const double doubleData)
{
    throw std::logic_error("tried to set number data to bool node");
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::BoolNode::GetChildNodeVector()
{
    throw std::logic_error("tried to get child node vector in leaf node");
}

void UglyJSONParser::BoolNode::Clear()
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::BoolNode::DeleteChildNode(const string& strKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::BoolNode::DeleteChildNode(size_t intKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

bool UglyJSONParser::BoolNode::CreateNewNode(NodeType type, string strKey)
{
    throw std::logic_error("tried to create child node in leaf node");
}

bool UglyJSONParser::BoolNode::CreateNewNode(NodeType type)
{
    throw std::logic_error("tried to create child node in leaf node");
}

size_t UglyJSONParser::BoolNode::GetChildNodeCount() const
{
    return 0;
}

bool UglyJSONParser::BoolNode::Contains(const string& key) const
{
    return false;
}

#pragma endregion

#pragma region ObjectNode

std::string UglyJSONParser::ObjectNode::GetJsonTreeByString()
{
    std::ostringstream buffer;

    buffer << Tokens::TokenObjectStart;

    for (BaseNode* i : _childNodeVector)
    {
        buffer << Tokens::TokenQuotationMark << i->GetName() << Tokens::TokenQuotationMark << Tokens::TokenColon;

        buffer << (i->GetJsonTreeByString());

        if (i != _childNodeVector.back())
        {
            buffer << Tokens::TokenComma;
        }
    }

    buffer << Tokens::TokenObjectEnd;

    return buffer.str();
}

const std::string& UglyJSONParser::ObjectNode::AsString() const
{
    throw std::logic_error("tried to access data in parent node");
}

long long UglyJSONParser::ObjectNode::AsInt() const
{
    throw std::logic_error("tried to access data in parent node");
}

bool UglyJSONParser::ObjectNode::AsBool() const
{
    throw std::logic_error("tried to access data in parent node");
}

double UglyJSONParser::ObjectNode::AsDouble() const
{
    throw std::logic_error("tried to access data in parent node");
}

UglyJSONParser::BaseNode& UglyJSONParser::ObjectNode::operator[](const string& strKey)
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(strKey)))
        {
            return *i;
        }
    }

    throw std::logic_error("item not found");
}

UglyJSONParser::BaseNode& UglyJSONParser::ObjectNode::operator[](const size_t intKey)
{
    throw std::logic_error("tried to access by int index in object node");
}

void UglyJSONParser::ObjectNode::operator=(const char* strData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ObjectNode::operator=(const string& strData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ObjectNode::operator=(const long long intData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ObjectNode::operator=(const bool boolData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ObjectNode::operator=(const double doubleData)
{
    throw std::logic_error("tried to insert data in parent node");
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::ObjectNode::GetChildNodeVector()
{
    return _childNodeVector;
}

void UglyJSONParser::ObjectNode::Clear()
{
    for (BaseNode* i : _childNodeVector)
    {
        if (i->GetNodeType() == NodeType::Object || i->GetNodeType() == NodeType::Array)//null, string, bool, number면 안된다
        {
            i->Clear();
        }

        delete i;
    }
    _childNodeVector.clear();
}

void UglyJSONParser::ObjectNode::DeleteChildNode(const string& strKey)
{
    for (size_t i = 0; i < _childNodeVector.size(); i++)
    {
        if (!(_childNodeVector[i]->GetName().compare(strKey)))
        {
            delete _childNodeVector[i];
            _childNodeVector.erase(_childNodeVector.begin() + i);
            return;
        }
    }
    throw std::logic_error("item not found");
}

void UglyJSONParser::ObjectNode::DeleteChildNode(size_t intKey)
{
    throw std::logic_error("tried to access by int index in object node");
}

bool UglyJSONParser::ObjectNode::CreateNewNode(NodeType type, string strKey)
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(strKey)))
        {
            return false;
        }
    }

    BaseNode* newNode = _factory.CreateNode(type, std::move(strKey));

    if (newNode == nullptr)
    {
        return false;
    }

    _childNodeVector.push_back(newNode);

    return true;
}

bool UglyJSONParser::ObjectNode::CreateNewNode(NodeType type)
{
    return false;
}

size_t UglyJSONParser::ObjectNode::GetChildNodeCount() const
{
    return _childNodeVector.size();
}

bool UglyJSONParser::ObjectNode::Contains(const string& key) const
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(key)))
        {
            return true;
        }
    }
    return false;
}

#pragma endregion

#pragma region ArrayNode

std::string UglyJSONParser::ArrayNode::GetJsonTreeByString()
{
    std::ostringstream buffer;

    buffer << Tokens::TokenArrayStart;

    for (BaseNode* i : _childNodeVector)
    {

        buffer << (i->GetJsonTreeByString());

        if (i != _childNodeVector.back())
        {
            buffer << Tokens::TokenComma;
        }
    }

    buffer << Tokens::TokenArrayEnd;

    return buffer.str();
}

const std::string& UglyJSONParser::ArrayNode::AsString() const
{
    throw std::logic_error("tried to access data in parent node");
}

long long UglyJSONParser::ArrayNode::AsInt() const
{
    throw std::logic_error("tried to access data in parent node");
}

bool UglyJSONParser::ArrayNode::AsBool() const
{
    throw std::logic_error("tried to access data in parent node");
}

double UglyJSONParser::ArrayNode::AsDouble() const
{
    throw std::logic_error("tried to access data in parent node");
}

UglyJSONParser::BaseNode& UglyJSONParser::ArrayNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to access by string index in array node");
}

UglyJSONParser::BaseNode& UglyJSONParser::ArrayNode::operator[](const size_t intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        throw std::logic_error("index exceeded array bound");
    }
    return *_childNodeVector[intKey];
}

void UglyJSONParser::ArrayNode::operator=(const char* strData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ArrayNode::operator=(const string& strData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ArrayNode::operator=(const long long intData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ArrayNode::operator=(const bool boolData)
{
    throw std::logic_error("tried to insert data in parent node");
}

void UglyJSONParser::ArrayNode::operator=(const double doubleData)
{
    throw std::logic_error("tried to insert data in parent node");
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::ArrayNode::GetChildNodeVector()
{
    return _childNodeVector;
}

void UglyJSONParser::ArrayNode::Clear()
{
    for (BaseNode* i : _childNodeVector)
    {
        if (i->GetNodeType() == NodeType::Object || i->GetNodeType() == NodeType::Array)
        {
            i->Clear();
        }

        delete i;
    }
    _childNodeVector.clear();
}

void UglyJSONParser::ArrayNode::DeleteChildNode(const string& strKey)
{
    throw std::logic_error("tried to access by string index in array node");
}

void UglyJSONParser::ArrayNode::DeleteChildNode(size_t intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        throw std::logic_error("index exceeded array bound");
    }

    delete _childNodeVector[intKey];
    _childNodeVector.erase(_childNodeVector.begin() + intKey);
}

bool UglyJSONParser::ArrayNode::CreateNewNode(NodeType type, string strKey)
{
    return CreateNewNode(type);
}

bool UglyJSONParser::ArrayNode::CreateNewNode(NodeType type)
{
    BaseNode* tmp = _factory.CreateNode(type, "nullName");

    if (tmp == nullptr)
    {
        return false;   
    }

    _childNodeVector.push_back(tmp);
    return true;
}

size_t UglyJSONParser::ArrayNode::GetChildNodeCount() const
{
    return _childNodeVector.size();
}

bool UglyJSONParser::ArrayNode::Contains(const string& key) const
{
    return false;
}

#pragma endregion

#pragma region NullNode

std::string UglyJSONParser::NullNode::GetJsonTreeByString()
{
    return Tokens::TokenNull;
}

const std::string& UglyJSONParser::NullNode::AsString() const
{
    throw std::logic_error("tried to get data in null node");
}

long long UglyJSONParser::NullNode::AsInt() const
{
    throw std::logic_error("tried to get data in null node");
}

bool UglyJSONParser::NullNode::AsBool() const
{
    throw std::logic_error("tried to get data in null node");
}

double UglyJSONParser::NullNode::AsDouble() const
{
    throw std::logic_error("tried to get data in null node");
}

UglyJSONParser::BaseNode& UglyJSONParser::NullNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to get child node in null node");
}

UglyJSONParser::BaseNode& UglyJSONParser::NullNode::operator[](const size_t intKey)
{
    throw std::logic_error("tried to get child node in null node");
}

void UglyJSONParser::NullNode::operator=(const char* strData)
{
    throw std::logic_error("tried to insert data in null node");
}

void UglyJSONParser::NullNode::operator=(const string& strData)
{
    throw std::logic_error("tried to insert data in null node");
}

void UglyJSONParser::NullNode::operator=(const long long intData)
{
    throw std::logic_error("tried to insert data in null node");
}

void UglyJSONParser::NullNode::operator=(const bool boolData)
{
    throw std::logic_error("tried to insert data in null node");
}

void UglyJSONParser::NullNode::operator=(const double doubleData)
{
    throw std::logic_error("tried to insert data in null node");
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::NullNode::GetChildNodeVector()
{
    throw std::logic_error("tried to get child node in null node");
}

void UglyJSONParser::NullNode::Clear()
{
    throw std::logic_error("tried to delete child node in null node");
}

void UglyJSONParser::NullNode::DeleteChildNode(const string& strKey)
{
    throw std::logic_error("tried to delete child node in null node");
}

void UglyJSONParser::NullNode::DeleteChildNode(size_t intKey)
{
    throw std::logic_error("tried to delete child node in null node");
}

bool UglyJSONParser::NullNode::CreateNewNode(NodeType type, string strKey)
{
    throw std::logic_error("tried to create child node in null node");
}

bool UglyJSONParser::NullNode::CreateNewNode(NodeType type)
{
    throw std::logic_error("tried to create child node in null node");
}

size_t UglyJSONParser::NullNode::GetChildNodeCount() const
{
    return 0;
}

bool UglyJSONParser::NullNode::Contains(const string& key) const
{
    return false;
}

#pragma endregion

#pragma region RootNode

bool UglyJSONParser::RootNode::CreateRootNode(NodeType nodeType)
{
    if (nodeType == NodeType::Error || nodeType == NodeType::Root || !(_nodeType == NodeType::Root && _entryPoint == nullptr))
    {
        return false;
    }

    _entryPoint = _factory.CreateNode(nodeType, _FirstNodeName);

    if (_entryPoint == nullptr)
    {
        return false;
    }

    _nodeType = nodeType;

    return true;
}

std::string UglyJSONParser::RootNode::GetJsonTreeByString()
{
    return _entryPoint->GetJsonTreeByString();
}

const std::string& UglyJSONParser::RootNode::AsString() const
{
    return _entryPoint->AsString();
}

long long UglyJSONParser::RootNode::AsInt() const
{
    return _entryPoint->AsInt();
}

bool UglyJSONParser::RootNode::AsBool() const
{
    return _entryPoint->AsBool();
}

double UglyJSONParser::RootNode::AsDouble() const
{
    return _entryPoint->AsDouble();
}

UglyJSONParser::BaseNode& UglyJSONParser::RootNode::operator[](const string& strKey)
{
    return (*_entryPoint)[strKey];
}

UglyJSONParser::BaseNode& UglyJSONParser::RootNode::operator[](const size_t intKey)
{
    return (*_entryPoint)[intKey];
}

void UglyJSONParser::RootNode::operator=(const char* strData)
{
    (*_entryPoint) = strData;
}

void UglyJSONParser::RootNode::operator=(const string& strData)
{
    (*_entryPoint) = strData;
}

void UglyJSONParser::RootNode::operator=(const long long intData)
{
    (*_entryPoint) = intData;
}

void UglyJSONParser::RootNode::operator=(const bool boolData)
{
    (*_entryPoint) = boolData;
}

void UglyJSONParser::RootNode::operator=(const double doubleData)
{
    (*_entryPoint) = doubleData;
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::RootNode::GetChildNodeVector()
{
    return _entryPoint->GetChildNodeVector();
}

void UglyJSONParser::RootNode::Clear()
{
    _entryPoint->Clear();
}

void UglyJSONParser::RootNode::DeleteChildNode(const string& strKey)
{
    _entryPoint->DeleteChildNode(strKey);
}

void UglyJSONParser::RootNode::DeleteChildNode(size_t intKey)
{
    _entryPoint->DeleteChildNode(intKey);
}

bool UglyJSONParser::RootNode::CreateNewNode(NodeType type, string strKey)
{
    return _entryPoint->CreateNewNode(type, strKey);
}

bool UglyJSONParser::RootNode::CreateNewNode(NodeType type)
{
    return _entryPoint->CreateNewNode(type);
}

size_t UglyJSONParser::RootNode::GetChildNodeCount() const
{
    return _entryPoint->GetChildNodeCount();
}

bool UglyJSONParser::RootNode::Contains(const string& key) const
{
    return _entryPoint->Contains(key);
}

#pragma endregion

#pragma region NodeFactory

UglyJSONParser::BaseNode* UglyJSONParser::NodeFactory::CreateNode(NodeType type, std::string name)
{
    if (name.front() == Tokens::TokenQuotationMark)
    {
        name.erase(0, 1);
    }
    
    if (name.back() == Tokens::TokenQuotationMark)
    {
        name.pop_back();
    }

    switch (type)
    {
    case NodeType::Object:
        return new ObjectNode(std::move(name));

    case NodeType::Array:
        return new ArrayNode(std::move(name));

    case NodeType::String:
        return new StringNode(std::move(name));

    case NodeType::Number:
        return new NumberNode(std::move(name));

    case NodeType::Bool:
        return new BoolNode(std::move(name));

    case NodeType::Null:
        return new NullNode(std::move(name));

    default:
        return nullptr;
    }
}

#pragma endregion