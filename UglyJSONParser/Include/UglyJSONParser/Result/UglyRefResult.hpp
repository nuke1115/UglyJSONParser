#ifndef UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER
#define UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER

#include <optional>
#include <string>
#include <assert.h>
#include <stdint.h>
#include <type_traits>
#include "../Constants/ResultEnumConstants.hpp"
#include "../Utils/ResultUtils.hpp"

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
        ErrorBitmask _errInfo;
        std::optional<ValueType*> _value;
    public:

        UglyRefResult(ValueType* value);

        UglyRefResult(ErrorBitmask errInfoBitMask);

        inline bool HasValue() const;

        inline ErrorBitmask GetErrorInfoMask() const;

        inline ValueType& GetValueRef();

        inline const ValueType& GetConstRef() const;
    };
}

#include "../../../src/Result/UglyRefResultINL.hpp"
#include "../../../src/Result/UglyRefResultTPP.hpp"

#endif // !UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER
