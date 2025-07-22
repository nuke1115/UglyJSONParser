#include "../../Include/UglyJSONParser/Utils/ResultUtils.hpp"

std::string UglyJSONParser::ResultUtils::DecodeErrorBitMask(ErrorBitmask errorBitMask)
{
    
    if (errorBitMask == noErrorFilter)
    {
        return std::string("no error");
    }

    if (static_cast<uint32_t>(AccessTypes::FALSE_BIT) & static_cast<uint32_t>(errorBitMask))//일반 접근
    {
        return std::move(std::format(
            "tried to {} {} in {} node",
            TypeUtils::GetOperationTypeName(static_cast<OperationTypes>(errorBitMask) & operationTypeFilter),
            TypeUtils::GetDataTypeName(static_cast<DataTypes>(errorBitMask) & dataTypeFilter),
            TypeUtils::GetNodeTypeName(static_cast<NodeType>(errorBitMask) & nodeTypeFilter)
        ));
    }
    else//자식노드 접근
    {
        return std::move(std::format(
            "tried to {} {} by {} in {} node",
            TypeUtils::GetOperationTypeName(static_cast<OperationTypes>(errorBitMask) & operationTypeFilter),
            TypeUtils::GetDataTypeName(static_cast<DataTypes>(errorBitMask) & dataTypeFilter),
            TypeUtils::GetAccessTypeName(static_cast<AccessTypes>(errorBitMask) & accessTypeFilter),
            TypeUtils::GetNodeTypeName(static_cast<NodeType>(errorBitMask) & nodeTypeFilter)
        ));
    }
}