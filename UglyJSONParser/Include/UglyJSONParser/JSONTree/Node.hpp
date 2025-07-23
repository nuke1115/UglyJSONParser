#ifndef UGLY_JSON_PARSER_NODE_HEADER
#define UGLY_JSON_PARSER_NODE_HEADER

#include <utility>
#include "./NodeBase.hpp"
#include "../EnumerationInclude.hpp"
#include "../Utils/TypeUtils.hpp"
#include "../Tokenizer/Tokens.hpp"
#include "../Utils/ResultUtils.hpp"
#include "../ResultInclude.hpp"


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

        UglyConstRefResult<string> AsString() const override;

        UglyNonRefResult<bool> operator=(const char* strData) override;
        UglyNonRefResult<bool> operator=(const string& strData) override;

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

        UglyNonRefResult<long long> AsInt() const override;
        UglyNonRefResult<double> AsDouble() const override;

        UglyNonRefResult<bool> operator=(const long long intData) override;
        UglyNonRefResult<bool> operator=(const double doubleData) override;

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

        UglyNonRefResult<bool> AsBool() const override;

        UglyNonRefResult<bool> operator=(const bool boolData) override;

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

        UglyRefResult<BaseNode> operator[](const string& strKey) override;

        UglyRefResult<std::vector<BaseNode*>> GetChildNodeVector() override;

        UglyNonRefResult<bool> Clear() override;

        UglyNonRefResult<bool> DeleteChildNode(const string& strKey) override;

        UglyNonRefResult<bool> CreateNewNode(NodeType type, string strKey) override;

        UglyNonRefResult<size_t> GetChildNodeCount() const override;

        UglyNonRefResult<bool> Contains(const string& key) const override;

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

        UglyRefResult<BaseNode> operator[](const size_t intKey) override;

        UglyRefResult<std::vector<BaseNode*>> GetChildNodeVector() override;

        UglyNonRefResult<bool> Clear() override;

        UglyNonRefResult<bool> DeleteChildNode(size_t intKey) override;

        UglyNonRefResult<bool> CreateNewNode(NodeType type) override;

        UglyNonRefResult<size_t> GetChildNodeCount() const override;

        UglyNonRefResult<bool> Contains(const string& key) const override;

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

        UglyConstRefResult<string> AsString() const override;
        UglyNonRefResult<long long> AsInt() const override;
        UglyNonRefResult<bool> AsBool() const override;
        UglyNonRefResult<double> AsDouble() const override;

        UglyRefResult<BaseNode> operator[](const string& strKey) override;
        UglyRefResult<BaseNode> operator[](const size_t intKey) override;

        UglyNonRefResult<bool> operator=(const char* strData) override;
        UglyNonRefResult<bool> operator=(const string& strData) override;
        UglyNonRefResult<bool> operator=(const long long intData) override;
        UglyNonRefResult<bool> operator=(const bool boolData) override;
        UglyNonRefResult<bool> operator=(const double doubleData) override;

        UglyRefResult<std::vector<BaseNode*>> GetChildNodeVector() override;

        UglyNonRefResult<bool> Clear() override;

        UglyNonRefResult<bool> DeleteChildNode(const string& strKey) override;
        UglyNonRefResult<bool> DeleteChildNode(size_t intKey) override;

        UglyNonRefResult<bool> CreateNewNode(NodeType type, string strKey) override;
        UglyNonRefResult<bool> CreateNewNode(NodeType type) override;

        UglyNonRefResult<size_t> GetChildNodeCount() const override;

        UglyNonRefResult<bool> Contains(const string& key) const override;

        UglyNonRefResult<bool> CreateRootNode(NodeType nodeType);

        ~RootNode();
    };
}

#endif // !UGLY_JSON_PARSER_NODE_HEADER