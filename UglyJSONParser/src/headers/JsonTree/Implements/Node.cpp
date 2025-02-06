#include "..\Node.hpp"


#pragma region Constructors

UglyJSONParser::SingleValueNode::SingleValueNode(string name) : BaseNode(std::move(name), NodeType::SingleValue)
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


UglyJSONParser::SingleValueNode::~SingleValueNode()
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

#pragma region SingleValueNode

std::string UglyJSONParser::SingleValueNode::GetJsonTreeByString()
{
    std::ostringstream buffer;

    if (_isStringData)
    {
        buffer << Tokens::TokenQuotationMark << _data << Tokens::TokenQuotationMark;
    }
    else
    {
        buffer << _data;
    }

    return buffer.str();
}

const std::string& UglyJSONParser::SingleValueNode::AsString() const
{
    return _data;
}

long long UglyJSONParser::SingleValueNode::AsInt() const
{
    return std::stoll(_data);
}

bool UglyJSONParser::SingleValueNode::AsBool() const
{
    return TypeUtils::ConvertStringToBool(_data);
}

double UglyJSONParser::SingleValueNode::AsDouble() const
{
    return std::stod(_data);
}

UglyJSONParser::BaseNode& UglyJSONParser::SingleValueNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

UglyJSONParser::BaseNode& UglyJSONParser::SingleValueNode::operator[](const size_t intKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

void UglyJSONParser::SingleValueNode::operator=(const char* strData)
{
    _isStringData = true;
    _data = strData;
}

void UglyJSONParser::SingleValueNode::operator=(const string& strData)
{
    _isStringData = true;
    _data = strData;
}

void UglyJSONParser::SingleValueNode::operator=(const long long intData)
{
    _isStringData = false;
    _data = std::move(std::to_string(intData));
}

void UglyJSONParser::SingleValueNode::operator=(const bool boolData)
{
    _isStringData = false;
    _data = std::move(TypeUtils::ConvertBoolToString(boolData));
}

void UglyJSONParser::SingleValueNode::operator=(const double doubleData)
{
    _isStringData = false;
    _data = std::move(std::to_string(doubleData));
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::SingleValueNode::GetChildNodeVector()
{
    throw std::logic_error("tried to get child node vector in leaf node");
}

void UglyJSONParser::SingleValueNode::Clear()
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::SingleValueNode::DeleteChildNode(const string& strKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

void UglyJSONParser::SingleValueNode::DeleteChildNode(size_t intKey)
{
    throw std::logic_error("tried to delete child node in leaf node");
}

bool UglyJSONParser::SingleValueNode::CreateNewNode(NodeType type, string strKey)
{
    throw std::logic_error("tried to create child node in leaf node");
}

bool UglyJSONParser::SingleValueNode::CreateNewNode(NodeType type)
{
    throw std::logic_error("tried to create child node in leaf node");
}

size_t UglyJSONParser::SingleValueNode::GetChildNodeCount() const
{
    return 0;
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
        if (i->GetNodeType() != NodeType::SingleValue && i->GetNodeType() != NodeType::Null)
        {
            i->Clear();
        }

        delete i;
    }
    _childNodeVector.clear();
}

void UglyJSONParser::ObjectNode::DeleteChildNode(const string& strKey)
{
    for (int i = 0; i < _childNodeVector.size(); i++)
    {
        if (!(_childNodeVector[i]->GetName().compare(strKey)))
        {
            delete _childNodeVector[i];
            _childNodeVector.erase(_childNodeVector.begin() + i);
            return;
        }
    }
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
        if (i->GetNodeType() != NodeType::SingleValue && i->GetNodeType() != NodeType::Null)
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

    case NodeType::SingleValue:
        return new SingleValueNode(std::move(name));

    case NodeType::Null:
        return new NullNode(std::move(name));

    default:
        return nullptr;
    }
}

#pragma endregion