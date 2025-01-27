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

        const char TokenSpace = ' ';
        const char TokenLineFeed = '\n';
        const char TokenCarriageReturn = '\r';
        const char TokenHorizontalTab = '\t';


        bool TokenizeString(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index);
        bool TokenizeNumber(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index);

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
