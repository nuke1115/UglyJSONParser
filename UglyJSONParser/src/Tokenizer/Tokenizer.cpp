#include "../../Include/UglyJSONParser/Tokenizer/Tokenizer.hpp"

bool UglyJSONParser::Tokenizer::TokenizeString(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index)
{
    //size()�� ���� \0�� ������ char���� ����(����)�� ��ȯ�Ѵ�. �׷��ٸ� ������ char�� index�� size()-1�̴�.
    //���� null�� ������ ������ ���̿��� 1�� ������ ���� �ε����� ���̰� ���ٸ�, ���� ����ǥ �ϳ��� ������ �����°Ŵϱ�, �߸��� ���ڿ��̴�.
    if (index >= sourceString.size() - 1)
    {
        return false;
    }

    std::string str = "";

    str.push_back(sourceString[index]);
    index++;

    // backslash�� �ڽ� �ٷ� ���� ���ڸ� �̽�������ó���Ѵ�.
    // \"�� �̽������� ó���� �����̱⿡, �̷� ������ "������ ���Ḧ �ϸ� �ȵȴ�.
    // ������ \\" �� �̽��������� backslash�� "�� �������̱⿡, �̰��� ���������� ����ó���� �ؾߵȴ�.
    // ���� �̽��������� backslash�� ������ ¦������ ���ӵǼ� �����⿡, �� ������ ¦���϶�+���� ��ū�� "���� ���� �ߵ� ������������ �����ߴ�.
    size_t consecutiveBackslashCnt = 0;

    for (char nowChar;index < sourceString.size(); index++)
    {
        nowChar = sourceString[index];
        if (nowChar == Tokens::TokenQuotationMark && (consecutiveBackslashCnt % 2 == 0)) // => consecutiveBackslashCnt ^ 1 <= ������������ �ٲ�
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
    
    //������ ��ȣ�� �� �� �� �ƴҶ� true�� �Ǿ��Ѵ�.
    if (!(StringUtils::IsItDigit(numString.front()) || StringUtils::IsItSign(numString.front())))
    {
        return false;
    }

    //���� ���� �ƴҶ� true�� �Ǿ��Ѵ�.
    if (!StringUtils::IsItDigit(numString.back()))
    {
        return false;
    }

    //�̹� �տ��� �� ���� ���̽� ó�������ϱ� �� ���� �˻����� �ʴ´�.
    for (size_t i = 1; i < numString.size() - 1; i++)
    {
        if (StringUtils::IsItSign(numString[i])) // ��ȣ�϶�
        {
            //��ġ�� 0�� �ƴ� ��ȣ�� �տ��� ������ e �Ǵ� E�� �;��ϰ�, �ڿ��� ������ ���� �;��Ѵ�.
            //=> ��ġ�� 0�� �ƴ� ��ȣ�� �ڿ� ���� ���ų�, �տ� ������ ���ٸ� �߸��� �����̴�.
            if (!(numString[i - 1] == Tokens::TokenExponentUpper || numString[i - 1] == Tokens::TokenExponentLower) || !StringUtils::IsItDigit(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == Tokens::TokenDecimalPoint) //�Ҽ����϶�
        {
            //������ ��� ������ �Ѵ� => ���� ��� ���� �ƴϸ� �߸��� ����
            if (!StringUtils::IsItDigit(numString[i - 1]) || !StringUtils::IsItDigit(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == Tokens::TokenExponentUpper || numString[i] == Tokens::TokenExponentLower) //������ȣ�϶�
        {
            //������ ���� �տ��� ������ ���� �;��ϰ�, �ڿ��� ��ȣ �Ǵ� ���� �;��Ѵ�.
            //=> ������ ��� ���� ��ū�� ���� �ƴϰų�, �ڿ� ���� ��ū�� ��ȣ�� �� �� �� �ƴϸ� �߸��� �����̴�.
            if (!StringUtils::IsItDigit(numString[i - 1]) || !(StringUtils::IsItDigit(numString[i + 1]) || StringUtils::IsItSign(numString[i + 1])))
            {
                return false;
            }
        }
    }
    //�� �� �� �� ������ �޷��ִٸ�, �� �� ���߿� �ϳ��� Ʋ����� Ʋ�������̴�.

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
            index--; //numbers�� ���� �ʴ� ���ڸ� ���� ������������ �ϰ��ִµ�, �� �Լ��� Ż���ϸ� index++�� for���� ȣ��ȴ�. �׷��� ���� ���� �� ���ڴ� �������⿡ �װ� �����ϰ��� �̷��� ���.
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
            return false;//continue�� �ұ� �����غôµ�, �̷��� �߸����� �𸣴ϱ�... return false�� �ϴ����� ������Ҷ� ������ �ִٴ°� �˱⿡�� ���ҵ�
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

    size_t rootValueCnt = 0;//������ ��������� arr,obj�� ���۰�ȣ, singlejsonvalue�� ���ϴ� ���� �����Ǹ� +1

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
            outTokenizedStrings.push_back(string(1,nowChar));// �̰� �� �б�� ���ҰŰ��Ƽ� �̷��� ���ϴ�. �����Ϸ��� ������!//emplace_back(1, nowChar); old
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