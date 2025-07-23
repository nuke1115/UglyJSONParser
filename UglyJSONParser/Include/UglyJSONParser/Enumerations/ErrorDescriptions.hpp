#ifndef UGLY_JSON_PARSER_ERROR_DESCRIPTIONS_HEADER
#define UGLY_JSON_PARSER_ERROR_DESCRIPTIONS_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class ErrorDescriptions : uint32_t
    {
        FALSE_BIT=0b1<<26,
        WRONG_TYPE=0b1<<27,
        NOT_FOUND = 0b1<<28,
        INDEX_EXCEED = 0b1<<29,
        DUPLICATED_KEY = 0b1<<30,
        CREATE_FAILED = 0b1U <<31
    };

    inline constexpr ErrorDescriptions operator|(ErrorDescriptions left, ErrorDescriptions right) noexcept
    {
        using T = std::underlying_type_t<ErrorDescriptions>;
        return static_cast<ErrorDescriptions>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr ErrorDescriptions operator&(ErrorDescriptions left, ErrorDescriptions right) noexcept
    {
        using T = std::underlying_type_t<ErrorDescriptions>;
        return static_cast<ErrorDescriptions>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr ErrorDescriptions operator^(ErrorDescriptions left, ErrorDescriptions right) noexcept
    {
        using T = std::underlying_type_t<ErrorDescriptions>;
        return static_cast<ErrorDescriptions>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr ErrorDescriptions operator~(ErrorDescriptions left) noexcept
    {
        using T = std::underlying_type_t<ErrorDescriptions>;
        return static_cast<ErrorDescriptions>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_ERROR_DESCRIPTIONS_HEADER
