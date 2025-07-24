#include "../../Include/UglyJSONParser/JSONTree/JSONTreeBuilder.hpp"

void AssignExponentValueToNumberNode(UglyJSONParser::BaseNode& TargetNodeRef, size_t index,const std::string& str)
{
    if (str[index + 1] == UglyJSONParser::Tokens::TokenMinus)
    {
        TargetNodeRef = std::stod(str);
    }
    else
    {
        TargetNodeRef = static_cast<long long>(std::stod(str));
    }
}

void UglyJSONParser::JSONTreeBuilder::AssignValue(BaseNode& TargetNodeRef, const std::string& str)
{
    if ((StringUtils::IsItDigit(str.front()) || StringUtils::IsItSign(str.front())) && StringUtils::IsItDigit(str.back()))
    {
        size_t expLower = str.find(Tokens::TokenExponentLower), expUpper = str.find(Tokens::TokenExponentUpper);
        if (StringUtils::Contains(str, Tokens::TokenDecimalPoint))
        {
            TargetNodeRef = std::stod(str);
        }
        else if (expLower != std::string::npos)
        {
            AssignExponentValueToNumberNode(TargetNodeRef, expLower, str);
        }
        else if (expUpper != std::string::npos)
        {
            AssignExponentValueToNumberNode(TargetNodeRef, expUpper, str);
        }
        else
        {
            TargetNodeRef = std::stoll(str);
        }
    }
    else if (TypeUtils::IsItJsonBool(str))
    {
        TargetNodeRef = TypeUtils::ConvertStringToBool(str);
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

    NodeType type = TypeUtils::GetNodeTypeOfToken(tokens.front());

    if (type == NodeType::Error)
    {
        return false;
    }

    auto createResult = rootNode.CreateRootNode(type);

    if (createResult.HasValue() && createResult.GetValue() == false)
    {
        return false;
    }
    
    BaseNode* nowNode = &rootNode;

    std::stack<BaseNode*> indentationStack;


    if (!(nowNode->GetNodeType() == NodeType::Array || nowNode->GetNodeType() == NodeType::Object))
    {
        AssignValue(*nowNode, tokens.front());
    }

    for (auto iter = std::next(tokens.begin()); iter != tokens.end(); iter++)//여기서 첫번째값은 넣지를 못하네
    {
        if (!indentationStack.empty() && StringUtils::IsItClosingToken(iter->front()))
        {
            nowNode = indentationStack.top();
            indentationStack.pop();
        }
        else if (nowNode->GetNodeType() == NodeType::Array && (StringUtils::IsItOpeningToken(iter->front()) || TypeUtils::IsItSingleJsonValue(*iter)))
        {
            auto createResult = nowNode->CreateNewNode(TypeUtils::GetNodeTypeOfToken(*iter));
            if (createResult.HasValue() && createResult.GetValue() == false)
            {
                return false;
            }

            auto getChildNodeVectorResult = nowNode->GetChildNodeVector();

            if (getChildNodeVectorResult.HasValue() == false)
            {
                return false;
            }

            BaseNode* tmp = getChildNodeVectorResult.GetValueRef().back();

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
            auto createResult = nowNode->CreateNewNode(TypeUtils::GetNodeTypeOfToken(*right), *left);
            if (createResult.HasValue() && createResult.GetValue() == false)
            {
                return false;
            }

            auto getChildNodeVectorResult = nowNode->GetChildNodeVector();

            if (getChildNodeVectorResult.HasValue() == false)
            {
                return false;
            }

            BaseNode* tmp = getChildNodeVectorResult.GetValueRef().back();
            

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