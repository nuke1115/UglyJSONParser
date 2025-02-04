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
    
    fileIO.LoadTextFromFile(str, "E:\\�� ���� (2)\\json.json");
    
    tokenizer.Tokenize(str, tokens);

    builder.BuildJSONTree(root, tokens);

    

    std::cout << root.GetChildNodeCount() << '\n' << root["age"].GetChildNodeCount() << '\n';


    std::cout << root.GetJsonTreeByString();

    std::cout << fileIO.WriteTextToFile(root.GetJsonTreeByString(), "E:\\�� ���� (2)\\json.json");


   /*
   todo:
   getChildCnt �Լ� ����� (�����ߵǴ� �Լ� �ֳ� ã�ƺ���)


   ���� ���
   �����丵�ϱ�
   �ϳ��� Ŭ������ �����
   */
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

Ʈ���� ����·� �����ϰ�, �����ұ�?

root��� Ŭ������ �����, �ű� ���ο� basenode* ������ �����,
�����Լ��� ��Ʈ��� �ν��Ͻ��� �־��ָ�, �װ� ������� �����Ѵ�?

��Ʈ���� �ܼ��� ù��° ��忡 �����ϴ� ���Ҹ� �Ѵ�.




---------------

���� �б�//v
������ ��ū������ ����//v
��ū�� ������� Ʈ�� ����//v
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

-------------

�����丵
class private��������� �տ� _ �� ���̱�

*/