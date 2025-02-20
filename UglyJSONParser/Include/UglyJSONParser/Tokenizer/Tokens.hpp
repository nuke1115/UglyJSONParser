#ifndef UGLY_JSON_PARSER_TOKENS_HEADER
#define UGLY_JSON_PARSER_TOKENS_HEADER


namespace UglyJSONParser
{
    namespace Tokens
    {
        constexpr const char* TokenTrue = "true";
        constexpr const char* TokenFalse = "false";
        constexpr const char* TokenNull = "null";

        constexpr char TokenQuotationMark = '"';
        constexpr char TokenObjectStart = '{';
        constexpr char TokenObjectEnd = '}';
        constexpr char TokenArrayStart = '[';
        constexpr char TokenArrayEnd = ']';
        constexpr char TokenComma = ',';
        constexpr char TokenPlus = '+';
        constexpr char TokenMinus = '-';
        constexpr char TokenColon = ':';
        constexpr char TokenBackslash = '\\';
        constexpr char NumRangeStart = '0';
        constexpr char NumRangeEnd = '9';
        constexpr char TokenDecimalPoint = '.';
        constexpr char TokenExponentUpper = 'E';
        constexpr char TokenExponentLower = 'e';

        constexpr char TokenSpace = ' ';
        constexpr char TokenLineFeed = '\n';
        constexpr char TokenCarriageReturn = '\r';
        constexpr char TokenHorizontalTab = '\t';
    }
}

#endif // !UGLY_JSON_PARSER_TOKENS_HEADER