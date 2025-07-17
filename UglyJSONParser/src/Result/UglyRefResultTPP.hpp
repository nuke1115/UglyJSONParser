#ifndef UGLY_JSON_PARSER_UGLY_REF_RESULT_TPP_HEADER
#define UGLY_JSON_PARSER_UGLY_REF_RESULT_TPP_HEADER


template<typename ValueType>
UglyRefResult<ValueType>::UglyRefResult(ValueType* value) : _errInfo("no error")
{
    if (value == nullptr)
    {
        _errInfo = "entered nullptr";
        _value = std::nullopt;
    }
    else
    {
        _value = value;
    }
}

template<typename ValueType>
UglyRefResult<ValueType>::UglyRefResult(std::string_view errInfo) : _errInfo(errInfo)
{
    _value = std::nullopt;
}

#endif // !UGLY_JSON_PARSER_UGLY_REF_RESULT_TPP_HEADER
