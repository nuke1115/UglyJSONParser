#include<stdio.h>
#include<iostream>
#include <fstream>

//#include ".\src\headers\JsonTree\Node.hpp"
#include ".\src\headers\FileIO\FileIOManager.hpp"
#include ".\src\headers\Tokenizer\Tokenizer.hpp"

using namespace UglyJSONParser;

void run()
{
    Tokenizer tokenizer;

    std::string str = "12e+18";
    std::list<std::string> list;

    std::cout << tokenizer.Tokenize(str, list) << '\n';

    for (auto& i : list)
    {
        std::cout << i << '\n';
    }
    

}

int main()
{
    run();




}
/*

operator �����ε带 �Ҷ�, �������� ���� �����ε�� ���� Ÿ���� ���������� ������, �⺻������ bool���·� �޴´�.

������ ��ȯ �����Ѱ� ���� �����ε尡 ������ bool�� ��ȯ�Ѵ�
=>���� ��ȯ ������ Ÿ�Ե鳢���� ������� �����ε尡 ����, �־��ִ� Ÿ�Կ� �´� �����ε尡 ������, �Ͻ������� ��ȯ�Ǿ ����.
https://stackoverflow.com/questions/66452781/why-const-char-implicitly-converted-to-bool-rather-than-stdstring
https://en.cppreference.com/w/cpp/language/overload_resolution

ǥ�غ�ȯ, ����� ���� ��ȯ





---------------

���� �б�//v
������ ��ū������ ����
��ū�� ������� Ʈ�� ����
����

jsonƮ���� ���ڿ��� ��ȯ//v
���Ͽ� ����//v



---------
���� i/o�ý��� �����

��ũ������, ���� �����

Ʈ�� ������ �����


------------


std::_Fac_node �����ִ� ���� <== std::ifstream std::ostream 

------------

ostringstream �� �˾ƺ���
�� ��ȿ�����̸� ����ġ����



*/