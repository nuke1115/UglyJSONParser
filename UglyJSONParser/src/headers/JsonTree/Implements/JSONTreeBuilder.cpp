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

            BaseNode* tmp = nowNode->GetChildNodeVector().back();//더 안전하게 검사하기.
            
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
빌드 방법:

전제조건: 들어오는 tokens는 tokenizer에서 토큰화와 검증이 완료된 문자열이다. (object에서의 같은 스코프에서의 중복되는 string키는 node단위에서 걸러짐)

초기설정:
첫번째 토큰으로 노드를 만들어, rootNode에 entry point로 설정한다.

그리고 루트노드를 가리키는 BaseNode* nowNode를 만들고, 루트노드의 주소를 할당한다.

그리고 그 노드가 arr/obj라면 indentationStack에 nowNode를 push한다.


루프:
iter = tokens의 이터레이터의 두번째값
iter != tokens.end()일때동안 iter++를 하며 반복

} => stack.top을 nowNode로 설정하고, stack.pop
] => stack.top을 nowNode로 설정하고, stack.pop
, => (무시하기)
: => obj일때만 => 오른쪽 토큰이 여는토큰이라면 왼쪽토큰에서 이름 가져와서 여는토큰일때의 로직 실행.
                    아니라면 왼쪽토큰에서 이름 가져와서 오른쪽 토큰 타입에 알맞는 노드 생성해서 nowNode에 createChild 실행

arr일때는 그냥 읽고 추가하기.
근데 여는 토큰 나오면 밑에 여는 토큰 나왔을때 로직으로 하고

여는토큰일때:
토큰에 맞는 타입으로 nowNode에 CreateChildNode하고, 그 포인터를 stack에 push하고 nowNode를 그 포인터로 설정

여는토큰이 아니면:
=>


이 토큰들로 해야될거같은데


*/