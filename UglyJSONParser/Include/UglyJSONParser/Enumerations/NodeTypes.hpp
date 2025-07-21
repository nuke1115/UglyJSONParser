#ifndef UGLY_JSON_PARSER_NODE_TYPES_HEADER
#define UGLY_JSON_PARSER_NODE_TYPES_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class NodeType : uint32_t
    {
        ZERO_VALUE = 0b0,
        Null    = 0b1<<0,
        Object  = 0b1<<1,
        Array   = 0b1<<2,
        String  = 0b1<<3,
        Number  = 0b1<<4,
        Bool    = 0b1<<5,
        Root    = 0b1<<6,
        Error   = 0b1<<7
    };

    //underlying_type_t<NodeType> == uint32_t
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