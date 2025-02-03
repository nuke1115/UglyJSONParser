#include "..\JSONTreeBuilder.hpp"

UglyJSONParser::BaseNode* UglyJSONParser::JSONTreeBuilder::CreateFirstNode(const std::string& token)
{
    NodeType type = TypeUtils::GetNodeTypeOfToken(token);
    
    if (type == NodeType::Error)
    {
        return nullptr;
    }

    return _factory.CreateNode(type, _FirstNodeName);

}

void UglyJSONParser::JSONTreeBuilder::AssignValue(BaseNode& TargetNodeRef, const std::string& str)
{
    if (StringUtils::IsItDigit(str.front()) || StringUtils::IsItSign(str.front()))
    {
        if (StringUtils::Contains(str, TokenDecimalPoint) || StringUtils::Contains(str, _TokenExponentLower) || StringUtils::Contains(str, _TokenExponentUpper))
        {
            TargetNodeRef = static_cast<double>(std::stod(str));
        }
        else
        {
            TargetNodeRef = static_cast<long long>(std::stoll(str));
        }
    }
    else if (TypeUtils::IsItJsonBool(str))
    {
        TargetNodeRef = static_cast<bool>(TypeUtils::StrToBool(str));
    }
    else if (TypeUtils::IsItJsonString(str))
    {
        std::string tmp(str);
        
        if (tmp.front() == _TokenQuotationMark)
        {
            tmp.erase(0, 1);
        }

        if (tmp.back() == _TokenQuotationMark)
        {
            tmp.pop_back();
        }

        TargetNodeRef = tmp;
    }
}


bool UglyJSONParser::JSONTreeBuilder::BuildJSONTree(RootNode& rootNode, const std::list<std::string>& tokens)
{
    if (tokens.empty())
    {
        return false;
    }

    BaseNode* firstNodeTmpPtr = CreateFirstNode(tokens.front());

    if (firstNodeTmpPtr == nullptr || !rootNode.SetRoot(firstNodeTmpPtr) || !rootNode.SetType(firstNodeTmpPtr->GetNodeType()))
    {
        return false;
    }
    
    BaseNode* nowNode = &rootNode;

    std::stack<BaseNode*> indentationStack;

    for (auto iter = std::next(tokens.begin()); iter != tokens.end(); iter++)
    {
        if (!indentationStack.empty() && StringUtils::IsItClosingToken(iter->front()))
        {
            nowNode = indentationStack.top();
            indentationStack.pop();
        }
        else if (nowNode->GetNodeType() == NodeType::Array)
        {
            nowNode->CreateNewNode(TypeUtils::GetNodeTypeOfToken(*iter));

            BaseNode* tmp = nowNode->GetChildNodeVector().back();

            if (StringUtils::IsItOpeningToken(iter->front()))
            {
                indentationStack.push(nowNode);
                nowNode = tmp;
            }
            else
            {
                AssignValue(*tmp, *iter);
            }
        }
        else if (nowNode->GetNodeType() == NodeType::Object && iter->front() == _TokenColon)
        {
            auto right = std::next(iter), left = std::prev(iter);



            nowNode->CreateNewNode(TypeUtils::GetNodeTypeOfToken(*right), *left);

            BaseNode* tmp = nowNode->GetChildNodeVector().back();//�� �����ϰ� �˻��ϱ�.
            
            if (StringUtils::IsItOpeningToken(right->front()))
            {
                indentationStack.push(nowNode);
                nowNode = tmp;
            }
            else
            {
                AssignValue(*tmp, *right);
            }

            iter++;
        }

    }
    return true;
}

/*
���� ���:

��������: ������ tokens�� tokenizer���� ��ūȭ�� ������ �Ϸ�� ���ڿ��̴�. (object������ ���� ������������ �ߺ��Ǵ� stringŰ�� node�������� �ɷ���)

�ʱ⼳��:
ù��° ��ū���� ��带 �����, rootNode�� entry point�� �����Ѵ�.

�׸��� ��Ʈ��带 ����Ű�� BaseNode* nowNode�� �����, ��Ʈ����� �ּҸ� �Ҵ��Ѵ�.

�׸��� �� ��尡 arr/obj��� indentationStack�� nowNode�� push�Ѵ�.


����:
iter = tokens�� ���ͷ������� �ι�°��
iter != tokens.end()�϶����� iter++�� �ϸ� �ݺ�

} => stack.top�� nowNode�� �����ϰ�, stack.pop
] => stack.top�� nowNode�� �����ϰ�, stack.pop
, => (�����ϱ�)
: => obj�϶��� => ������ ��ū�� ������ū�̶�� ������ū���� �̸� �����ͼ� ������ū�϶��� ���� ����.
                    �ƴ϶�� ������ū���� �̸� �����ͼ� ������ ��ū Ÿ�Կ� �˸´� ��� �����ؼ� nowNode�� createChild ����

arr�϶��� �׳� �а� �߰��ϱ�.
�ٵ� ���� ��ū ������ �ؿ� ���� ��ū �������� �������� �ϰ�

������ū�϶�:
��ū�� �´� Ÿ������ nowNode�� CreateChildNode�ϰ�, �� �����͸� stack�� push�ϰ� nowNode�� �� �����ͷ� ����

������ū�� �ƴϸ�:
=>


�� ��ū��� �ؾߵɰŰ�����


*/