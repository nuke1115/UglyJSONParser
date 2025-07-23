#ifndef UGLY_JSON_PARSER_NODE_BASE_HEADER
#define UGLY_JSON_PARSER_NODE_BASE_HEADER

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <stdlib.h>
#include <format>
#include "../EnumerationInclude.hpp"
#include "../Utils/TypeUtils.hpp"
#include "../Utils/ResultUtils.hpp"
#include "../ResultInclude.hpp"


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
        virtual UglyConstRefResult <string> AsString() const;


        /// <summary>
        /// returns data as int(long long)
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<long long> AsInt() const;

        /// <summary>
        /// returns data as bool
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> AsBool() const;

        /// <summary>
        /// returns data as double
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<double> AsDouble() const;

        virtual UglyRefResult<BaseNode> operator[](const string& strKey);
        virtual UglyRefResult<BaseNode> operator[](const size_t intKey);

        virtual UglyNonRefResult<bool> operator=(const string& strData);
        virtual UglyNonRefResult<bool> operator=(const char* strData);
        virtual UglyNonRefResult<bool> operator=(const long long intData);
        virtual UglyNonRefResult<bool> operator=(const bool boolData);
        virtual UglyNonRefResult<bool> operator=(const double doubleData);

        /// <summary>
        /// returns reference of node's childeNodeVector
        /// </summary>
        /// <returns></returns>
        virtual UglyRefResult<std::vector<BaseNode*>> GetChildNodeVector();

        /// <summary>
        /// Clears all child node of this node
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> Clear();

        /// <summary>
        /// Delete this node's child node by string.
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> DeleteChildNode(const string& strKey);

        /// <summary>
        /// Delete this node's child node by int index.
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> DeleteChildNode(size_t intKey);

        /// <summary>
        /// Create new child node to this node.
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> CreateNewNode(NodeType type, string strKey);

        /// <summary>
        /// Create new child node to this node.
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> CreateNewNode(NodeType type);

        /// <summary>
        /// Returns child node count of this node
        /// </summary>
        /// <returns></returns>
        virtual UglyNonRefResult<size_t> GetChildNodeCount() const;

        /// <summary>
        /// Returns whether childNodeVector contains node which name is same to key
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        virtual UglyNonRefResult<bool> Contains(const string& key) const;

        virtual ~BaseNode();
    };
}

#endif // UGLY_JSON_PARSER_NODE_BASE_HEADER