#ifndef UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER
#define UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER

#include <optional>
#include <string>
#include <assert.h>

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
        std::string _errInfo;
        std::optional<ValueType*> _value;
    public:

        UglyRefResult(ValueType* value);

        UglyRefResult(std::string_view errInfo);

        inline bool HasValue() const;

        inline const std::string& GetErrorInfo() const;

        inline ValueType& GetValueRef();

        inline const ValueType& GetConstRef() const;
    };
}

#include "../../../src/Result/UglyRefResultINL.hpp"
#include "../../../src/Result/UglyRefResultTPP.hpp"

#endif // !UGLY_JSON_PARSER_UGLY_REF_RESULT_HEADER
