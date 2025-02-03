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


        inline NodeType GetNodeType() const //戚暗 砧鯵 陥 virtual 稽 郊蚊醤吉陥 繕然陥 せせせせせせせせせせせせせせせせせせせせせせせ
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

        //array蟹 object税 乞窮 据社研 肢薦廃陥.
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
爽汐級:

Clear():
array/obj析凶.
据社研 襖鎧紳陥.
伊紫廃陥.
array/obj展脊戚檎 益 据社研 企雌生稽 陥獣 廃陥.

焼諌凶:
益 据社研 肢薦廃陥.
----------

幻級 葛球級:
SingleData
Array
Object

---------

NodeFactory

展脊引 識澱旋生稽 string聖 閤焼辞 葛球研 幻級嬢 匂昔斗 鋼発

--------
null坦軒研 嬢胸惟 背醤吃猿?



1:singleData拭 unknown 庚切伸戚蟹 null聖 汽戚斗稽 隔澗陥.
2:肢薦廃陥.
3:singleData人 array,object研 呉獄痕呪稽 亜走壱, BaseNode研 雌紗閤澗 歯稽錘 葛球研 幻級嬢辞, 坦製 叔楳馬澗 敗呪拭 魚虞辞 展脊巴傾益研 竺舛背辞 展脊聖 壱舛馬澗 号縦生稽 廃陥.

---------

亜雌社瑚切亜 蒸生檎 採乞葛球 匂昔斗稽 切縦葛球 羨悦梅聖凶 切縦葛球 社瑚切 硲窒 照喫
戚暗凶庚拭 切縦葛球税 社瑚切亜 舛雌旋生稽 硲窒戚 照鞠辞, 走紗旋生稽 五乞軒雌拭 昔什渡什 析採亜 害焼赤醸陥.
採乞葛球拭 亜雌社瑚切 幻級嬢捜生稽潤 背衣
獣娃=>1獣娃 30歳 さげ

*/