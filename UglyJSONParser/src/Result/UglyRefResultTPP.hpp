#ifndef UGLY_JSON_PARSER_UGLY_REF_RESULT_TPP_HEADER
#define UGLY_JSON_PARSER_UGLY_REF_RESULT_TPP_HEADER


template<typename ValueType>
UglyJSONParser::UglyRefResult<ValueType>::UglyRefResult(ValueType* value)
{
    _errInfo = 0;
    if (value == nullptr)
    {
        _errInfo = 0;
        _value = std::nullopt;
    }
    else
    {
        _value = value;
    }
}

template<typename ValueType>
UglyJSONParser::UglyRefResult<ValueType>::UglyRefResult(uint32_t errInfoBitMask)
{
    _errInfo = errInfoBitMask;
    _value = std::nullopt;
}

#endif // !UGLY_JSON_PARSER_UGLY_REF_RESULT_TPP_HEADER
