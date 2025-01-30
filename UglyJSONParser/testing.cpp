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
    
    std::string strJ = "{\"string\": \"Hello\",\"number\": 123,\"boolean_true\": true,\"boolean_false\": false,\"null_value\": null,\"array\": [1, 2, 3],\"object\": {\"key\": \"value\"},\"large_number\": 1234567890,\"float_number\": 3.14,\"exponential_number\": 1.23e4,\"date\": \"2025-01-29T12:00:00Z\"}";
    std::string str = "\"";
    std::list<std::string> list;


    std::cout << tokenizer.Tokenize(strJ, list) << '\n';

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