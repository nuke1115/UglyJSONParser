#ifndef UGLY_JSON_PARSER_DATA_TYPES_HEADER
#define UGLY_JSON_PARSER_DATA_TYPES_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class DataTypes : uint32_t
    {
        ZERO_VALUE = 0b0,
        BOOL        = 0b1<<8,
        INT         = 0b1<<9,
        DOUBLE      = 0b1<<10,
        STRING      = 0b1<<11,
        NODE        = 0b1<<12,
        NODE_VECTOR = 0b1<<13
    };

    inline constexpr DataTypes operator|(DataTypes left, DataTypes right) noexcept
    {
        using T = std::underlying_type_t<DataTypes>;
        return static_cast<DataTypes>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr DataTypes operator&(DataTypes left, DataTypes right) noexcept
    {
        using T = std::underlying_type_t<DataTypes>;
        return static_cast<DataTypes>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr DataTypes operator^(DataTypes left, DataTypes right) noexcept
    {
        using T = std::underlying_type_t<DataTypes>;
        return static_cast<DataTypes>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr DataTypes operator~(DataTypes left) noexcept
    {
        using T = std::underlying_type_t<DataTypes>;
        return static_cast<DataTypes>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_DATA_TYPES_HEADER
