#ifndef UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_TPP_HEADER
#define UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_TPP_HEADER

template<typename ValueType>
UglyJSONParser::UglyNonRefResult<ValueType>::UglyNonRefResult(uint32_t errInfoBitMask)
{
    _errInfo = errInfoBitMask;
    _value = std::nullopt;
}

template<typename ValueType>
UglyJSONParser::UglyNonRefResult<ValueType>::UglyNonRefResult(ValueType value)
{
    _errInfo = noErrorFilter;
    _value = value;
}

#endif // !UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_TPP_HEADER
