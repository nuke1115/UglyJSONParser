#ifndef UGLY_JSON_PARSER_NODE_TYPES_HEADER
#define UGLY_JSON_PARSER_NODE_TYPES_HEADER


namespace UglyJSONParser
{
    enum class NodeType
    {
        Null = 0,
        Object = 1,
        Array = 2,
        SingleValue = 3,
        Root = 4,
        Error = -1
    };
}


#endif // !UGLY_JSON_PARSER_NODE_TYPES_HEADER
