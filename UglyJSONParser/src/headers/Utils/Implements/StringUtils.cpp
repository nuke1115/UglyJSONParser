#include "..\StringUtils.hpp"

bool UglyJSONParser::StringUtils::CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex)
{
    //���� 1: ���� �ε����� Ÿ�� ���ڿ��� ���̺��� ���ų� ū��? // asdf���ڿ��� f�� ����Ű�� �ε��� => 3�� ������ ����. �ٵ� �ε����� 4�� ������ ������ ���� ����Ŵ�.
    //���� 2: Ÿ�� ���ڿ��� ���� �ε����� ����Ű�� ���ڸ� �����ؼ� null�� ������ �������� ���̰� Ű�� ���̺��� ª����?// Ű���� ���̰� ª���� �翬�� �ٸ���.
    if (targetStringStartIndex >= target.size() || target.size() - targetStringStartIndex < key.size())
    {
        return false;
    }

    for (size_t targetIndex = targetStringStartIndex, keyIndex = 0; keyIndex < key.size(); targetIndex++, keyIndex++)
    {
        if (target[targetIndex] != key[keyIndex])
        {
            return false;
        }
    }

    return true;
}

bool UglyJSONParser::StringUtils::IsItNumber(const char token)
{
    return '0' <= token && '9' >= token;
}

bool UglyJSONParser::StringUtils::IsItOpeningToken(const char token)
{
    return token == '{' || token == '[';
}

bool UglyJSONParser::StringUtils::IsItClosingToken(const char token)
{
    return token == '}' || token == ']';
}

bool UglyJSONParser::StringUtils::IsItSign(const char token)
{
    return token == '+' || token == '-';
}