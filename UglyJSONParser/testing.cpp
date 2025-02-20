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
#include <SFML/Graphics.hpp>


/*
버그수정 및 기능 추가 기록

1:JSONTreeBuilder에 첫번째 값 추가 안하는 버그
에러 케이스
1:const char*를 string이 아닌bool로 인식했다
2:long long, double, bool이 있을때, int데이터를 주면, 저거 3개에 다 걸린다

*/





/*
아니 주석도 다 뜯어고쳐야되네

*/

















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



void run()
{

}
/*

코딩 스타일/스텐다드를 작성하고, 그거에 맞춰서 리팩토링을 대대적으로 해야되겠다.

v1.0에는 아직 코딩 스텐다드나 스타일이 확립되지 않은 상태라서 조금 어지러울수도 있다.

*/
/*

이거 스트링노드로 변환/출력할때 \붙은 문자들 처리하는 로직 시바

다음 버전에서 뜯어고치면서 하자

에초에 들어오는 JSON의 이스케이프 문자는 무조건 \코드로 두가지 문자가 조합된 형태다.
여기에 아무런 조작도 안하고, 그냥 있는대로 저장하고 내보내는건 딱히 문제가 없다.



*/
/*
todo:
배포할때 api문서,튜토리얼,문서 작성하기
링커오류 안일으키도록 하는 방법,해결방법 알아보기
//MD, MDd로 런타임 라이브러리 설정

아니 썅
루트노드에 설정된게 obj/arr아니면 오류나네



아니 썅 개같은 멍청할 컴파일러

int오버로드 만들어야되네

아니 이거 우선순위 이거 작업 끝나면 억울해서 찾아봐야지 아니
en.cppreference.com/w/cpp/language/implicit_conversion
en.cppreference.com/w/cpp/language/overload_resolution



todo: 노드 문서들에서 사용 금지한거는 다 빼버리고 한문장으로 압축하기

이동연산자는 Root한해서 풀어줄까?

일단 지금 내가 const& &&둘 다 막은게, 저 두개를 하면, 한쪽에서 데이터를 삭제하면, 다른쪽에서 데이터 접근시 오류가 날거같으니까지



업데이트 예정인거: static_cast<long long>() 안써도 되도록 하기 << 아니 이거 암시적 형변환 개새야

*/

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


||GetNodeType()|
|-|-|
|설명|노드의 타입을 반환한다.|
|특징|BaseClass의 함수를 그대로 사용합니다.|
|반환|타입:UglyJSONParser::NodeType<br>노드의 타입|

||GetName()|
|-|-|
|설명|노드의 이름을 const 참조로 반환한다.|
|특징|BaseClass의 함수를 그대로 사용합니다.|
|반환|타입:std::string<br>노드의 이름의 const 참조|

