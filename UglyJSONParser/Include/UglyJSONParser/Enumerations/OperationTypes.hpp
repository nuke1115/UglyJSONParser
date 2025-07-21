#ifndef UGLY_JSON_PARSER_OPERATION_TYPES_HEADER
#define UGLY_JSON_PARSER_OPERATION_TYPES_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class OperationTypes : uint32_t
    {
        FALSE_BIT       = 0b1 << 21,
        INSERT          = 0b1 << 22,
        GET             = 0b1 << 23,
        DELETE          = 0b1 << 24,
        CREATE          = 0b1 << 25
    };

    inline constexpr OperationTypes operator|(OperationTypes left, OperationTypes right) noexcept
    {
        using T = std::underlying_type_t<OperationTypes>;
        return static_cast<OperationTypes>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr OperationTypes operator&(OperationTypes left, OperationTypes right) noexcept
    {
        using T = std::underlying_type_t<OperationTypes>;
        return static_cast<OperationTypes>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr OperationTypes operator^(OperationTypes left, OperationTypes right) noexcept
    {
        using T = std::underlying_type_t<OperationTypes>;
        return static_cast<OperationTypes>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr OperationTypes operator~(OperationTypes left) noexcept
    {
        using T = std::underlying_type_t<OperationTypes>;
        return static_cast<OperationTypes>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_OPERATION_TYPES_HEADER
