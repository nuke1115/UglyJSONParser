#include<stdio.h>
#include<iostream>
#include <fstream>

#include ".\src\headers\JsonTree\Node.hpp"
#include ".\src\headers\FileIO\FileIOManager.hpp"
#include ".\src\headers\Tokenizer\Tokenizer.hpp"
#include ".\src\headers\JsonTree\JSONTreeBuilder.hpp"

using namespace UglyJSONParser;


void run()
{
    std::string str;
    std::list<std::string> tokens;
    RootNode root;

    FileIOManager fileIO;
    Tokenizer tokenizer;
    JSONTreeBuilder builder;
    
    fileIO.LoadTextFromFile(str, "E:\\새 폴더 (2)\\json.json");
    
    tokenizer.Tokenize(str, tokens);

    builder.BuildJSONTree(root, tokens);

    

    std::cout << root.GetChildNodeCount() << '\n' << root["age"].GetChildNodeCount() << '\n';


    std::cout << root.GetJsonTreeByString();

    std::cout << fileIO.WriteTextToFile(root.GetJsonTreeByString(), "E:\\새 폴더 (2)\\json.json");


   /*
   todo:
   getChildCnt 함수 만들기 (만들어야되는 함수 있나 찾아보기)


   버그 잡기
   리펙토링하기
   하나의 클래스로 만들기
   */
}

int main()
{
    run();




}
/*

operator 오버로드를 할때, 포인터의 경우는 오버로드로 따로 타입을 지정해주지 않으면, 기본적으로 bool형태로 받는다.

정수로 변환 가능한건 따로 오버로드가 없으면 bool로 변환한다
=>서로 변환 가능한 타입들끼리는 명시적인 오버로드가 없고, 넣어주는 타입에 맞는 오버로드가 없으면, 암시적으로 변환되어서 들어간다.
https://stackoverflow.com/questions/66452781/why-const-char-implicitly-converted-to-bool-rather-than-stdstring
https://en.cppreference.com/w/cpp/language/overload_resolution

표준변환, 사용자 정의 변환

---------------

트리를 어떤형태로 빌드하고, 리턴할까?

root노드 클래스를 만들고, 거기 내부에 basenode* 변수를 만들고,
빌드함수에 루트노드 인스턴스를 넣어주면, 그걸 기반으로 빌드한다?

루트노드는 단순히 첫번째 노드에 접근하는 역할만 한다.




---------------

파일 읽기//v
파일을 토큰단위로 분해//v
토큰을 기반으로 트리 생성//v
리턴

json트리를 문자열로 변환//v
파일에 쓰기//v



---------
파일 i/o시스템 만들기

토크나이저, 렉서 만들기

트리 생성기 만들기


------------


std::_Fac_node 남아있는 문제 <== std::ifstream std::ostream 

------------

ostringstream 더 알아보기
더 비효율적이면 갈아치우자

-------------

리팩토링
class private멤버변수들 앞에 _ 다 붙이기

*/