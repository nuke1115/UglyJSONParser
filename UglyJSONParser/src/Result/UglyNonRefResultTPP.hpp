#ifndef UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_TPP_HEADER
#define UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_TPP_HEADER

template<typename ValueType>
UglyJSONParser::UglyNonRefResult<ValueType>::UglyNonRefResult(std::string_view errInfo) : _errInfo(errInfo)
{
    _value = std::nullopt;
}

template<typename ValueType>
UglyJSONParser::UglyNonRefResult<ValueType>::UglyNonRefResult(ValueType value) : _errInfo("no error"), _value(value)
{

}

#endif // !UGLY_JSON_PARSER_UGLY_NON_REF_RESULT_TPP_HEADER
