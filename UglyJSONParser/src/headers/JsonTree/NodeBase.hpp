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

        /// <summary>
        /// returns now node's node type
        /// </summary>
        /// <returns></returns>
        inline NodeType GetNodeType() const
        {
            return _nodeType;
        }

        /// <summary>
        /// returns now node's name
        /// </summary>
        /// <returns></returns>
        inline const string& GetName() const
        {
            return _nodeName;
        }

        /// <summary>
        /// serializes json tree from this node, and returns it
        /// </summary>
        /// <returns></returns>
        virtual string GetJsonTreeByString() = 0;

        /// <summary>
        /// returns data as string
        /// </summary>
        /// <returns></returns>
        virtual const string& AsString() const = 0;

        /// <summary>
        /// returns data as int(long long)
        /// </summary>
        /// <returns></returns>
        virtual long long AsInt() const = 0;

        /// <summary>
        /// returns data as bool
        /// </summary>
        /// <returns></returns>
        virtual bool AsBool() const = 0;

        /// <summary>
        /// returns data as double
        /// </summary>
        /// <returns></returns>
        virtual double AsDouble() const = 0;

        virtual BaseNode& operator[](const string& strKey) = 0;
        virtual BaseNode& operator[](const size_t intKey) = 0;

        virtual void operator=(const string& strData) = 0;
        virtual void operator=(const char* strData) = 0;
        virtual void operator=(const long long intData) = 0;
        virtual void operator=(const bool boolData) = 0;
        virtual void operator=(const double doubleData) = 0;

        /// <summary>
        /// returns reference of node's childeNodeVector
        /// </summary>
        /// <returns></returns>
        virtual std::vector<BaseNode*>& GetChildNodeVector() = 0;

        /// <summary>
        /// Clears all child node of this node
        /// </summary>
        /// <returns></returns>
        virtual void Clear() = 0;

        /// <summary>
        /// Delete this node's child node by string.
        /// </summary>
        /// <returns></returns>
        virtual void DeleteChildNode(const string& strKey) = 0;

        /// <summary>
        /// Delete this node's child node by int index.
        /// </summary>
        /// <returns></returns>
        virtual void DeleteChildNode(size_t intKey) = 0;

        /// <summary>
        /// Create new child node to this node.
        /// </summary>
        /// <returns></returns>
        virtual bool CreateNewNode(NodeType type, string strKey) = 0;

        /// <summary>
        /// Create new child node to this node.
        /// </summary>
        /// <returns></returns>
        virtual bool CreateNewNode(NodeType type) = 0;

        /// <summary>
        /// Returns child node count of this node
        /// </summary>
        /// <returns></returns>
        virtual size_t GetChildNodeCount() const = 0;

        virtual ~BaseNode();
    };
}

#endif // UGLY_JSON_PARSER_NODE_BASE_HEADER