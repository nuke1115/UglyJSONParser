#include "../../Include/UglyJSONParser/Tokenizer/Tokenizer.hpp"

bool UglyJSONParser::Tokenizer::TokenizeString(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index)
{
    //size()는 끝의 \0을 제외한 char들의 갯수(길이)를 반환한다. 그렇다면 마지막 char의 index는 size()-1이다.
    //만약 null을 제외한 문자의 길이에서 1을 뺀것이 현제 인덱스와 길이가 같다면, 여는 따옴표 하나만 나오고 끝나는거니까, 잘못된 문자열이다.
    if (index >= sourceString.size() - 1)
    {
        return false;
    }

    std::string str = "";

    str.push_back(sourceString[index]);
    index++;

    // backslash는 자신 바로 뒤의 문자를 이스케이프처리한다.
    // \"는 이스케이프 처리된 문자이기에, 이런 형태의 "에서는 종료를 하면 안된다.
    // 하지만 \\" 는 이스케이프된 backslash에 "가 붙은것이기에, 이것은 정상적으로 종료처리를 해야된다.
    // 저런 이스케이프된 backslash는 무조건 짝수개로 연속되서 나오기에, 이 변수가 짝수일때+지금 토큰이 "때를 루프 중도 종료조건으로 설정했다.
    size_t consecutiveBackslashCnt = 0;

    for (char nowChar;index < sourceString.size(); index++)
    {
        nowChar = sourceString[index];
        if (nowChar == Tokens::TokenQuotationMark && (consecutiveBackslashCnt % 2 == 0)) // => consecutiveBackslashCnt ^ 1 <= 가독성때문에 바꿈
        {
            str.push_back(nowChar);

            outTokenizedStrings.push_back(str);

            return true;
        }

        if (nowChar == Tokens::TokenBackslash)
        {
            consecutiveBackslashCnt++;
        }
        else
        {
            consecutiveBackslashCnt = 0;
        }

        str.push_back(nowChar);
    }

    return false;
}

