#include "..\Tokenizer.hpp"

bool UglyJSONParser::Tokenizer::TokenizeString(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index)
{
    if (index >= sourceString.size())
    {
        return false;
    }

    std::ostringstream oss;

    oss << sourceString[index];
    index++;

    size_t consecutiveBackslashCnt = 0;

    for (;index < sourceString.size(); index++)
    {

        if (sourceString[index] == TokenQuotationMark && (consecutiveBackslashCnt % 2 == 0)) // => consecutiveBackslashCnt ^ 1 <= 가독성때문에 바꿈
        {
            oss << sourceString[index];

            outTokenizedStrings.emplace_back(oss.str());

            return true;
        }

        if (sourceString[index] == TokenBackslash)
        {
            consecutiveBackslashCnt++;
        }
        else
        {
            consecutiveBackslashCnt = 0;
        }

        oss << sourceString[index];
    }

    return false;
}
//size_t 언더플로우 문제 개선
    // index - 1은 언더플로우가 안나는것이 보장된다.
    // 
    //단일 \ 가 들어왔을떄 케이스 처리


bool UglyJSONParser::Tokenizer::TokenizeNumber(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index)
{
    std::ostringstream oss;
    return true;
}

bool UglyJSONParser::Tokenizer::Tokenize(const std::string& sourceString, std::list<std::string>& outTokenizedStrings)
{
    if (sourceString.empty())
    {
        return false;
    }

    std::ostringstream oss;

    for (size_t i = 0; i < sourceString.size(); i++)
    {
        oss.clear();
        oss.str("");

        if (sourceString[i] == TokenObjectStart || sourceString[i] == TokenObjectEnd || sourceString[i] == TokenArrayStart || sourceString[i] == TokenArrayEnd || sourceString[i] == TokenComma || sourceString[i] == TokenColon)
        {
            oss << sourceString[i];
            outTokenizedStrings.emplace_back(oss.str());
        }
        else if (sourceString[i] == TokenQuotationMark)
        {
            bool result = TokenizeString(sourceString,outTokenizedStrings, i);
            if (result == false)
            {
                outTokenizedStrings.clear();
                return false;
            }
        }
        else if (sourceString[i] == TokenPlus || sourceString[i] == TokenMinus || (NumRangeStart <= sourceString[i] && sourceString[i] <= NumRangeEnd))
        {
            bool result = TokenizeNumber(sourceString, outTokenizedStrings, i);
            if (result == false)
            {
                return false;
            }
        }

    }
    return true;
}

/*
읽은 문자가 괄호 토큰들( {,},[,] ) 이것들이라면 바로 리스트에 push하고 다음문자를 읽는다.
읽은 문자가 쉼표토큰이라면 바로 리스트에 push하고 다음문자를 읽는다.
읽은 문자가 :토큰이라면 바로 리스트에 push하고 다음문자를 읽는다.

만약 문자열 플레그가 내려간 상태에서 읽은 토큰이 " 토큰이라면, 문자열 플래그를 올리고, 내부 문자열 변수 oss에 다음 " 토큰이 읽힐때까지 다른 처리과정으로 안가고, 문자열을 읽어서 oss에 더해준다.
만약 문자열 플레그가 올라간 상태에서 읽은 토큰이 "이면서 이전 토큰이 \라면 그냥 더해준다. 
    그러나,\ 다음이 바로 끝나거나, \"다음에 아무런 문자도 없으면 false리턴
만약 문자열 플레그가 올라간 상태에서 읽은 토큰이 "이라면 문자열 플레그를 내리고, oss에서 문자열을 꺼내와서 리스트에 push한다.

만약 수 플레그가 내려간 상태에서 읽은 토큰이 +,-,0~9까지의 수 중에 하나라면 수 플레그를 올리고,  ( ] , } , whitespace쪽 문자들, ,)이 읽힐때까지 문자를 읽어서 oss에 더해준다.
만약 수 플레그가 올라간 상태에서 읽은 토큰이 ( ] , } , whitespace쪽 문자들, ,) 를 제외한 json의 numbers 범위에 들어가지 않는 문자라면 무시한다.
e또는 E와 +또는 -, .의 갯수를 센다.
다 읽으면 수 플레그를 내리고 검사를 시작한다.
검사
{
만약 e또는 E가 2개 이상 사용되거나, +또는 -가 3개 이상 사용되거나, .이 2개 이상 사용되면 false 리턴
부호를 제외한 가장 첫 문자가 .이라면 false 리턴

부호 앞에 수가 온다면 false 리턴 
부호 뒤에 수가 없다면 false리턴

. 앞과 뒤에 수가 없다면 false리턴

e 또는 E 앞에 수가 없다면 false리턴
e 또는 E 뒤에 아무것도 없다면 false 리턴


e또는 E가 있거나, .이 있다면 d를 oss에 더해준다.

}






만약 :다음에 읽은 토큰이 ,거나 },]라면 리스트를 비우고 false리턴
만약 , 다음에 읽은 토큰이 "이 아니라면 false리턴

oss알아보기
*/