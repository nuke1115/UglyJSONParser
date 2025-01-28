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

��ũ������ ���:
1:��ūȭ
{
���ڿ� �Է�
���ڸ� �տ������� �ϳ��� �о��.
���� ���ڿ��� �� ��ū�� ���۹��ڿ� ���Ṯ�ڿ� ���� ��带 �ٲ۴�.
���� ���ڿ� ��忡 ���� ���ڿ��� ����� ����Ʈ�� �ִ´�.
����Ʈ ��ȯ

Ư�������� \������ \�� Ư������ �ΰ��� �ϳ��� ��޵ȴ�?


�̽�������ó���Ȱ�, �׳� \�ϰ� ���ڸ� �ִ� �״�� ����ұ�?
\" �� "�� �������� ����, �ִ� �״�� \" �̷���

}
��Ģ:
)

}


*/

#endif // !UGLY_JSON_PARSER_TOKENIZER_HEADER
