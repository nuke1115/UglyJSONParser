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
�� ������ �� �÷��׸� ������ �˻縦 �����Ѵ�.
�˻�
{
���� e�Ǵ� E�� 2�� �̻� ���ǰų�, +�Ǵ� -�� 3�� �̻� ���ǰų�, .�� 2�� �̻� ���Ǹ� false ����
��ȣ�� ������ ���� ù ���ڰ� .�̶�� false ����

��ȣ �տ� ���� �´ٸ� false ���� 
��ȣ �ڿ� ���� ���ٸ� false����

. �հ� �ڿ� ���� ���ٸ� false����

e �Ǵ� E �տ� ���� ���ٸ� false����
e �Ǵ� E �ڿ� �ƹ��͵� ���ٸ� false ����


e�Ǵ� E�� �ְų�, .�� �ִٸ� d�� oss�� �����ش�.

}






���� :������ ���� ��ū�� ,�ų� },]��� ����Ʈ�� ���� false����
���� , ������ ���� ��ū�� "�� �ƴ϶�� false����

oss�˾ƺ���
*/