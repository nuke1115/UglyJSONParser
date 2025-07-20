#ifndef UGLY_JSON_PARSER_NODE_TYPES_HEADER
#define UGLY_JSON_PARSER_NODE_TYPES_HEADER

namespace UglyJSONParser
{
    enum class NodeType : uint8_t
    {
        ZERO_VALUE = 0b0,
        Null    = 0b00000001,
        Object  = 0b00000010,
        Array   = 0b00000100,
        String  = 0b00001000,
        Number  = 0b00010000,
        Bool    = 0b00100000,
        Root    = 0b01000000,
        Error   = 0b10000000
    };

    //underlying_type_t<NodeType> == uint8_t
    inline constexpr NodeType operator|(NodeType left, NodeType right) noexcept
    {
        using T = std::underlying_type_t<NodeType>;
        return static_cast<NodeType>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr NodeType operator&(NodeType left, NodeType right) noexcept
    {
        using T = std::underlying_type_t<NodeType>;
        return static_cast<NodeType>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr NodeType operator^(NodeType left, NodeType right) noexcept
    {
        using T = std::underlying_type_t<NodeType>;
        return static_cast<NodeType>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr NodeType operator~(NodeType left) noexcept
    {
        using T = std::underlying_type_t<NodeType>;
        return static_cast<NodeType>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_NODE_TYPES_HEADER