bool UglyJSONParser::Tokenizer::CheckTokenizedNumber(const string& numString, size_t exponentCnt, size_t signCnt, size_t pointCnt)
{
    if (exponentCnt > 1 || signCnt > 2 || pointCnt > 1 || numString.empty())
    {
        return false;
    }
    
    //시작은 부호와 수 둘 다 아닐때 true가 되야한다.
    if (!(StringUtils::IsItDigit(numString.front()) || StringUtils::IsItSign(numString.front())))
    {
        return false;
    }

    //끝은 수가 아닐때 true가 되야한다.
    if (!StringUtils::IsItDigit(numString.back()))
    {
        return false;
    }

    //이미 앞에서 양 끝쪽 케이스 처리했으니까 양 끝은 검사하지 않는다.
    for (size_t i = 1; i < numString.size() - 1; i++)
    {
        if (StringUtils::IsItSign(numString[i])) // 부호일때
        {
            //위치가 0이 아닌 부호는 앞에는 무조건 e 또는 E가 와야하고, 뒤에는 무조건 수가 와야한다.
            //=> 위치가 0이 아닌 부호는 뒤에 수가 없거나, 앞에 지수가 없다면 잘못된 문법이다.
            if (!(numString[i - 1] == Tokens::TokenExponentUpper || numString[i - 1] == Tokens::TokenExponentLower) || !StringUtils::IsItDigit(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == Tokens::TokenDecimalPoint) //소수점일때
        {
            //양쪽이 모두 수여야 한다 => 양쪽 모두 수가 아니면 잘못된 문법
            if (!StringUtils::IsItDigit(numString[i - 1]) || !StringUtils::IsItDigit(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == Tokens::TokenExponentUpper || numString[i] == Tokens::TokenExponentLower) //지수기호일때
        {
            //지수의 경우는 앞에는 무조건 수가 와야하고, 뒤에는 부호 또는 수가 와야한다.
            //=> 지수의 경우 앞의 토큰이 수가 아니거나, 뒤에 오는 토큰이 부호와 수 둘 다 아니면 잘못된 문법이다.
            if (!StringUtils::IsItDigit(numString[i - 1]) || !(StringUtils::IsItDigit(numString[i + 1]) || StringUtils::IsItSign(numString[i + 1])))
            {
                return false;
            }
        }
    }
    //앞 뒤 둘 다 조건이 달려있다면, 앞 뒤 둘중에 하나라도 틀릴경우 틀린문법이다.

    return true;
}

bool UglyJSONParser::Tokenizer::TokenizeNumber(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index)
{
    string numberString = "";

    size_t exponentCnt = 0, signCnt = 0, decimalPointCnt = 0;

    for (; index < sourceString.size(); index++)
    {
        char nowChar = sourceString[index];
        
        if (StringUtils::IsItClosingToken(nowChar) || nowChar == Tokens::TokenComma || nowChar == Tokens::TokenSpace || nowChar == Tokens::TokenLineFeed || nowChar == Tokens::TokenCarriageReturn || nowChar == Tokens::TokenHorizontalTab)
        {
            index--; //numbers에 들어가지 않는 문자를 루프 종료조건으로 하고있는데, 이 함수를 탈출하면 index++이 for에서 호출된다. 그러면 지금 읽은 이 문자는 버려지기에 그걸 방지하고자 이렇게 썼다.
            break;
        }
        
        if (nowChar == Tokens::TokenExponentUpper || nowChar == Tokens::TokenExponentLower)
        {
            exponentCnt++;
        }
        else if (nowChar == Tokens::TokenDecimalPoint)
        {
            decimalPointCnt++;
        }
        else if (StringUtils::IsItSign(nowChar))
        {
            signCnt++;
        }
        else if (!StringUtils::IsItDigit(nowChar))
        {
            return false;//continue로 할까 생각해봤는데, 이러면 잘못된줄 모르니까... return false로 하는편이 디버깅할때 문제가 있다는걸 알기에는 편할듯
        }

        numberString.push_back(nowChar);
    }

    bool result =  CheckTokenizedNumber(numberString, exponentCnt, signCnt, decimalPointCnt);

    if (result)
    {
        outTokenizedStrings.push_back(numberString);
    }

    return result;
}

bool UglyJSONParser::Tokenizer::TokenizeBool(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index)
{
    if (StringUtils::CompareString(sourceString, Tokens::TokenTrue, index))
    {
        outTokenizedStrings.push_back(Tokens::TokenTrue);
        index += 3;
        return true;
    }
    else if (StringUtils::CompareString(sourceString, Tokens::TokenFalse, index))
    {
        outTokenizedStrings.push_back(Tokens::TokenFalse);
        index += 4;
        return true;
    }
    
    return false;
}

bool UglyJSONParser::Tokenizer::TokenizeNull(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index)
{
    if (StringUtils::CompareString(sourceString, Tokens::TokenNull, index) == false)
    {
        return false;
    }
    
    outTokenizedStrings.push_back(Tokens::TokenNull);
    index += 3;

    return true;
}

bool UglyJSONParser::Tokenizer::CheckTokenizedTokens(const std::list<string>& tokenizedStrings)
{
    if (tokenizedStrings.empty())
    {
        return false;
    }

    size_t rootValueCnt = 0;//스택이 비어있을때 arr,obj의 시작괄호, singlejsonvalue에 속하는 값이 감지되면 +1

    std::stack<char> indentationStack;

    if ((tokenizedStrings.front().front() == Tokens::TokenColon || tokenizedStrings.front().front() == Tokens::TokenComma) ||
        (tokenizedStrings.back().front() == Tokens::TokenColon || tokenizedStrings.back().front() == Tokens::TokenComma))
    {
        return false;
    }
    
    for (auto presentIter = tokenizedStrings.begin(); presentIter != tokenizedStrings.end() && rootValueCnt < 2; presentIter++)
    {
        if (StringUtils::IsItOpeningToken(presentIter->front()))
        {
            if (indentationStack.empty())
            {
                rootValueCnt++;
            }

            auto nextIter = std::next(presentIter);

            if (nextIter == tokenizedStrings.end())
            {
                return false;
            }
            else if (presentIter->front() == Tokens::TokenObjectStart && !(TypeUtils::IsItJsonString(*nextIter) || nextIter->front() == Tokens::TokenObjectEnd))
            {
                return false;
            }
            else if (presentIter->front() == Tokens::TokenArrayStart && !(StringUtils::IsItOpeningToken(nextIter->front()) || TypeUtils::IsItSingleJsonValue(*nextIter) || nextIter->front() == Tokens::TokenArrayEnd))
            {
                return false;
            }

            indentationStack.push(presentIter->front());
        }
        else if (StringUtils::IsItClosingToken(presentIter->front()))
        {
            if (indentationStack.empty() || (indentationStack.top() == Tokens::TokenObjectStart && presentIter->front() == Tokens::TokenArrayEnd)
                || (indentationStack.top() == Tokens::TokenArrayStart && presentIter->front() == Tokens::TokenObjectEnd))
            {
                return false;
            }

            indentationStack.pop();
        }
        else if (presentIter->front() == Tokens::TokenColon)
        {
            auto nextIter = std::next(presentIter), pastIter = std::prev(presentIter);
            if (indentationStack.empty() || indentationStack.top() != Tokens::TokenObjectStart)
            {
                return false;
            }

            if (!TypeUtils::IsItJsonString(*pastIter) || !(StringUtils::IsItOpeningToken(nextIter->front()) || TypeUtils::IsItSingleJsonValue(*nextIter)))
            {
                return false;
            }
        }
        else if (presentIter->front() == Tokens::TokenComma)
        {
            auto nextIter = std::next(presentIter), pastIter = std::prev(presentIter);
            if (indentationStack.empty())
            {
                return false;
            }

            if (!(StringUtils::IsItClosingToken(pastIter->front()) || TypeUtils::IsItSingleJsonValue(*pastIter)))
            {
                return false;
            }

            if (indentationStack.top() == Tokens::TokenObjectStart && !TypeUtils::IsItJsonString(*nextIter))
            {
                return false;
            }
            else if (indentationStack.top() == Tokens::TokenArrayStart && !(StringUtils::IsItOpeningToken(nextIter->front()) || TypeUtils::IsItSingleJsonValue(*nextIter)))
            {
                return false;
            }
        }
        else if (indentationStack.empty() && TypeUtils::IsItSingleJsonValue(*presentIter))
        {
            rootValueCnt++;
        }

    }

    if (!indentationStack.empty() || rootValueCnt > 1)
    {
        return false;
    }

    return true;
}

bool UglyJSONParser::Tokenizer::Tokenize(const string& sourceString, std::list<string>& outTokenizedStrings)
{
    if (sourceString.empty())
    {
        return false;
    }

    bool result = true;
    outTokenizedStrings.clear();

    for (size_t i = 0; i < sourceString.size() && result; i++)
    {
        char nowChar = sourceString[i];
        if (StringUtils::IsItOpeningToken(nowChar) || StringUtils::IsItClosingToken(nowChar) || nowChar == Tokens::TokenComma || nowChar == Tokens::TokenColon)
        {
            outTokenizedStrings.push_back(string(1,nowChar));// 이게 더 읽기는 편할거같아서 이렇게 씁니다. 컴파일러야 힘내라!//emplace_back(1, nowChar); old
        }
        else if (nowChar == Tokens::TokenQuotationMark)
        {
            result = TokenizeString(sourceString, outTokenizedStrings, i);
        }
        else if ( StringUtils::IsItSign(nowChar) || StringUtils::IsItDigit(nowChar))
        {
            result = TokenizeNumber(sourceString, outTokenizedStrings, i);
        }
        else if (nowChar == Tokens::TokenTrue[0] || nowChar == Tokens::TokenFalse[0])
        {
            result = TokenizeBool(sourceString, outTokenizedStrings, i);
        }
        else if (nowChar == Tokens::TokenNull[0])
        {
            result = TokenizeNull(sourceString, outTokenizedStrings, i);
        }
    }

    if (result == false)
    {
        outTokenizedStrings.clear();
    }

    return CheckTokenizedTokens(outTokenizedStrings);
}