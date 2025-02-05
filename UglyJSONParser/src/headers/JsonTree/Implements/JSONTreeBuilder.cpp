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
        if (StringUtils::Contains(str, Tokens::TokenDecimalPoint) || StringUtils::Contains(str, Tokens::TokenExponentLower) || StringUtils::Contains(str, Tokens::TokenExponentUpper))
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
        
        if (tmp.front() == Tokens::TokenQuotationMark)
        {
            tmp.erase(0, 1);
        }

        if (tmp.back() == Tokens::TokenQuotationMark)
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
        else if (nowNode->GetNodeType() == NodeType::Array && (StringUtils::IsItOpeningToken(iter->front()) || TypeUtils::IsItSingleJsonValue(*iter)))
        {
            if (nowNode->CreateNewNode(TypeUtils::GetNodeTypeOfToken(*iter)) == false)
            {
                return false;
            }

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
        else if (nowNode->GetNodeType() == NodeType::Object && iter->front() == Tokens::TokenColon)
        {
            auto right = std::next(iter), left = std::prev(iter);

            if (nowNode->CreateNewNode(TypeUtils::GetNodeTypeOfToken(*right), *left) == false)
            {
                return false;
            }

            BaseNode* tmp = nowNode->GetChildNodeVector().back();
            
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