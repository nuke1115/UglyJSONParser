#include<stdio.h>
#include<iostream>
#include <fstream>


#include ".\src\headers\UglyJSONParserInclude.hpp"
using namespace UglyJSONParser;


void run()
{
    std::string str, jsonFilePath = "E:\\�� ���� (2)\\json.json";
    RootNode root;

    JSONParser parser;

    std::cout << parser.BuildJSONTreeFromFile(jsonFilePath, root) << '\n';


    std::cout << root.GetJsonTreeByString() << '\n';


    std::cout << parser.SaveJSONTreeToFile(jsonFilePath, root) << '\n';

}

int main()
{
    run();

    using namespace std;
    
    
    
    ios::in;
    ios::out;
    ios::ate;
    ios::app;
    ios::trunc;
    ios::binary;

}
/*
todo
------
�� �̰� �������̺귯���� �����ϰ�ʹ�.
���� ������� �ѹ��� include�����ϵ��� �� �ϱ�
���� include��� ������ ��ġ���ִ�.
src�ϰ� include�ϰ� ���� ���������ִ�.
�׷��� github�� �ø���, include�����ϰ� src�����ϰ� ������ ������?
----------

include ���� ����:


include
{
    UglyJSONParserInclude.hpp

    FileIO.hpp
    JSONTree.hpp
    Tokenizer.hpp
    JSONParser.hpp
    Utils.hpp

    libs
    {
        lib
    }
}


*/