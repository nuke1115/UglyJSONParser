#ifndef UGLY_JSON_PARSER_TOKENIZER_HEADER
#define UGLY_JSON_PARSER_TOKENIZER_HEADER
#include <string>
#include <list>
#include <xutility>
#include <sstream>

namespace UglyJSONParser
{

    class Tokenizer
    {
    private:
        using string = std::string;

        const char TokenQuotationMark = '"';
        const char TokenObjectStart = '{';
        const char TokenObjectEnd = '}';
        const char TokenArrayStart = '[';
        const char TokenArrayEnd = ']';
        const char TokenComma = ',';
        const char TokenPlus = '+';
        const char TokenMinus = '-';
        const char TokenColon = ':';
        const char TokenBackslash = '\\';
        const char NumRangeStart = '0';
        const char NumRangeEnd = '9';
        const char TokenDecimalPoint = '.';
        const char TokenExponentUpper = 'E';
        const char TokenExponentLower = 'e';

        const char TokenSpace = ' ';
        const char TokenLineFeed = '\n';
        const char TokenCarriageReturn = '\r';
        const char TokenHorizontalTab = '\t';

        inline bool IsItNumber(const char token)
        {
            return NumRangeStart <= token && NumRangeEnd >= token;
        }

        bool TokenizeString(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index);
        bool TokenizeNumber(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index);
        bool CheckTokenizedNumber(const std::string& numString, size_t exponentCnt, size_t signCnt, size_t pointCnt);

    public:
        bool Tokenize(const std::string& sourceString, std::list<std::string>& outTokenizedStrings);
    };


}

/*

토크나이저 기능:
1:토큰화
{
문자열 입력
문자를 앞에서부터 하나씩 읽어간다.
원본 문자열의 각 토큰의 시작문자와 종료문자에 따라 모드를 바꾼다.
현제 문자와 모드에 따라서 문자열을 만들어 리스트에 넣는다.
리스트 반환

특수문자중 \붙은건 \와 특수문자 두개가 하나로 취급된다?


이스케이프처리된건, 그냥 \하고 문자를 있는 그대로 출력할까?
\" 를 "로 보여주지 말고, 있는 그대로 \" 이렇게

}
규칙:
)

}


*/

#endif // !UGLY_JSON_PARSER_TOKENIZER_HEADER
