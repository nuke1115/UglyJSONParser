#ifndef UGLY_JSON_PARSER_ERROR_BIT_MASK_HEADER
#define UGLY_JSON_PARSER_ERROR_BIT_MASK_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class ErrorBitmask : uint32_t {};

    inline constexpr ErrorBitmask operator|(ErrorBitmask left, ErrorBitmask right) noexcept
    {
        using T = std::underlying_type_t<ErrorBitmask>;
        return static_cast<ErrorBitmask>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr ErrorBitmask operator&(ErrorBitmask left, ErrorBitmask right) noexcept
    {
        using T = std::underlying_type_t<ErrorBitmask>;
        return static_cast<ErrorBitmask>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr ErrorBitmask operator^(ErrorBitmask left, ErrorBitmask right) noexcept
    {
        using T = std::underlying_type_t<ErrorBitmask>;
        return static_cast<ErrorBitmask>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr ErrorBitmask operator~(ErrorBitmask left) noexcept
    {
        using T = std::underlying_type_t<ErrorBitmask>;
        return static_cast<ErrorBitmask>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_ERROR_BIT_MASK_HEADER