||GetJsonTreeByString()|
|-|-|
|정의|string GetJsonTreeByString() override|
|설명|StringNode의 데이터(이하 strData로 칭함)를 (")로 감싸서 반환한다.|
|반환|타입:std::string<br>(")로 감싸진 strData|

||AsString()<br>AsInt()<br>AsBool()<br>AsDouble()|
|-|-|
|정의|const string& AsString() const override;<br>long long AsInt() const override;<br>bool AsBool() const override;<br>double AsDouble() const override;|
|<span style="color:red">주의</span>|이 함수들은 ArrayNode와 마찬가지로 호출하면 런타임 에러가 발생합니다.<br>절대로 호출하시면 안됩니다.|

||operator=()|
|-|-|
|오버로드 1|void operator=(const string& strData) override|
|오버로드 2|void operator=(const char* strData) override|
|오버로드 3|void operator=(const long long intData) override|
|오버로드 4|void operator=(const bool boolData) override|
|오버로드 5|void operator=(const double doubleData) override|
|<span style="color:red">주의</span>|이 함수들은 ArrayNode와 마찬가지로 호출하면 런타임 에러가 발생합니다.<br>절대로 호출하시면 안됩니다.|

||operator\[\]()|
|-|-|
|오버로드 1|BaseNode& operator\[\](const string& strKey) override;|
|설명|이 오버로드는 const std::string& 타입의 문자열을 입력받아, 일치하는 이름을 가진 노드를 childNodeVector에서 찾아 참조를 반환합니다.|
|<span style="color:red">주의</span>|입력한 문자열을 이름으로 가지는 노드가 childNodeVector에 없다면 런타임 에러가 발생합니다.<br>입력할 문자열이 있는게 맞는지 확인하시기 바랍니다.|

||operator\[\]()|
|-|-|
|오버로드 2|BaseNode& operator\[\](const size_t intKey) override;|
|<span style="color:red">주의</span>|이 오버로드는 호출하면 런타임 에러가 발생합니다.<br>절대로 정수를 키로 넣어, 이 오버로드를호출하시면 안됩니다.|

||GetChildNodeVector()|
|-|-|
|정의|std::vector<BaseNode*>& GetChildNodeVector() override;|
|설명|childNodeVector의 참조를 반환합니다.|
|반환|타입:std::vector\<UglyJSONParser::BaseNode*\>&<br>childNodeVector의 참조|


||Clear()|
|-|-|
|정의|void Clear() override;|
|설명|이 함수를 재귀적으로 호출하며, 자신을 기준으로 모든 자식노드를 삭제합니다.|
|작동|이 함수가 호출되면, childNodeVector를 순회하며, 만약 object 또는 arrayNode라면, Clear()함수를 재귀호출하고, 아니라면 삭제합니다. |
||그리고 루프가 끝나면 childNodeVector.clear()를 호출하여 백터를 비우고 함수를 종료합니다.|
|특징|소멸시에 자동으로 호출됨|

||DeleteChildNode()|
|-|-|
|오버로드 1|void DeleteChildNode(const string& strKey) override;|
|설명|이 오버로드는 const string& strKey 타입의 문자열 키를 입력받아, 내부의 childNodeVector에서 해당 키와 같은 이름을 가지는 자식노드를 삭제합니다.|
|<span style="color:red">주의</span>|만약 입력 키를 이름으로 가지는 노드가 childNodeVector에 없다면 런타임 오류가 발생합니다.<br>반드시 키를 확인하여 주십시오.|
|매개변수|타입:const std::string<br>삭제할 노드의 이름|

||DeleteChildNode()|
|-|-|
|오버로드 2|void DeleteChildNode(size_t intKey) override;|
|<span style="color:red">주의</span>|이 오버로드는 호출하면 런타임 에러가 발생합니다.<br>절대로 정수를 키로 넣어, 이 오버로드를호출하시면 안됩니다.|

||CreateNewNode()|
|-|-|
|오버로드 1|bool CreateNewNode(NodeType type, string strKey) override;|
|설명|이 오버로드는 노드의 타입과 문자열로 된 노드의 이름을 입력받아,먼저 childNodeVector에 겹치는 이름이 있는지 검사합니다.|
||없다면, NodeFactory에 타입과 이름을 넣어서 노드 생성을 시도하고, 성공한다면 childNodeVector에 push합니다|
|반환|타입:bool<br>true : 자식노드 생성에 성공했습니다.<br>false : 자식노드 생성에 문제가 발생했습니다|
|매개변수|타입:UglyJSONParser::NodeType, std::string<br>생성할 노드의 타입과 이름|

||CreateNewNode()|
|-|-|
|오버로드 2|bool CreateNewNode(NodeType type) override;|
|<span style="color:red">주의</span>|이 object는 std::string타입의 이름까지 생성에 필요하기에, 이 오버로드는 항상 false만 반환합니다.|
|반환|타입:bool<br>false : 자식노드 생성에 문제가 발생했습니다|
|매개변수|타입:UglyJSONParser::NodeType<br>생성할 노드의 타입|

||GetChildNodeCount()|
|-|-|
|정의|size_t GetChildNodeCount() const override;|
|설명|childNodeVector.size() 의 결과를 반환합니다.|
|반환|타입:size_t<br>자식노드의 갯수|

||Contains()|
|-|-|
|정의|bool Contains(const std::string& key) const override;|
|설명|입력으로 받은 키와 일치하는 이름을 가지는 노드가 childNodeVector에 있는지 검사하고 결과를 반환한다.|
|반환|타입:bool<br>true:있다<br>false:없다|
|매개변수|const std::string&<br>검사할 이름|


*/