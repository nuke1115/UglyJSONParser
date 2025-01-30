#include "..\Tokenizer.hpp"

bool UglyJSONParser::Tokenizer::TokenizeString(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index)
{
    //���� null�� ������ ������ ���̿��� 1�� ������ ���� �ε����� ���̰� ���ٸ�, ���� ����ǥ �ϳ��� ������ �����°Ŵϱ�, �߸��� ���ڿ��̴�.
    if (index >= sourceString.size() - 1)
    {
        return false;
    }

    std::ostringstream oss;

    oss << sourceString[index];
    index++;

    size_t consecutiveBackslashCnt = 0;

    for (;index < sourceString.size(); index++)
    {
        if (sourceString[index] == TokenQuotationMark && (consecutiveBackslashCnt % 2 == 0)) // => consecutiveBackslashCnt ^ 1 <= ������������ �ٲ�
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

bool UglyJSONParser::Tokenizer::CheckTokenizedNumber(const std::string& numString, size_t exponentCnt, size_t signCnt, size_t pointCnt)
{
    if (exponentCnt > 1 || signCnt > 2 || pointCnt > 1)
    {
        return false;
    }

    //��ȣ�� �� �� �� �ƴҶ� true�� �Ǿ��Ѵ�.
    if (!IsItNumber(numString.front()) && (numString.front() != TokenPlus && numString.front() != TokenMinus))
    {
        return false;
    }

    //���� �ƴҶ� true�� �Ǿ��Ѵ�.
    if (!IsItNumber(numString.back()))
    {
        return false;
    }

    for (size_t i = 1; i < numString.size() - 1; i++)
    {
        if (numString[i] == TokenPlus || numString[i] == TokenMinus) // ��ȣ�϶�
        {
            //��ġ�� 0�� �ƴ� ��ȣ�� �տ��� ������ e �Ǵ� E�� �;��ϰ�, �ڿ��� ������ ���� �;��Ѵ�.
            //=> ��ġ�� 0�� �ƴ� ��ȣ�� �ڿ� ���� ���ų�, �տ� ������ ���ٸ� �߸��� �����̴�.
            if (!IsItNumber(numString[i + 1]) || (numString[i - 1] != TokenExponentUpper && numString[i - 1] != TokenExponentLower))
            {
                return false;
            }
        }
        else if (numString[i] == TokenDecimalPoint) //�Ҽ����϶�
        {
            //������ ��� ������ �Ѵ� => ���� ��� ���� �ƴϸ� �߸��� ����
            if (!IsItNumber(numString[i - 1]) || !IsItNumber(numString[i + 1]))
            {
                return false;
            }
        }
        else if (numString[i] == TokenExponentUpper || numString[i] == TokenExponentLower) //������ȣ�϶�
        {
            //������ ���� �տ��� ������ ���� �;��ϰ�, �ڿ��� ��ȣ �Ǵ� ���� �;��Ѵ�.
            //=> ������ ��� ���� ��ū�� ���� �ƴϰų�, �ڿ� ���� ��ū�� ��ȣ�� �� �� �� �ƴϸ� �߸��� �����̴�.
            if (!IsItNumber(numString[i - 1]) || (!IsItNumber(numString[i + 1]) && (numString[i + 1] != TokenPlus && numString[i + 1] != TokenMinus)))
            {
                return false;
            }
        }
    }
    //�� �� �� �� ������ �޷��ִٸ�, �� �� ���߿� �ϳ��� Ʋ����� Ʋ�������̴�.

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
            return false;//continue�� �ұ� �����غôµ�, �̷��� �߸����� �𸣴ϱ�... return false�� �ϴ����� ������Ҷ� ������ �ִٴ°� �˱⿡�� ���ҵ�
        }

        numberString.push_back(nowChar);
    }

    bool result =  CheckTokenizedNumber(numberString, exponentCnt, signCnt, decimalPointCnt);

    outTokenizedStrings.emplace_back(numberString);

    return result;
}
/*
stod�� ���� stoll�� ���� ���ϴ°�, Ʈ�� �����ϴ� �κп��� e�� E�� .�� �ִ��� �˻��ؼ� ���ϴ� ������� ����
*/

bool UglyJSONParser::Tokenizer::TokenizeBool(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index)
{
    if (CompareString(sourceString, TokenTrue, index))
    {
        outTokenizedStrings.emplace_back(TokenTrue);
        index += 3;
        return true;
    }
    else if (CompareString(sourceString, TokenFalse, index))
    {
        outTokenizedStrings.emplace_back(TokenFalse);
        index += 4;
        return true;
    }
    else
    {
        return false;
    }
}

