#ifndef UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_INL_HEADER
#define UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_INL_HEADER

template<typename ValueType>
bool UglyJSONParser::UglyNonRefResult<ValueType>::HasValue() const
{
    return _value.has_value();
}

template<typename ValueType>
uint32_t UglyJSONParser::UglyNonRefResult<ValueType>::GetErrorInfoMask() const
{
    return _errInfo;
}

template<typename ValueType>
ValueType UglyJSONParser::UglyNonRefResult<ValueType>::GetValue() const
{
    assert(HasValue());
    return _value.value();
}

template<typename ValueType>
const ValueType& UglyJSONParser::UglyNonRefResult<ValueType>::GetConstRef() const
{
    assert(HasValue());
    return _value.value();
}

#endif // !UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_INL_HEADER
