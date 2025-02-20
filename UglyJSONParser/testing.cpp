#include<stdio.h>
#include<iostream>
#include <fstream>
#include <xstring>

#include ".\Include\UglyJSONParser\UglyJSONParserIncludeHeader.hpp"

//x������ ��ǥ���̾���...?
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
#include <SFML/Graphics.hpp>


/*
���׼��� �� ��� �߰� ���

1:JSONTreeBuilder�� ù��° �� �߰� ���ϴ� ����
���� ���̽�
1:const char*�� string�� �ƴ�bool�� �ν��ߴ�
2:long long, double, bool�� ������, int�����͸� �ָ�, ���� 3���� �� �ɸ���

*/





/*
�ƴ� �ּ��� �� �����ľߵǳ�

*/

















class Test
{
    int *data=nullptr;
public:
    Test(int* ptr)
    {
        data = ptr;
        printf("%p ����\n",data);
    }

    Test(const Test&)
    {
        printf("%p ����\n", data);
    }

    Test(Test&&)
    {
        printf("%p �̵�\n", data);
    }

    ~Test()
    {
        printf("%p �Ҹ�\n", data);
    }
};



void run()
{

}
/*

�ڵ� ��Ÿ��/���ٴٵ带 �ۼ��ϰ�, �װſ� ���缭 �����丵�� ��������� �ؾߵǰڴ�.

v1.0���� ���� �ڵ� ���ٴٵ峪 ��Ÿ���� Ȯ������ ���� ���¶� ���� ����������� �ִ�.

*/
/*

�̰� ��Ʈ������ ��ȯ/����Ҷ� \���� ���ڵ� ó���ϴ� ���� �ù�

���� �������� ����ġ�鼭 ����

���ʿ� ������ JSON�� �̽������� ���ڴ� ������ \�ڵ�� �ΰ��� ���ڰ� ���յ� ���´�.
���⿡ �ƹ��� ���۵� ���ϰ�, �׳� �ִ´�� �����ϰ� �������°� ���� ������ ����.



*/
/*
todo:
�����Ҷ� api����,Ʃ�丮��,���� �ۼ��ϱ�
��Ŀ���� ������Ű���� �ϴ� ���,�ذ��� �˾ƺ���
//MD, MDd�� ��Ÿ�� ���̺귯�� ����

�ƴ� ��
��Ʈ��忡 �����Ȱ� obj/arr�ƴϸ� ��������



�ƴ� �� ������ ��û�� �����Ϸ�

int�����ε� �����ߵǳ�

�ƴ� �̰� �켱���� �̰� �۾� ������ ����ؼ� ã�ƺ����� �ƴ�
en.cppreference.com/w/cpp/language/implicit_conversion
en.cppreference.com/w/cpp/language/overload_resolution



todo: ��� �����鿡�� ��� �����ѰŴ� �� �������� �ѹ������� �����ϱ�

�̵������ڴ� Root���ؼ� Ǯ���ٱ�?

�ϴ� ���� ���� const& &&�� �� ������, �� �ΰ��� �ϸ�, ���ʿ��� �����͸� �����ϸ�, �ٸ��ʿ��� ������ ���ٽ� ������ ���Ű����ϱ���



������Ʈ �����ΰ�: static_cast<long long>() �Ƚᵵ �ǵ��� �ϱ� << �ƴ� �̰� �Ͻ��� ����ȯ ������

*/

