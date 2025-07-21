#ifndef UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER
#define UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER

#include <optional>
#include <string>
#include <assert.h>
#include <stdint.h>
#include <type_traits>
#include "../Enumerations/DetailedErrInfo.hpp"

namespace UglyJSONParser
{
    /// <summary>
    /// std::optional's wrapper class. this doesn't manage life cycle
    /// </summary>
    /// <typeparam name="ValueType"></typeparam>
    template<typename ValueType>
    class UglyRefResult
    {
    private:
        uint32_t _errInfo;
        std::optional<ValueType*> _value;
    public:

        UglyRefResult(ValueType* value);

        UglyRefResult(uint32_t errInfoBitMask);

        inline bool HasValue() const;

        inline uint32_t GetErrorInfoMask() const;

        inline ValueType& GetValueRef();

        inline const ValueType& GetConstRef() const;
    };
}

#include "../../../src/Result/UglyRefResultINL.hpp"
#include "../../../src/Result/UglyRefResultTPP.hpp"

#endif // !UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER
