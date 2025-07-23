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


    auto f = ResultUtils::DecodeErrorBitMask;

    std::cout << f(root.CreateNewNode(NodeType::Array,).GetErrorInfoMask());

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