bool UglyJSONParser::Tokenizer::TokenizeNull(const std::string& sourceString, std::list<std::string>& outTokenizedStrings, size_t& index)
{
    if (CompareString(sourceString, TokenNull, index) == false)
    {
        return false;
    }

    outTokenizedStrings.emplace_back(TokenNull);
    index += 3;

    return true;
}

bool UglyJSONParser::Tokenizer::Tokenize(const std::string& sourceString, std::list<std::string>& outTokenizedStrings)
{
    if (sourceString.empty())
    {
        return false;
    }
    
    bool result = true;

    for (size_t i = 0; i < sourceString.size(); i++)
    {
        if (sourceString[i] == TokenObjectStart || sourceString[i] == TokenObjectEnd || sourceString[i] == TokenArrayStart || sourceString[i] == TokenArrayEnd || sourceString[i] == TokenComma || sourceString[i] == TokenColon)
        {
            outTokenizedStrings.emplace_back(1,sourceString[i]);
        }
        else if (sourceString[i] == TokenQuotationMark)
        {
            result = TokenizeString(sourceString,outTokenizedStrings, i);
        }
        else if ((sourceString[i] == TokenPlus || sourceString[i] == TokenMinus) || (NumRangeStart <= sourceString[i] && sourceString[i] <= NumRangeEnd))
        {
            result = TokenizeNumber(sourceString, outTokenizedStrings, i);
        }
        else if (sourceString[i] == TokenTrue[0] || sourceString[i] == TokenFalse[0])
        {
            result = TokenizeBool(sourceString, outTokenizedStrings, i);
        }
        else if (sourceString[i] == TokenNull[0])
        {
            result = TokenizeNull(sourceString, outTokenizedStrings, i);
        }

        if (result == false)
        {
            outTokenizedStrings.clear();
            return false;
        }
    }

    return true;
}

/*
���� ���ڰ� ��ȣ ��ū��( {,},[,] ) �̰͵��̶�� �ٷ� ����Ʈ�� push�ϰ� �������ڸ� �д´�.
���� ���ڰ� ��ǥ��ū�̶�� �ٷ� ����Ʈ�� push�ϰ� �������ڸ� �д´�.
���� ���ڰ� :��ū�̶�� �ٷ� ����Ʈ�� push�ϰ� �������ڸ� �д´�.

���� ���ڿ� �÷��װ� ������ ���¿��� ���� ��ū�� " ��ū�̶��, ���ڿ� �÷��׸� �ø���, ���� ���ڿ� ���� oss�� ���� " ��ū�� ���������� �ٸ� ó���������� �Ȱ���, ���ڿ��� �о oss�� �����ش�.
���� ���ڿ� �÷��װ� �ö� ���¿��� ���� ��ū�� "�̸鼭 ���� ��ū�� \��� �׳� �����ش�. 
    �׷���,\ ������ �ٷ� �����ų�, \"������ �ƹ��� ���ڵ� ������ false����
���� ���ڿ� �÷��װ� �ö� ���¿��� ���� ��ū�� "�̶�� ���ڿ� �÷��׸� ������, oss���� ���ڿ��� �����ͼ� ����Ʈ�� push�Ѵ�.

���� �� �÷��װ� ������ ���¿��� ���� ��ū�� +,-,0~9������ �� �߿� �ϳ���� �� �÷��׸� �ø���,  ( ] , } , whitespace�� ���ڵ�, ,)�� ���������� ���ڸ� �о oss�� �����ش�.
���� �� �÷��װ� �ö� ���¿��� ���� ��ū�� ( ] , } , whitespace�� ���ڵ�, ,) �� ������ json�� numbers ������ ���� �ʴ� ���ڶ�� �����Ѵ�.
e�Ǵ� E�� +�Ǵ� -, .�� ������ ����.
e�Ǵ� E�� �ְų�, .�� �ִٸ� d�� oss�� �����ش�.
�� ������ �� �÷��׸� ������ �˻縦 �����Ѵ�.
�˻�
{
���� e�Ǵ� E�� 2�� �̻� ���ǰų�, +�Ǵ� -�� 3�� �̻� ���ǰų�, .�� 2�� �̻� ���Ǹ� false ����

��ȣ�� �ִ� �ε����� 0�� �ƴϸ鼭 �տ� e �Ǵ� E�� ���� �ʴ´ٸ� false ����.
��ȣ �ڿ� ���� ���ٸ� false ����.

. ���ʿ� ���� ���ٸ� false ����.

e �Ǵ� E �տ� ���� ���ٸ� false ����.
e �Ǵ� E �ڿ� ��ȣ �Ǵ� ���� ���ٸ� false ����.


}
//////
*/