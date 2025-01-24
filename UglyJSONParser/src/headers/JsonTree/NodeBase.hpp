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

        //array�� object�� ��� ���Ҹ� �����Ѵ�.
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
�ּ���:

Clear():
array/obj�϶�.
���Ҹ� �����´�.
�˻��Ѵ�.
array/objŸ���̸� �� ���Ҹ� ������� �ٽ� �Ѵ�.

�ƴҶ�:
�� ���Ҹ� �����Ѵ�.
----------

���� ����:
SingleData
Array
Object

---------

NodeFactory

Ÿ�԰� ���������� string�� �޾Ƽ� ��带 ����� ������ ��ȯ

--------
nulló���� ��� �ؾߵɱ�?



1:singleData�� unknown ���ڿ��̳� null�� �����ͷ� �ִ´�.
2:�����Ѵ�.
3:singleData�� array,object�� ��������� ������, BaseNode�� ��ӹ޴� ���ο� ��带 ����, ó�� �����ϴ� �Լ��� ���� Ÿ���÷��׸� �����ؼ� Ÿ���� �����ϴ� ������� �Ѵ�.

---------

����Ҹ��ڰ� ������ �θ��� �����ͷ� �ڽĳ�� ���������� �ڽĳ�� �Ҹ��� ȣ�� �ȵ�
�̰Ŷ����� �ڽĳ���� �Ҹ��ڰ� ���������� ȣ���� �ȵǼ�, ���������� �޸𸮻� �ν��Ͻ� �Ϻΰ� �����־���.
�θ��忡 ����Ҹ��� ����������ν� �ذ�
�ð�=>1�ð� 30�� ����

*/