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
        if (_entryPoint->GetNodeType() == NodeType::Object || _entryPoint->GetNodeType() == NodeType::Array)
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

UglyJSONParser::UglyConstRefResult<std::string> UglyJSONParser::StringNode::AsString() const
{
    return UglyConstRefResult<string>(&_stringData);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::StringNode::operator=(const char* strData)
{
    _stringData = strData;
    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::StringNode::operator=(const string& strData)
{
    _stringData = strData;
    return UglyNonRefResult<bool>(true);
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

UglyJSONParser::UglyNonRefResult<long long> UglyJSONParser::NumberNode::AsInt() const
{
    if (_isItDouble)
    {
        return UglyNonRefResult<long long>(static_cast<long long>(_doubleData));
    }
    else
    {
        return UglyNonRefResult<long long>(_intData);
    }
}

UglyJSONParser::UglyNonRefResult<double> UglyJSONParser::NumberNode::AsDouble() const
{
    if (_isItDouble)
    {
        return UglyNonRefResult<double>(_doubleData);
    }
    else
    {
        return UglyNonRefResult<double>(static_cast<double>(_intData));
    }
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::NumberNode::operator=(const long long intData)
{
    _isItDouble = false;
    _intData = intData;
    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::NumberNode::operator=(const double doubleData)
{
    _isItDouble = true;
    _doubleData = doubleData;
    return UglyNonRefResult<bool>(true);
}

#pragma endregion

#pragma region BoolNode

std::string UglyJSONParser::BoolNode::GetJsonTreeByString()
{
    return TypeUtils::ConvertBoolToString(_boolData);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BoolNode::AsBool() const
{
    return UglyNonRefResult<bool>(_boolData);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::BoolNode::operator=(const bool boolData)
{
    _boolData = boolData;
    return UglyNonRefResult<bool>(true);
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

UglyJSONParser::UglyRefResult<UglyJSONParser::BaseNode> UglyJSONParser::ObjectNode::operator[](const string& strKey)
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(strKey)))
        {
            return UglyRefResult<BaseNode>(i);
        }
    }

    return UglyRefResult<BaseNode>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE,
        AccessTypes::BY_STRING,
        OperationTypes::GET,
        ErrorDescriptions::NOT_FOUND
    ));
}

UglyJSONParser::UglyRefResult<std::vector<UglyJSONParser::BaseNode*>> UglyJSONParser::ObjectNode::GetChildNodeVector()
{
    return UglyRefResult<std::vector<BaseNode*>>(&_childNodeVector);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ObjectNode::Clear()
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
    
    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ObjectNode::DeleteChildNode(const string& strKey)
{
    for (size_t i = 0; i < _childNodeVector.size(); i++)
    {
        if (!(_childNodeVector[i]->GetName().compare(strKey)))
        {
            delete _childNodeVector[i];
            _childNodeVector.erase(_childNodeVector.begin() + i);
            return UglyNonRefResult<bool>(true);
        }
    }

    return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE,
        AccessTypes::BY_STRING,
        OperationTypes::DELETE,
        ErrorDescriptions::NOT_FOUND
    ));
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ObjectNode::CreateNewNode(NodeType type, string strKey)
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(strKey)))
        {
            return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
                GetNodeType(),
                DataTypes::NODE,
                AccessTypes::BY_STRING,
                OperationTypes::CREATE,
                ErrorDescriptions::DUPLICATED_KEY
            ));
        }
    }

    BaseNode* newNode = _factory.CreateNode(type, std::move(strKey));

    if (newNode == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::BY_STRING,
            OperationTypes::CREATE,
            ErrorDescriptions::CREATE_FAILED
        ));
    }

    _childNodeVector.push_back(newNode);

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<size_t> UglyJSONParser::ObjectNode::GetChildNodeCount() const
{
    return UglyNonRefResult<size_t>(_childNodeVector.size());
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ObjectNode::Contains(const string& key) const
{
    for (BaseNode* i : _childNodeVector)
    {
        if (!(i->GetName().compare(key)))
        {
            return UglyNonRefResult<bool>(true);
        }
    }
    return UglyNonRefResult<bool>(false);
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

UglyJSONParser::UglyRefResult<UglyJSONParser::BaseNode> UglyJSONParser::ArrayNode::operator[](const size_t intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        return UglyRefResult<BaseNode>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::GET,
            ErrorDescriptions::INDEX_EXCEED
        ));
    }
    return UglyRefResult<BaseNode>(_childNodeVector[intKey]);
}


UglyJSONParser::UglyRefResult<std::vector<UglyJSONParser::BaseNode*>> UglyJSONParser::ArrayNode::GetChildNodeVector()
{
    return UglyRefResult<std::vector<BaseNode*>>(&_childNodeVector);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ArrayNode::Clear()
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

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ArrayNode::DeleteChildNode(size_t intKey)
{
    if (intKey >= _childNodeVector.size())
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::DELETE,
            ErrorDescriptions::INDEX_EXCEED
        ));
    }

    delete _childNodeVector[intKey];
    _childNodeVector.erase(_childNodeVector.begin() + intKey);

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ArrayNode::CreateNewNode(NodeType type)
{
    BaseNode* tmp = _factory.CreateNode(type, "nullName");

    if (tmp == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::CREATE,
            ErrorDescriptions::CREATE_FAILED
        ));   
    }

    _childNodeVector.push_back(tmp);
    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<size_t> UglyJSONParser::ArrayNode::GetChildNodeCount() const
{
    return UglyJSONParser::UglyNonRefResult<size_t>(_childNodeVector.size());
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::ArrayNode::Contains(const string& key) const
{
    return UglyJSONParser::UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
        GetNodeType(),
        DataTypes::NODE_EXISTENCE,
        AccessTypes::BY_STRING,
        OperationTypes::GET,
        ErrorDescriptions::WRONG_TYPE
    ));
}

