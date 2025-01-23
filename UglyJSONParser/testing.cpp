#include<stdio.h>
#include<iostream>

#include ".\headers\JsonTree\Node.hpp"

using namespace UglyJSONParser;


void do_test()
{
    ObjectNode val("root");

    val.CreateNewNode(NodeType::SingleValue, "c1");
    val["c1"] = 1;

    val.CreateNewNode(NodeType::Object, "o1");
    val["o1"].CreateNewNode(NodeType::SingleValue, "c2");
    val["o1"]["c2"] = "fuck";


    std::cout << val.GetJsonTreeByString() << '\n';

    val.DeleteChildNode("c1");
    val["o1"]["c2"] = 18;

    val.CreateNewNode(NodeType::Array, "a1");

    val["a1"].CreateNewNode(NodeType::SingleValue);
    val["a1"].CreateNewNode(NodeType::SingleValue);

    val["a1"][0] = 1;
    val["a1"][1] = 2;

    std::cout << val.GetJsonTreeByString() << '\n';

    val["a1"][1] = "fuck";

    val["a1"].CreateNewNode(NodeType::Null);
    val["o1"].CreateNewNode(NodeType::Null,"this is null");

    val["a1"].CreateNewNode(NodeType::SingleValue);
    val["a1"][3] = false;

    std::cout << val.GetJsonTreeByString()<<'\n';

    
}

int main()
{
    //todo. 디버깅 코드 지우기
    int brk;
    //scanf_s("%d",&brk);
    

    
    do_test();
    

    //scanf_s("%d", &brk);
}
/*

operator 오버로드를 할때, 포인터의 경우는 오버로드로 따로 타입을 지정해주지 않으면, 기본적으로 bool형태로 받는다.

정수로 변환 가능한건 따로 오버로드가 없으면 bool로 변환한다
=>서로 변환 가능한 타입들끼리는 명시적인 오버로드가 없고, 넣어주는 타입에 맞는 오버로드가 없으면, 암시적으로 변환되어서 들어간다.
https://stackoverflow.com/questions/66452781/why-const-char-implicitly-converted-to-bool-rather-than-stdstring
https://en.cppreference.com/w/cpp/language/overload_resolution

표준변환, 사용자 정의 변환

*/