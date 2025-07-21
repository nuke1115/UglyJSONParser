#ifndef UGLY_JSON_PARSER_ACCESS_TYPES_HEADER
#define UGLY_JSON_PARSER_ACCESS_TYPES_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class AccessTypes : uint32_t
    {
        ZERO_VALUE = 0b0,
        BY_INT      = 0b1<<14,
        BY_STRING   = 0b1<<15
    };

    inline constexpr AccessTypes operator|(AccessTypes left, AccessTypes right) noexcept
    {
        using T = std::underlying_type_t<AccessTypes>;
        return static_cast<AccessTypes>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr AccessTypes operator&(AccessTypes left, AccessTypes right) noexcept
    {
        using T = std::underlying_type_t<AccessTypes>;
        return static_cast<AccessTypes>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr AccessTypes operator^(AccessTypes left, AccessTypes right) noexcept
    {
        using T = std::underlying_type_t<AccessTypes>;
        return static_cast<AccessTypes>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr AccessTypes operator~(AccessTypes left) noexcept
    {
        using T = std::underlying_type_t<AccessTypes>;
        return static_cast<AccessTypes>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_ACCESS_TYPES_HEADER
