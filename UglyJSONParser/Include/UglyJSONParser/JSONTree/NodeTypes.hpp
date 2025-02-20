#ifndef UGLY_JSON_PARSER_NODE_TYPES_HEADER
#define UGLY_JSON_PARSER_NODE_TYPES_HEADER

namespace UglyJSONParser
{
    enum class NodeType
    {
        Null = 0,
        Object = 1,
        Array = 2,
        String = 3,
        Number = 4,
        Bool = 5,
        Root = 6,
        Error = -1
    };
}

#endif // !UGLY_JSON_PARSER_NODE_TYPES_HEADER