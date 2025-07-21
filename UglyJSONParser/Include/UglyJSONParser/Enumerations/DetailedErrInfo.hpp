#ifndef UGLY_JSON_PARSER_DETAILED_ERR_INFO_HEADER
#define UGLY_JSON_PARSER_DETAILED_ERR_INFO_HEADER
#include <stdint.h>
#include <type_traits>

namespace UglyJSONParser
{
    enum class DetailedErrInfo : uint32_t
    {
        ZERO_VALUE = 0b0,
        ACCESS_WITH_WRONG_TYPE      = 0b1<<19,
        ACCESS_WITH_WRONG_INDEX_TYPE= 0b1<<20,
        VALUE_NOT_FOUND             =0b1<<21,
        NULLPTR_TO_REF_RESULT       =0b1<<22
    };

    inline constexpr DetailedErrInfo operator|(DetailedErrInfo left, DetailedErrInfo right) noexcept
    {
        using T = std::underlying_type_t<DetailedErrInfo>;
        return static_cast<DetailedErrInfo>(static_cast<T>(left) | static_cast<T>(right));
    }

    inline constexpr DetailedErrInfo operator&(DetailedErrInfo left, DetailedErrInfo right) noexcept
    {
        using T = std::underlying_type_t<DetailedErrInfo>;
        return static_cast<DetailedErrInfo>(static_cast<T>(left) & static_cast<T>(right));
    }

    inline constexpr DetailedErrInfo operator^(DetailedErrInfo left, DetailedErrInfo right) noexcept
    {
        using T = std::underlying_type_t<DetailedErrInfo>;
        return static_cast<DetailedErrInfo>(static_cast<T>(left) ^ static_cast<T>(right));
    }

    inline constexpr DetailedErrInfo operator~(DetailedErrInfo left) noexcept
    {
        using T = std::underlying_type_t<DetailedErrInfo>;
        return static_cast<DetailedErrInfo>(~static_cast<T>(left));
    }
}

#endif // !UGLY_JSON_PARSER_DETAILED_ERR_INFO_HEADER
