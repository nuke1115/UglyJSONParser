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

bool UglyJSONParser::Tokenizer::CheckTokenizedNumber(const std::string& numString, size_t exponentCnt, size_t signCnt, size_t pointCnt)//버그 고치기, 코드 다듬기
{
    if (exponentCnt > 1 || signCnt > 2 || pointCnt > 1)
    {
        return false;
    }

    if (numString.front() == TokenDecimalPoint || (numString.front() == TokenExponentUpper || numString.front() == TokenExponentLower))
    {
        return false;
    }

    if (numString.back() == TokenDecimalPoint || (numString.back() == TokenExponentUpper || numString.back() == TokenExponentLower) || (numString.back() == TokenPlus || numString.back() == TokenMinus))
    {
        return false;
    }

    for (size_t i = 1; i < numString.size() - 1; i++)
    {
        if (numString[i] == TokenPlus || numString[i] == TokenMinus) // 부호일때
        {
            //위치가 0이 아닌 부호는 앞에는 무조건 e 또는 E가 와야하고, 뒤에는 무조건 수가 와야한다.
            //=> 위치가 0이 아닌 부호는 앞에 e하고 E 둘 다 없거나, 뒤에 수가 없으면 잘못된 문법이다.
            if ((numString[i - 1] != TokenExponentUpper && numString[i - 1] != TokenExponentLower) || !IsItNumber(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == TokenDecimalPoint) //소수점일때
        {
            //양쪽이 모두 수여야 한다 => 양쪽 모두 수가 아니면 잘못된 문법
            if (!IsItNumber(numString[i - 1]) || !IsItNumber(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == TokenExponentUpper || numString[i] == TokenExponentLower) //지수기호일때
        {
            //지수의 경우는 앞에는 무조건 수가 와야하고, 뒤에는 부호 또는 수가 와야한다.
            //=> 지수의 경우 앞의 토큰이 수가 아니거나, 뒤에 오는 토큰이 부호와 수 둘 다 아니면 잘못된 문법이다.
            if (!IsItNumber(numString[i - 1]) || (!IsItNumber(numString[i + 1]) && (numString[i + 1] != TokenPlus && numString[i + 1] != TokenMinus)))//조건 다시 유심히 살펴보기
            {
                return false;
            }
        }
    }
    //앞 뒤 둘 다 조건이 달려있다면, 앞 뒤 둘중에 하나라도 틀릴경우 틀린문법이다.

    return true;
}

bool UglyJSONParser::Tokenizer::TokenizeNumber(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index)
{
    string numberString = "";

    size_t exponentCnt = 0, signCnt = 0, decimalPointCnt = 0;

    for (char nowChar; index < sourceString.size(); index++)
    {
        nowChar = sourceString[index];

        if (nowChar == TokenObjectEnd || nowChar == TokenArrayEnd || nowChar == TokenComma || nowChar == TokenSpace || nowChar == TokenLineFeed || nowChar == TokenCarriageReturn || nowChar == TokenHorizontalTab)
        {
            index--;
            break;
        }

        if (nowChar == TokenExponentUpper || nowChar == TokenExponentLower)
        {
            exponentCnt++;
        }
        else if (nowChar == TokenDecimalPoint)
        {
            decimalPointCnt++;
        }
        else if (nowChar == TokenPlus || nowChar == TokenMinus)
        {
            signCnt++;
        }
        else if (nowChar < NumRangeStart || nowChar > NumRangeEnd)
        {
            continue;
        }

        numberString.push_back(nowChar);
    }

    bool result =  CheckTokenizedNumber(numberString, exponentCnt, signCnt, decimalPointCnt);

    outTokenizedStrings.emplace_back(numberString);

    return result;
}
/*
stod로 할지 stoll로 할지 정하는건, 트리 생성하는 부분에서 e나 E나 .이 있는지 검사해서 정하는 방식으로 하자
*/

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
        else if ((sourceString[i] == TokenPlus || sourceString[i] == TokenMinus) || (NumRangeStart <= sourceString[i] && sourceString[i] <= NumRangeEnd))
        {
            bool result = TokenizeNumber(sourceString, outTokenizedStrings, i);
            if (result == false)
            {
                outTokenizedStrings.clear();
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
e또는 E가 있거나, .이 있다면 d를 oss에 더해준다.
다 읽으면 수 플레그를 내리고 검사를 시작한다.
검사
{
만약 e또는 E가 2개 이상 사용되거나, +또는 -가 3개 이상 사용되거나, .이 2개 이상 사용되면 false 리턴

부호가 있는 인덱스가 0이 아니면서 앞에 e 또는 E가 오지 않는다면 false 리턴.
부호 뒤에 수가 없다면 false 리턴.

. 양쪽에 수가 없다면 false 리턴.

e 또는 E 앞에 수가 없다면 false 리턴.
e 또는 E 뒤에 부호 또는 수가 없다면 false 리턴.


}






만약 :다음에 읽은 토큰이 ,거나 },]라면 리스트를 비우고 false리턴
만약 , 다음에 읽은 토큰이 "이 아니라면 false리턴

oss알아보기
*/