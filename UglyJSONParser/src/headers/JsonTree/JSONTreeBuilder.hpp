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
#include "..\Tokenizer\Tokens.hpp"


namespace UglyJSONParser
{
    class JSONTreeBuilder
    {
    private:
        NodeFactory _factory;

        const char* _FirstNodeName = "root";

        BaseNode* CreateFirstNode(const std::string& token);

        void AssignValue(BaseNode& TargetNodeRef, const std::string& str);

    public:

        bool BuildJSONTree(RootNode& rootNode, const std::list<std::string>& tokens);

    };
}

#endif // !UGLY_JSON_PARSER_JSON_TREE_BUILDER_HEADER
