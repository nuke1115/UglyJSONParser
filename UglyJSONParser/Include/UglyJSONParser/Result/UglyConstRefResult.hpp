#ifndef UGLY_JSON_PARSER_UGLY_CONST_REF_RESULT_HEADER
#define UGLY_JSON_PARSER_UGLY_CONST_REF_RESULT_HEADER

#include <optional>
#include <string>
#include <assert.h>
#include <stdint.h>
#include <type_traits>
#include "../EnumerationInclude.hpp"
#include "../Constants/ResultEnumConstants.hpp"
#include "../Utils/ResultUtils.hpp"

namespace UglyJSONParser
{
    /// <summary>
    /// std::optional's wrapper class. this doesn't manage life cycle
    /// </summary>
    /// <typeparam name="ValueType"></typeparam>
    template<typename ValueType>
    class UglyConstRefResult
    {
    private:
        ErrorBitmask _errInfo;
        std::optional<const ValueType*> _value;
    public:

        UglyConstRefResult(const ValueType* value);

        UglyConstRefResult(ErrorBitmask errInfoBitMask);

        inline bool HasValue() const;

        inline ErrorBitmask GetErrorInfoMask() const;

        inline const ValueType& GetConstRef() const;
    };
}

#include "../../../src/Result/UglyConstRefResultINL.hpp"
#include "../../../src/Result/UglyConstRefResultTPP.hpp"

#endif // !UGLY_JSON_PARSER_UGLY_CONST_REF_RESULT_HEADER
