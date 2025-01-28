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
//size_t ����÷ο� ���� ����
    // index - 1�� ����÷ο찡 �ȳ��°��� ����ȴ�.
    // 
    //���� \ �� �������� ���̽� ó��

bool UglyJSONParser::Tokenizer::CheckTokenizedNumber(const std::string& numString, size_t exponentCnt, size_t signCnt, size_t pointCnt)//���� ��ġ��, �ڵ� �ٵ��
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
        if (numString[i] == TokenPlus || numString[i] == TokenMinus) // ��ȣ�϶�
        {
            //��ġ�� 0�� �ƴ� ��ȣ�� �տ��� ������ e �Ǵ� E�� �;��ϰ�, �ڿ��� ������ ���� �;��Ѵ�.
            //=> ��ġ�� 0�� �ƴ� ��ȣ�� �տ� e�ϰ� E �� �� ���ų�, �ڿ� ���� ������ �߸��� �����̴�.
            if ((numString[i - 1] != TokenExponentUpper && numString[i - 1] != TokenExponentLower) || !IsItNumber(numString[i + 1]))
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
            if (!IsItNumber(numString[i - 1]) || (!IsItNumber(numString[i + 1]) && (numString[i + 1] != TokenPlus && numString[i + 1] != TokenMinus)))//���� �ٽ� ������ ���캸��
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
            continue;
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






���� :������ ���� ��ū�� ,�ų� },]��� ����Ʈ�� ���� false����
���� , ������ ���� ��ū�� "�� �ƴ϶�� false����

oss�˾ƺ���
*/