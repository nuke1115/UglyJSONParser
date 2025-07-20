#include "../../Include/UglyJSONParser/JSONTree/Node.hpp"


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
        if (static_cast<uint64_t>((NodeType::Array | NodeType::Object) & _entryPoint->GetNodeType()))
        {
            _entryPoint->Clear();
        }

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

void UglyJSONParser::StringNode::operator=(const char* strData)
{
    _stringData = strData;
}

void UglyJSONParser::StringNode::operator=(const string& strData)
{
    _stringData = strData;
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

void UglyJSONParser::NumberNode::operator=(const long long intData)
{
    _isItDouble = false;
    _intData = intData;
}

void UglyJSONParser::NumberNode::operator=(const double doubleData)
{
    _isItDouble = true;
    _doubleData = doubleData;
}

#pragma endregion

#pragma region BoolNode

std::string UglyJSONParser::BoolNode::GetJsonTreeByString()
{
    return TypeUtils::ConvertBoolToString(_boolData);
}

bool UglyJSONParser::BoolNode::AsBool() const
{
    return _boolData;
}

void UglyJSONParser::BoolNode::operator=(const bool boolData)
{
    _boolData = boolData;
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

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::ObjectNode::GetChildNodeVector()
{
    return _childNodeVector;
}

void UglyJSONParser::ObjectNode::Clear()
{
    for (BaseNode* i : _childNodeVector)
    {
        if(static_cast<uint64_t>((NodeType::Object | NodeType::Array) & i->GetNodeType()))//null, string, bool, number면 안된다
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

UglyJSONParser::BaseNode& UglyJSONParser::ArrayNode::operator[](const size_t intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        throw std::logic_error("index exceeded array bound");
    }
    return *_childNodeVector[intKey];
}


std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::ArrayNode::GetChildNodeVector()
{
    return _childNodeVector;
}

void UglyJSONParser::ArrayNode::Clear()
{
    for (BaseNode* i : _childNodeVector)
    {
        if(static_cast<uint64_t>((NodeType::Object | NodeType::Array) & i->GetNodeType()))
        {
            i->Clear();
        }

        delete i;
    }
    _childNodeVector.clear();
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

#pragma endregion

#pragma region RootNode

bool UglyJSONParser::RootNode::CreateRootNode(NodeType nodeType)
{
    if (((NodeType::Error | NodeType::Root) & nodeType) != NodeType::ZERO_VALUE || !((NodeType::Root & _nodeType) != NodeType::ZERO_VALUE && _entryPoint == nullptr))
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