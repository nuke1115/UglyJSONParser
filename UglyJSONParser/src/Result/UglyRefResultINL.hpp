#ifndef UGLY_JSON_PARSER_UGLY_REF_RESULT_INL_HEADER
#define UGLY_JSON_PARSER_UGLY_REF_RESULT_INL_HEADER


template<typename ValueType>
bool UglyJSONParser::UglyRefResult<ValueType>::HasValue() const
{
    return _value.has_value();
}

template<typename ValueType>
UglyJSONParser::ErrorBitmask UglyJSONParser::UglyRefResult<ValueType>::GetErrorInfoMask() const
{
    return _errInfo;
}

template<typename ValueType>
ValueType& UglyJSONParser::UglyRefResult<ValueType>::GetValueRef()
{
    assert(HasValue());
    return *(_value.value());
}

template<typename ValueType>
const ValueType& UglyJSONParser::UglyRefResult<ValueType>::GetConstRef() const
{
    assert(HasValue());
    return *(_value.value());
}

#endif // !UGLY_JSON_PARSER_UGLY_REF_RESULT_INL_HEADER
