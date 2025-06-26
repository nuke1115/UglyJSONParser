#ifndef UGLY_JSON_PARSER_NODE_BASE_HEADER
#define UGLY_JSON_PARSER_NODE_BASE_HEADER

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <stdlib.h>
#include <format>
#include "./NodeTypes.hpp"
#include "../Utils/TypeUtils.hpp"

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
        virtual const string& AsString() const;


        /// <summary>
        /// returns data as int(long long)
        /// </summary>
        /// <returns></returns>
        virtual long long AsInt() const;

        /// <summary>
        /// returns data as bool
        /// </summary>
        /// <returns></returns>
        virtual bool AsBool() const;

        /// <summary>
        /// returns data as double
        /// </summary>
        /// <returns></returns>
        virtual double AsDouble() const;

        virtual BaseNode& operator[](const string& strKey);
        virtual BaseNode& operator[](const size_t intKey);

        virtual void operator=(const string& strData);
        virtual void operator=(const char* strData);
        virtual void operator=(const long long intData);
        virtual void operator=(const bool boolData);
        virtual void operator=(const double doubleData);

        /// <summary>
        /// returns reference of node's childeNodeVector
        /// </summary>
        /// <returns></returns>
        virtual std::vector<BaseNode*>& GetChildNodeVector();

        /// <summary>
        /// Clears all child node of this node
        /// </summary>
        /// <returns></returns>
        virtual void Clear();

        /// <summary>
        /// Delete this node's child node by string.
        /// </summary>
        /// <returns></returns>
        virtual void DeleteChildNode(const string& strKey);

        /// <summary>
        /// Delete this node's child node by int index.
        /// </summary>
        /// <returns></returns>
        virtual void DeleteChildNode(size_t intKey);

        /// <summary>
        /// Create new child node to this node.
        /// </summary>
        /// <returns></returns>
        virtual bool CreateNewNode(NodeType type, string strKey);

        /// <summary>
        /// Create new child node to this node.
        /// </summary>
        /// <returns></returns>
        virtual bool CreateNewNode(NodeType type);

        /// <summary>
        /// Returns child node count of this node
        /// </summary>
        /// <returns></returns>
        virtual size_t GetChildNodeCount() const;

        /// <summary>
        /// Returns whether childNodeVector contains node which name is same to key
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        virtual bool Contains(const string& key) const;

        virtual ~BaseNode();
    };
}

#endif // UGLY_JSON_PARSER_NODE_BASE_HEADER