int main()
{

    run();
    //�ٽ� �����ϱ�

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


||GetNodeType()|
|-|-|
|����|����� Ÿ���� ��ȯ�Ѵ�.|
|Ư¡|BaseClass�� �Լ��� �״�� ����մϴ�.|
|��ȯ|Ÿ��:UglyJSONParser::NodeType<br>����� Ÿ��|

||GetName()|
|-|-|
|����|����� �̸��� const ������ ��ȯ�Ѵ�.|
|Ư¡|BaseClass�� �Լ��� �״�� ����մϴ�.|
|��ȯ|Ÿ��:std::string<br>����� �̸��� const ����|

||GetJsonTreeByString()|
|-|-|
|����|string GetJsonTreeByString() override|
|����|StringNode�� ������(���� strData�� Ī��)�� (")�� ���μ� ��ȯ�Ѵ�.|
|��ȯ|Ÿ��:std::string<br>(")�� ������ strData|

||AsString()<br>AsInt()<br>AsBool()<br>AsDouble()|
|-|-|
|����|const string& AsString() const override;<br>long long AsInt() const override;<br>bool AsBool() const override;<br>double AsDouble() const override;|
|<span style="color:red">����</span>|�� �Լ����� ArrayNode�� ���������� ȣ���ϸ� ��Ÿ�� ������ �߻��մϴ�.<br>����� ȣ���Ͻø� �ȵ˴ϴ�.|

||operator=()|
|-|-|
|�����ε� 1|void operator=(const string& strData) override|
|�����ε� 2|void operator=(const char* strData) override|
|�����ε� 3|void operator=(const long long intData) override|
|�����ε� 4|void operator=(const bool boolData) override|
|�����ε� 5|void operator=(const double doubleData) override|
|<span style="color:red">����</span>|�� �Լ����� ArrayNode�� ���������� ȣ���ϸ� ��Ÿ�� ������ �߻��մϴ�.<br>����� ȣ���Ͻø� �ȵ˴ϴ�.|

||operator\[\]()|
|-|-|
|�����ε� 1|BaseNode& operator\[\](const string& strKey) override;|
|����|�� �����ε�� const std::string& Ÿ���� ���ڿ��� �Է¹޾�, ��ġ�ϴ� �̸��� ���� ��带 childNodeVector���� ã�� ������ ��ȯ�մϴ�.|
|<span style="color:red">����</span>|�Է��� ���ڿ��� �̸����� ������ ��尡 childNodeVector�� ���ٸ� ��Ÿ�� ������ �߻��մϴ�.<br>�Է��� ���ڿ��� �ִ°� �´��� Ȯ���Ͻñ� �ٶ��ϴ�.|

||operator\[\]()|
|-|-|
|�����ε� 2|BaseNode& operator\[\](const size_t intKey) override;|
|<span style="color:red">����</span>|�� �����ε�� ȣ���ϸ� ��Ÿ�� ������ �߻��մϴ�.<br>����� ������ Ű�� �־�, �� �����ε带ȣ���Ͻø� �ȵ˴ϴ�.|

||GetChildNodeVector()|
|-|-|
|����|std::vector<BaseNode*>& GetChildNodeVector() override;|
|����|childNodeVector�� ������ ��ȯ�մϴ�.|
|��ȯ|Ÿ��:std::vector\<UglyJSONParser::BaseNode*\>&<br>childNodeVector�� ����|


||Clear()|
|-|-|
|����|void Clear() override;|
|����|�� �Լ��� ��������� ȣ���ϸ�, �ڽ��� �������� ��� �ڽĳ�带 �����մϴ�.|
|�۵�|�� �Լ��� ȣ��Ǹ�, childNodeVector�� ��ȸ�ϸ�, ���� object �Ǵ� arrayNode���, Clear()�Լ��� ���ȣ���ϰ�, �ƴ϶�� �����մϴ�. |
||�׸��� ������ ������ childNodeVector.clear()�� ȣ���Ͽ� ���͸� ���� �Լ��� �����մϴ�.|
|Ư¡|�Ҹ�ÿ� �ڵ����� ȣ���|

||DeleteChildNode()|
|-|-|
|�����ε� 1|void DeleteChildNode(const string& strKey) override;|
|����|�� �����ε�� const string& strKey Ÿ���� ���ڿ� Ű�� �Է¹޾�, ������ childNodeVector���� �ش� Ű�� ���� �̸��� ������ �ڽĳ�带 �����մϴ�.|
|<span style="color:red">����</span>|���� �Է� Ű�� �̸����� ������ ��尡 childNodeVector�� ���ٸ� ��Ÿ�� ������ �߻��մϴ�.<br>�ݵ�� Ű�� Ȯ���Ͽ� �ֽʽÿ�.|
|�Ű�����|Ÿ��:const std::string<br>������ ����� �̸�|

||DeleteChildNode()|
|-|-|
|�����ε� 2|void DeleteChildNode(size_t intKey) override;|
|<span style="color:red">����</span>|�� �����ε�� ȣ���ϸ� ��Ÿ�� ������ �߻��մϴ�.<br>����� ������ Ű�� �־�, �� �����ε带ȣ���Ͻø� �ȵ˴ϴ�.|

||CreateNewNode()|
|-|-|
|�����ε� 1|bool CreateNewNode(NodeType type, string strKey) override;|
|����|�� �����ε�� ����� Ÿ�԰� ���ڿ��� �� ����� �̸��� �Է¹޾�,���� childNodeVector�� ��ġ�� �̸��� �ִ��� �˻��մϴ�.|
||���ٸ�, NodeFactory�� Ÿ�԰� �̸��� �־ ��� ������ �õ��ϰ�, �����Ѵٸ� childNodeVector�� push�մϴ�|
|��ȯ|Ÿ��:bool<br>true : �ڽĳ�� ������ �����߽��ϴ�.<br>false : �ڽĳ�� ������ ������ �߻��߽��ϴ�|
|�Ű�����|Ÿ��:UglyJSONParser::NodeType, std::string<br>������ ����� Ÿ�԰� �̸�|

||CreateNewNode()|
|-|-|
|�����ε� 2|bool CreateNewNode(NodeType type) override;|
|<span style="color:red">����</span>|�� object�� std::stringŸ���� �̸����� ������ �ʿ��ϱ⿡, �� �����ε�� �׻� false�� ��ȯ�մϴ�.|
|��ȯ|Ÿ��:bool<br>false : �ڽĳ�� ������ ������ �߻��߽��ϴ�|
|�Ű�����|Ÿ��:UglyJSONParser::NodeType<br>������ ����� Ÿ��|

||GetChildNodeCount()|
|-|-|
|����|size_t GetChildNodeCount() const override;|
|����|childNodeVector.size() �� ����� ��ȯ�մϴ�.|
|��ȯ|Ÿ��:size_t<br>�ڽĳ���� ����|

||Contains()|
|-|-|
|����|bool Contains(const std::string& key) const override;|
|����|�Է����� ���� Ű�� ��ġ�ϴ� �̸��� ������ ��尡 childNodeVector�� �ִ��� �˻��ϰ� ����� ��ȯ�Ѵ�.|
|��ȯ|Ÿ��:bool<br>true:�ִ�<br>false:����|
|�Ű�����|const std::string&<br>�˻��� �̸�|


*/