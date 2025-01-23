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
    //todo. ����� �ڵ� �����
    int brk;
    //scanf_s("%d",&brk);
    

    
    do_test();
    

    //scanf_s("%d", &brk);
}
/*

operator �����ε带 �Ҷ�, �������� ���� �����ε�� ���� Ÿ���� ���������� ������, �⺻������ bool���·� �޴´�.

������ ��ȯ �����Ѱ� ���� �����ε尡 ������ bool�� ��ȯ�Ѵ�
=>���� ��ȯ ������ Ÿ�Ե鳢���� ������� �����ε尡 ����, �־��ִ� Ÿ�Կ� �´� �����ε尡 ������, �Ͻ������� ��ȯ�Ǿ ����.
https://stackoverflow.com/questions/66452781/why-const-char-implicitly-converted-to-bool-rather-than-stdstring
https://en.cppreference.com/w/cpp/language/overload_resolution

ǥ�غ�ȯ, ����� ���� ��ȯ

*/