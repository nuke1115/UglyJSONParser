#ifndef UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_HEADER
#define UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_HEADER

#include <optional>
#include <string>
#include <assert.h>
#include <stdint.h>
#include "../EnumerationInclude.hpp"
#include "../Constants/ResultEnumConstants.hpp"

namespace UglyJSONParser
{
    /// <summary>
    /// std::optional's wrapper class.
    /// </summary>
    /// <typeparam name="ValueType"></typeparam>
    template<typename ValueType>
    class UglyNonRefResult
    {
    private:
        ErrorBitmask _errInfo;
        std::optional<ValueType> _value;
    public:
        UglyNonRefResult(ErrorBitmask errInfoBitMask);
        UglyNonRefResult(ValueType value);

        inline bool HasValue() const;
        inline ErrorBitmask GetErrorInfoMask() const;
        inline ValueType GetValue() const;
        inline const ValueType& GetConstRef() const;

    };
}

#include "../../../src/Result/UglyNonRefResultINL.hpp"
#include "../../../src/Result/UglyNonRefResultTPP.hpp"

#endif // !UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_HEADER
