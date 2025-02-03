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

/*

에초에 " 자체는 string 표현하려고 한거고, 문자열로 처리되는 "는 \"형태로 들어온다.

*/

#pragma region SingleValueNode

std::string UglyJSONParser::SingleValueNode::GetJsonTreeByString()
{
    std::ostringstream oss;
    if (_isStringData)
    {
        oss << '\"' << _data << '\"';
    }
    else
    {
        oss << _data;
    }

    return std::move(oss.str());
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
    return TypeUtils::StrToBool(_data);
}

double UglyJSONParser::SingleValueNode::AsDouble() const
{
    return std::stod(_data);
}

UglyJSONParser::BaseNode& UglyJSONParser::SingleValueNode::operator[](const string& strKey)
{
    throw std::logic_error("tried to access child node in leaf node");
}

UglyJSONParser::BaseNode& UglyJSONParser::SingleValueNode::operator[](const int intKey)
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
    _data = std::move(TypeUtils::BoolToString(boolData));
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
    return;
}

void UglyJSONParser::SingleValueNode::DeleteChildNode(const string& strKey)
{
    return;
}

void UglyJSONParser::SingleValueNode::DeleteChildNode(int intKey)
{
    return;
}

void UglyJSONParser::SingleValueNode::CreateNewNode(NodeType type, string strKey)
{
    return;
}

void UglyJSONParser::SingleValueNode::CreateNewNode(NodeType type)
{
    return;
}



#pragma endregion


#pragma region ObjectNode

std::string UglyJSONParser::ObjectNode::GetJsonTreeByString()
{
    std::ostringstream oss;

    oss << '{';

    for (BaseNode* i : _childNodeVector)
    {
        oss << "\"" << i->GetName() << "\"" << ':';

        oss << (i->GetJsonTreeByString());

        if (i != _childNodeVector.back())
        {
            oss << ',';
        }
    }

    oss << '}';

    return std::move(oss.str());
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

UglyJSONParser::BaseNode& UglyJSONParser::ObjectNode::operator[](const int intKey)
{
    throw std::logic_error("tried to access by int index in object node");
}

void UglyJSONParser::ObjectNode::operator=(const char* strData)
{
    return;
}

void UglyJSONParser::ObjectNode::operator=(const string& strData)
{
    return;
}

void UglyJSONParser::ObjectNode::operator=(const long long intData)
{
    return;
}

void UglyJSONParser::ObjectNode::operator=(const bool boolData)
{
    return;
}

void UglyJSONParser::ObjectNode::operator=(const double doubleData)
{
    return;
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::ObjectNode::GetChildNodeVector()
{
    return _childNodeVector;
}

void UglyJSONParser::ObjectNode::Clear()
{
    for (BaseNode* i : _childNodeVector)
    {
        if (i->GetNodeType() != NodeType::SingleValue)
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

void UglyJSONParser::ObjectNode::DeleteChildNode(int intKey)
{
    return;
}

void UglyJSONParser::ObjectNode::CreateNewNode(NodeType type, string strKey)
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(strKey)))
        {
            return;
        }
    }

    BaseNode* newNode = _factory.CreateNode(type, std::move(strKey));

    if (newNode != nullptr)
    {
        _childNodeVector.push_back(newNode);
    }
}

void UglyJSONParser::ObjectNode::CreateNewNode(NodeType type)
{
    return;
}

#pragma endregion


#pragma region ArrayNode

std::string UglyJSONParser::ArrayNode::GetJsonTreeByString()
{
    std::ostringstream oss;

    oss << '[';

    for (BaseNode* i : _childNodeVector)
    {

        oss << (i->GetJsonTreeByString());

        if (i != _childNodeVector.back())
        {
            oss << ',';
        }
    }

    oss << ']';

    return std::move(oss.str());
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

UglyJSONParser::BaseNode& UglyJSONParser::ArrayNode::operator[](const int intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        throw std::logic_error("index exceeded array bound");
    }
    return *_childNodeVector[intKey];
}

void UglyJSONParser::ArrayNode::operator=(const char* strData)
{
    return;
}

void UglyJSONParser::ArrayNode::operator=(const string& strData)
{
    return;
}

void UglyJSONParser::ArrayNode::operator=(const long long intData)
{
    return;
}

void UglyJSONParser::ArrayNode::operator=(const bool boolData)
{
    return;
}

void UglyJSONParser::ArrayNode::operator=(const double doubleData)
{
    return;
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::ArrayNode::GetChildNodeVector()
{
    return _childNodeVector;
}

void UglyJSONParser::ArrayNode::Clear()
{
    for (BaseNode* i : _childNodeVector)
    {
        if (i->GetNodeType() != NodeType::SingleValue)
        {
            i->Clear();
        }

        delete i;
    }
    _childNodeVector.clear();
}

void UglyJSONParser::ArrayNode::DeleteChildNode(const string& strKey)
{
    return;
}

void UglyJSONParser::ArrayNode::DeleteChildNode(int intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        throw std::logic_error("index exceeded array bound");
    }

    delete _childNodeVector[intKey];
    _childNodeVector.erase(_childNodeVector.begin() + intKey);
}

void UglyJSONParser::ArrayNode::CreateNewNode(NodeType type, string strKey)
{
    CreateNewNode(type);
}

void UglyJSONParser::ArrayNode::CreateNewNode(NodeType type)
{
    BaseNode* tmp = _factory.CreateNode(type, "nullName");

    if (tmp != nullptr)
    {
        _childNodeVector.push_back(tmp);
    }
}

#pragma endregion


#pragma region NullNode

std::string UglyJSONParser::NullNode::GetJsonTreeByString()
{
    std::ostringstream oss;
    
    oss << "null";

    return std::move(oss.str());
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

UglyJSONParser::BaseNode& UglyJSONParser::NullNode::operator[](const int intKey)
{
    throw std::logic_error("tried to get child node in null node");
}

void UglyJSONParser::NullNode::operator=(const char* strData)
{
    return;
}

void UglyJSONParser::NullNode::operator=(const string& strData)
{
    return;
}

void UglyJSONParser::NullNode::operator=(const long long intData)
{
    return;
}

void UglyJSONParser::NullNode::operator=(const bool boolData)
{
    return;
}

void UglyJSONParser::NullNode::operator=(const double doubleData)
{
    return;
}

std::vector<UglyJSONParser::BaseNode*>& UglyJSONParser::NullNode::GetChildNodeVector()
{
    throw std::logic_error("tried to get child node in null node");
}

void UglyJSONParser::NullNode::Clear()
{
    return;
}

void UglyJSONParser::NullNode::DeleteChildNode(const string& strKey)
{
    return;
}

void UglyJSONParser::NullNode::DeleteChildNode(int intKey)
{
    return;
}

void UglyJSONParser::NullNode::CreateNewNode(NodeType type, string strKey)
{
    return;
}

void UglyJSONParser::NullNode::CreateNewNode(NodeType type)
{
    return;
}

#pragma endregion

#pragma region RootNode

bool UglyJSONParser::RootNode::SetRoot(BaseNode* node)
{
    if (_entryPoint == nullptr && node != nullptr)
    {
        _entryPoint = node;
        return true;
    }
    return false;
}

bool UglyJSONParser::RootNode::SetType(NodeType type)
{
    if (_nodeType == NodeType::Root)
    {
        _nodeType = type;
        return true;
    }
    return false;
}

std::string UglyJSONParser::RootNode::GetJsonTreeByString()
{
    return std::move(_entryPoint->GetJsonTreeByString());
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

UglyJSONParser::BaseNode& UglyJSONParser::RootNode::operator[](const int intKey)
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
    _entryPoint = nullptr;
}

void UglyJSONParser::RootNode::DeleteChildNode(const string& strKey)
{
    _entryPoint->DeleteChildNode(strKey);
}

void UglyJSONParser::RootNode::DeleteChildNode(int intKey)
{
    _entryPoint->DeleteChildNode(intKey);
}

void UglyJSONParser::RootNode::CreateNewNode(NodeType type, string strKey)
{
    _entryPoint->CreateNewNode(type, strKey);
}

void UglyJSONParser::RootNode::CreateNewNode(NodeType type)
{
    _entryPoint->CreateNewNode(type);
}

#pragma endregion

#pragma region NodeFactory


UglyJSONParser::BaseNode* UglyJSONParser::NodeFactory::CreateNode(NodeType type, std::string name)
{
    if (name.front() == '\"')
    {
        name.erase(0, 1);
    }
    
    if (name.back() == '\"')
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

/*

std::string UglyJSONParser::SingleValueNode::GetJsonTreeByString()
{

}

const std::string& UglyJSONParser::SingleValueNode::AsString() const
{

}

int UglyJSONParser::SingleValueNode::AsInt() const
{

}

bool UglyJSONParser::SingleValueNode::AsBool() const
{

}


BaseNode& UglyJSONParser::SingleValueNode::operator[](const string& strKey)
{

}

BaseNode& UglyJSONParser::SingleValueNode::operator[](const int intKey)
{

}


void UglyJSONParser::SingleValueNode::operator=(const string& strData)
{

}

void UglyJSONParser::SingleValueNode::operator=(const int intData)
{

}

void UglyJSONParser::SingleValueNode::operator=(const bool boolData)
{

}



std::vector<BaseNode*>& UglyJSONParser::SingleValueNode::GetChildNodeVector()
{

}



void UglyJSONParser::SingleValueNode::Clear()
{

}


void UglyJSONParser::SingleValueNode::DeleteChildNode(const string& strKey)
{

}

void UglyJSONParser::SingleValueNode::DeleteChildNode(int intKey)
{

}


void UglyJSONParser::SingleValueNode::CreateNewNode(NodeType type, string strKey)
{

}

void UglyJSONParser::SingleValueNode::CreateNewNode(NodeType type)
{

}

*/