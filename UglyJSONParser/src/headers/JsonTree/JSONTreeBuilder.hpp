#ifndef UGLY_JSON_PARSER_JSON_TREE_BUILDER_HEADER
#define UGLY_JSON_PARSER_JSON_TREE_BUILDER_HEADER
#include <string>
#include <list>
#include <stack>
#include <algorithm>
#include <exception>
#include <xutility>
#include ".\Node.hpp"
#include "..\Utils\StringUtils.hpp"
#include "..\Utils\TypeUtils.hpp"


namespace UglyJSONParser
{
    class JSONTreeBuilder
    {
    private:
        NodeFactory _factory;

        const char* _TokenTrue = "true";
        const char* _TokenFalse = "false";
        const char* _TokenNull = "null";
        const char* _FirstNodeName = "root";

        const char _TokenQuotationMark = '"';
        const char _TokenObjectStart = '{';
        const char _TokenObjectEnd = '}';
        const char _TokenArrayStart = '[';
        const char _TokenArrayEnd = ']';
        const char _TokenPlus = '+';
        const char _TokenMinus = '-';
        const char _TokenColon = ':';
        const char _TokenComma = ',';
        const char _TokenExponentUpper = 'E';
        const char _TokenExponentLower = 'e';
        const char TokenDecimalPoint = '.';

        BaseNode* CreateFirstNode(const std::string& token);

        void AssignValue(BaseNode& TargetNodeRef, const std::string& str);

    public:

        bool BuildJSONTree(RootNode& rootNode, const std::list<std::string>& tokens);

    };
}

#endif // !UGLY_JSON_PARSER_JSON_TREE_BUILDER_HEADER
