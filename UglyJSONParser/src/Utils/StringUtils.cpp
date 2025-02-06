#include "..\..\Include\UglyJSONParser\Utils\StringUtils.hpp"

bool UglyJSONParser::StringUtils::CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex)
{
    //조건 1: 시작 인덱스가 타겟 문자열의 길이보다 같거나 큰가? // asdf문자열의 f를 가리키는 인덱스 => 3을 값으로 가짐. 근데 인덱스가 4를 값으로 가지면 범위 벗어난거다.
    //조건 2: 타겟 문자열의 시작 인덱스가 가리키는 문자를 포함해서 null을 제외한 끝까지의 길이가 키의 길이보다 짧은가?// 키보다 길이가 짧으면 당연히 다르지.
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