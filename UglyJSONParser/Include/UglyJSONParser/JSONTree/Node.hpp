#ifndef UGLY_JSON_PARSER_NODE_HEADER
#define UGLY_JSON_PARSER_NODE_HEADER

#include <utility>
#include "./NodeBase.hpp"
#include "./NodeTypes.hpp"
#include "../Utils/TypeUtils.hpp"
#include "../Tokenizer/Tokens.hpp"


namespace UglyJSONParser
{
    class NodeFactory
    {
    public:
        BaseNode* CreateNode(NodeType type, std::string name);
    };

    class StringNode : public BaseNode
    {
    private:
        string _stringData = "DefaultStringValue";
    public:
        StringNode(string name);
        StringNode(const StringNode&) = delete;
        StringNode(StringNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        ~StringNode();
    };

    class NumberNode : public BaseNode
    {
    private:
        double _doubleData = 0.0;
        long long _intData = 0;
        bool _isItDouble = false;
    public:
        NumberNode(string name);
        NumberNode(const NumberNode&) = delete;
        NumberNode(NumberNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        ~NumberNode();
    };

    class BoolNode : public BaseNode
    {
    private:
        bool _boolData = false;
    public:
        BoolNode(string name);
        BoolNode(const BoolNode&) = delete;
        BoolNode(BoolNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        ~BoolNode();
    };    

    class ObjectNode : public BaseNode
    {
    private:
        std::vector<BaseNode*> _childNodeVector;
        NodeFactory _factory;
    public:
        ObjectNode(string name);
        ObjectNode(const ObjectNode&) = delete;
        ObjectNode(ObjectNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        ~ObjectNode();
    };

    class ArrayNode : public BaseNode
    {
    private:
        std::vector<BaseNode*> _childNodeVector;
        NodeFactory _factory;
    public:
        ArrayNode(string name);
        ArrayNode(const ArrayNode&) = delete;
        ArrayNode(ArrayNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        ~ArrayNode();
    };

    class NullNode : public BaseNode
    {
    private:

    public:

        NullNode(string name);
        NullNode(const NullNode&) = delete;
        NullNode(NullNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        ~NullNode();
    };

    class RootNode : public BaseNode
    {
    private:
        const char* _FirstNodeName = "root";
        BaseNode* _entryPoint = nullptr;
        NodeFactory _factory;
    public:

        RootNode();
        RootNode(const RootNode&) = delete;
        RootNode(RootNode&&) = delete;

        string GetJsonTreeByString() override;

        const string& AsString() const override;
        long long AsInt() const override;
        bool AsBool() const override;
        double AsDouble() const override;

        BaseNode& operator[](const string& strKey) override;
        BaseNode& operator[](const size_t intKey) override;

        void operator=(const char* strData) override;
        void operator=(const string& strData) override;
        void operator=(const long long intData) override;
        void operator=(const bool boolData) override;
        void operator=(const double doubleData) override;

        std::vector<BaseNode*>& GetChildNodeVector() override;

        void Clear() override;

        void DeleteChildNode(const string& strKey) override;
        void DeleteChildNode(size_t intKey) override;

        bool CreateNewNode(NodeType type, string strKey) override;
        bool CreateNewNode(NodeType type) override;

        size_t GetChildNodeCount() const override;

        bool Contains(const string& key) const override;

        bool CreateRootNode(NodeType nodeType);

        ~RootNode();
    };
}

#endif // !UGLY_JSON_PARSER_NODE_HEADER