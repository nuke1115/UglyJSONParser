#ifndef UGLY_JSON_PARSER_TOKENS_HEADER
#define UGLY_JSON_PARSER_TOKENS_HEADER


namespace UglyJSONParser
{
    class Tokens
    {
    public:
        static constexpr const char* TokenTrue = "true";
        static constexpr const char* TokenFalse = "false";
        static constexpr const char* TokenNull = "null";

        static constexpr char TokenQuotationMark = '"';
        static constexpr char TokenObjectStart = '{';
        static constexpr char TokenObjectEnd = '}';
        static constexpr char TokenArrayStart = '[';
        static constexpr char TokenArrayEnd = ']';
        static constexpr char TokenComma = ',';
        static constexpr char TokenPlus = '+';
        static constexpr char TokenMinus = '-';
        static constexpr char TokenColon = ':';
        static constexpr char TokenBackslash = '\\';
        static constexpr char NumRangeStart = '0';
        static constexpr char NumRangeEnd = '9';
        static constexpr char TokenDecimalPoint = '.';
        static constexpr char TokenExponentUpper = 'E';
        static constexpr char TokenExponentLower = 'e';

        static constexpr char TokenSpace = ' ';
        static constexpr char TokenLineFeed = '\n';
        static constexpr char TokenCarriageReturn = '\r';
        static constexpr char TokenHorizontalTab = '\t';
    };
}

#endif // !UGLY_JSON_PARSER_TOKENS_HEADER
