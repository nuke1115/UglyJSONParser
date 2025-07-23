#ifndef UGLY_JSON_PARSER_UGLY_CONST_REF_RESULT_INL_HEADER
#define UGLY_JSON_PARSER_UGLY_CONST_REF_RESULT_INL_HEADER


template<typename ValueType>
bool UglyJSONParser::UglyConstRefResult<ValueType>::HasValue() const
{
    return _value.has_value();
}

template<typename ValueType>
UglyJSONParser::ErrorBitmask UglyJSONParser::UglyConstRefResult<ValueType>::GetErrorInfoMask() const
{
    return _errInfo;
}

template<typename ValueType>
const ValueType& UglyJSONParser::UglyConstRefResult<ValueType>::GetConstRef() const
{
    assert(HasValue());
    return *(_value.value());
}

#endif // !UGLY_JSON_PARSER_UGLY_CONST_REF_RESULT_INL_HEADER