#pragma endregion

#pragma region NullNode

std::string UglyJSONParser::NullNode::GetJsonTreeByString()
{
    return Tokens::TokenNull;
}

#pragma endregion

#pragma region RootNode

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::CreateRootNode(NodeType nodeType)
{
    if (nodeType == NodeType::Error || nodeType == NodeType::Root || !(_nodeType == NodeType::Root && _entryPoint == nullptr))
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::FALSE_BIT,
            OperationTypes::CREATE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    _entryPoint = _factory.CreateNode(nodeType, _FirstNodeName);

    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            GetNodeType(),
            DataTypes::NODE,
            AccessTypes::FALSE_BIT,
            OperationTypes::CREATE,
            ErrorDescriptions::CREATE_FAILED
        ));
    }

    _nodeType = nodeType;

    return UglyNonRefResult<bool>(true);
}

std::string UglyJSONParser::RootNode::GetJsonTreeByString()
{
    if (_entryPoint == nullptr)
    {
        return "";
    }

    return _entryPoint->GetJsonTreeByString();
}

UglyJSONParser::UglyConstRefResult<std::string>  UglyJSONParser::RootNode::AsString() const
{
    if (_entryPoint == nullptr)
    {
        return UglyConstRefResult<std::string>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::STRING,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    return _entryPoint->AsString();
}

UglyJSONParser::UglyNonRefResult<long long> UglyJSONParser::RootNode::AsInt() const
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<long long>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::INT,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    return _entryPoint->AsInt();
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::AsBool() const
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::BOOL,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    return _entryPoint->AsBool();
}

UglyJSONParser::UglyNonRefResult<double> UglyJSONParser::RootNode::AsDouble() const
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<double>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::DOUBLE,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    return _entryPoint->AsDouble();
}

UglyJSONParser::UglyRefResult<UglyJSONParser::BaseNode> UglyJSONParser::RootNode::operator[](const string& strKey)
{
    if (_entryPoint == nullptr)
    {
        return UglyRefResult<BaseNode>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE,
            AccessTypes::BY_STRING,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    return (*_entryPoint)[strKey];
}

UglyJSONParser::UglyRefResult<UglyJSONParser::BaseNode> UglyJSONParser::RootNode::operator[](const size_t intKey)
{
    if (_entryPoint == nullptr)
    {
        return UglyRefResult<BaseNode>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    return (*_entryPoint)[intKey];
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::operator=(const char* strData)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::STRING,
            AccessTypes::FALSE_BIT,
            OperationTypes::INSERT,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    (*_entryPoint) = strData;

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::operator=(const string& strData)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::STRING,
            AccessTypes::FALSE_BIT,
            OperationTypes::INSERT,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    (*_entryPoint) = strData;

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::operator=(const long long intData)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::INT,
            AccessTypes::FALSE_BIT,
            OperationTypes::INSERT,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    (*_entryPoint) = intData;

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::operator=(const bool boolData)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::BOOL,
            AccessTypes::FALSE_BIT,
            OperationTypes::INSERT,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    (*_entryPoint) = boolData;

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::operator=(const double doubleData)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::DOUBLE,
            AccessTypes::FALSE_BIT,
            OperationTypes::INSERT,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    (*_entryPoint) = doubleData;

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyRefResult<std::vector<UglyJSONParser::BaseNode*>> UglyJSONParser::RootNode::GetChildNodeVector()
{
    if (_entryPoint == nullptr)
    {
        return UglyRefResult<std::vector<UglyJSONParser::BaseNode*>>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE_VECTOR,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    return _entryPoint->GetChildNodeVector();
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::Clear()
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE_VECTOR,
            AccessTypes::FALSE_BIT,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    _entryPoint->Clear();

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::DeleteChildNode(const string& strKey)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE,
            AccessTypes::BY_STRING,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    _entryPoint->DeleteChildNode(strKey);

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::DeleteChildNode(size_t intKey)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::DELETE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    _entryPoint->DeleteChildNode(intKey);

    return UglyNonRefResult<bool>(true);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::CreateNewNode(NodeType type, string strKey)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE,
            AccessTypes::BY_STRING,
            OperationTypes::CREATE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    return _entryPoint->CreateNewNode(type, strKey);
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::CreateNewNode(NodeType type)
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE,
            AccessTypes::BY_INT,
            OperationTypes::CREATE,
            ErrorDescriptions::WRONG_TYPE
        ));
    }

    return _entryPoint->CreateNewNode(type);
}

UglyJSONParser::UglyNonRefResult<size_t> UglyJSONParser::RootNode::GetChildNodeCount() const
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<size_t>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE_COUNT,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
    return _entryPoint->GetChildNodeCount();
}

UglyJSONParser::UglyNonRefResult<bool> UglyJSONParser::RootNode::Contains(const string& key) const
{
    if (_entryPoint == nullptr)
    {
        return UglyNonRefResult<bool>(ResultUtils::MakeErrorBitmask(
            NodeType::FALSE_BIT,
            DataTypes::NODE_EXISTENCE,
            AccessTypes::FALSE_BIT,
            OperationTypes::GET,
            ErrorDescriptions::WRONG_TYPE
        ));
    }
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