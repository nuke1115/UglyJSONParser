#ifndef UGLY_JSON_PARSER_OPERATION_TYPES_HEADER
#define UGLY_JSON_PARSER_OPERATION_TYPES_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class OperationTypes : uint32_t
    {
        ZERO_VALUE = 0b0,
        INSERT          = 0b1 << 16,
        GET             = 0b1 << 17,
        DELETE          = 0b1 << 18
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
