#ifndef UGLY_JSON_PARSER_NODE_BASE_HEADER
#define UGLY_JSON_PARSER_NODE_BASE_HEADER

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <stdlib.h>
#include ".\NodeTypes.hpp"

namespace UglyJSONParser
{
    class BaseNode
    {
    protected:
        using string = std::string;
        string _nodeName;
        NodeType _nodeType;

    public:
        BaseNode(string name, NodeType nodeType);
        BaseNode(const BaseNode&) = delete;
        BaseNode(BaseNode&&) = delete;

        inline NodeType GetNodeType() const
        {
            return _nodeType;
        }

        inline const string& GetName() const
        {
            return _nodeName;
        }

        virtual string GetJsonTreeByString() = 0;


        virtual const string& AsString() const = 0;
        virtual long long AsInt() const = 0;
        virtual bool AsBool() const = 0;
        virtual double AsDouble() const = 0;

        virtual BaseNode& operator[](const string& strKey) = 0;
        virtual BaseNode& operator[](const int intKey) = 0;

        virtual void operator=(const string& strData) = 0;
        virtual void operator=(const char* strData) = 0;
        virtual void operator=(const long long intData) = 0;
        virtual void operator=(const bool boolData) = 0;
        virtual void operator=(const double doubleData) = 0;


        virtual std::vector<BaseNode*>& GetChildNodeVector() = 0;

        virtual void Clear() = 0;

        virtual void DeleteChildNode(const string& strKey) = 0;
        virtual void DeleteChildNode(int intKey) = 0;

        virtual bool CreateNewNode(NodeType type, string strKey) = 0;
        virtual bool CreateNewNode(NodeType type) = 0;


        virtual size_t GetChildNodeCount() const = 0;

        virtual ~BaseNode();
    };
}

#endif // UGLY_JSON_PARSER_NODE_BASE_HEADER