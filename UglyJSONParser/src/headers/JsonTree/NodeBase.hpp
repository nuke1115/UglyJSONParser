#ifndef UGLY_JSON_PARSER_NODE_BASE_HEADER
#define UGLY_JSON_PARSER_NODE_BASE_HEADER

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <stdlib.h>
#include ".\NodeTypes.hpp"



namespace UglyJSONParser
{
    class BaseNode
    {
    protected:
        using string = std::string;
        string _nodeName;
        NodeType _nodeType;

    public:
        BaseNode(string name, NodeType nodeType);
        BaseNode(const BaseNode&) = delete;
        BaseNode(BaseNode&&) = delete;


        inline NodeType GetNodeType() const
        {
            return _nodeType;
        }

        inline const string& GetName() const
        {
            return _nodeName;
        }


        virtual string GetJsonTreeByString() = 0;


        virtual const std::string& AsString() const = 0;
        virtual long long AsInt() const = 0;
        virtual bool AsBool() const = 0;
        virtual double AsDouble() const = 0;

        virtual BaseNode& operator[](const string& strKey) = 0;
        virtual BaseNode& operator[](const int intKey) = 0;

        virtual void operator=(const string& strData) = 0;
        virtual void operator=(const char* strData) = 0;
        virtual void operator=(const long long intData) = 0;
        virtual void operator=(const bool boolData) = 0;
        virtual void operator=(const double doubleData) = 0;


        virtual std::vector<BaseNode*>& GetChildNodeVector() = 0;

        //array나 object의 모든 원소를 삭제한다.
        virtual void Clear() = 0;

        virtual void DeleteChildNode(const string& strKey) = 0;
        virtual void DeleteChildNode(int intKey) = 0;

        virtual void CreateNewNode(NodeType type, string strKey) = 0;
        virtual void CreateNewNode(NodeType type) = 0;

        virtual ~BaseNode();
    };
}


#endif // UGLY_JSON_PARSER_NODE_BASE_HEADER

/*
주석들:

Clear():
array/obj일때.
원소를 꺼내온다.
검사한다.
array/obj타입이면 그 원소를 대상으로 다시 한다.

아닐때:
그 원소를 삭제한다.
----------

만들 노드들:
SingleData
Array
Object

---------

NodeFactory

타입과 선택적으로 string을 받아서 노드를 만들어 포인터 반환

--------
null처리를 어떻게 해야될까?



1:singleData에 unknown 문자열이나 null을 데이터로 넣는다.
2:삭제한다.
3:singleData와 array,object를 멤버변수로 가지고, BaseNode를 상속받는 새로운 노드를 만들어서, 처음 실행하는 함수에 따라서 타입플레그를 설정해서 타입을 고정하는 방식으로 한다.

---------

가상소멸자가 없으면 부모노드 포인터로 자식노드 접근했을때 자식노드 소멸자 호출 안됨
이거때문에 자식노드의 소멸자가 정상적으로 호출이 안되서, 지속적으로 메모리상에 인스턴스 일부가 남아있었다.
부모노드에 가상소멸자 만들어줌으로써 해결
시간=>1시간 30분 ㅅㅂ

*/