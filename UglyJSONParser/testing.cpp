#include<stdio.h>
#include<iostream>
#include <fstream>


#include ".\src\headers\UglyJSONParserInclude.hpp"
using namespace UglyJSONParser;


void run()
{
    std::string str, jsonFilePath = "E:\\새 폴더 (2)\\json.json";
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
난 이걸 정적라이브러리로 배포하고싶다.
저거 헤더들을 한번에 include가능하도록 뭐 하기
전부 include라는 폴더에 위치해있다.
src하고 include하고 따로 나뉘어져있다.
그러면 github에 올릴때, include버전하고 src버전하고 폴더를 나눌까?
----------

include 폴더 구조:


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