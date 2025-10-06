#include<stdio.h>
#include<iostream>
#include <fstream>
#include <xstring>

#include ".\Include\UglyJSONParser\UglyJSONParserIncludeHeader.hpp"

//x붙은게 비표준이었어...?
using namespace UglyJSONParser;

void print(double content)
{
    std::cout << content << '\n';
}

void print(std::string content)
{
    std::cout << content << '\n';
}

void print(bool content)
{
    std::cout << content << '\n';
}

void print(long long content)
{
    std::cout << content << '\n';
}   



class Test
{
    int *data=nullptr;
public:
    Test(int* ptr)
    {
        data = ptr;
        printf("%p 생성\n",data);
    }

    Test(const Test&)
    {
        printf("%p 복사\n", data);
    }

    Test(Test&&)
    {
        printf("%p 이동\n", data);
    }

    ~Test()
    {
        printf("%p 소멸\n", data);
    }
};


#include <optional>
#include <assert.h>



#include "Include/UglyJSONParser/ResultInclude.hpp"


enum I_HATE_ENUM_CLASS
{
    asdhflkjsaljkfdvmblkhjeghiihuwehjlkndsvuukjlnregfvdcujnrfgbijnerfgbkjnefkjnefvkjnedfvkjnvefkjedfjkedfkjnedfkjnkdjfvnkejfkfjkdf = 1
};


void run()
{
    //필요한 변수들 선언
    UglyJSONParser::JSONParser parser;
    UglyJSONParser::RootNode root;
    std::string json = "{\"key\":\"value and this is \\\"value\\\"\",   \"arr\" : [1,1e+4,1.234]}";

    //string을 기반으로 JSONTree 생성
    parser.BuildJSONTreeFromString(json, root);
    auto value1 = root["arr"].GetValueRef()[0].GetValueRef().AsInt().GetValue();//값 검사 안하고 했을 때

    
    auto res1 = root["arr"];
    if (!res1.HasValue())
    {
        return;
    }
    auto res2 = res1.GetValueRef()[0];
    if (!res2.HasValue())
    {
        return;
    }
    auto res3 = res2.GetValueRef().AsInt();
    if (!res3.HasValue())
    {
        return;
    }
    auto value2 = res3.GetValue();//값 검사 하면서 했을 때
    //둘 다 일단 코드가 복잡해지고, 첫번째는 이 구조로 고친 이유가 없어짐
    //=>체인을 만들어서 하면 더 깔끔하게 할 수 있을듯?

    printf("%lld %lld\n", value1, value2);
}

#include <mutex>
int main()
{

    run();
    //다시 빌드하기

    using namespace std;
    
    UglyJSONParser::BaseNode;
    
    ios::in;
    ios::out;
    ios::ate;
    ios::app;
    ios::trunc;
    ios::binary;
    UglyJSONParser::NodeType::Null;
    UglyJSONParser::NodeType::Object;
    UglyJSONParser::NodeType::Array;
    UglyJSONParser::NodeType::String;
    UglyJSONParser::NodeType::Number;
    UglyJSONParser::NodeType::Bool;
    UglyJSONParser::NodeType::Root;
    UglyJSONParser::NodeType::Error;
  
}
