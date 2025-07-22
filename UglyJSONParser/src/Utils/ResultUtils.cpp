#include "../../Include/UglyJSONParser/Utils/ResultUtils.hpp"

std::string UglyJSONParser::ResultUtils::DecodeErrorBitMask(uint32_t errorBitMask)
{
    constexpr NodeType nodeTypeFilter = NodeType::FALSE_BIT | NodeType::Null | NodeType::Object | NodeType::Array | NodeType::String | NodeType::Number | NodeType::Bool | NodeType::Root | NodeType::Error;
    constexpr DataTypes dataTypeFilter = DataTypes::FALSE_BIT | DataTypes::BOOL | DataTypes::INT | DataTypes::DOUBLE | DataTypes::STRING | DataTypes::NODE | DataTypes::NODE_VECTOR | DataTypes::NODE_EXISTENCE | DataTypes::NODE_COUNT;
    constexpr AccessTypes accessTypeFilter = AccessTypes::FALSE_BIT | AccessTypes::BY_INT | AccessTypes::BY_STRING;
    constexpr OperationTypes operationTypeFilter = OperationTypes::FALSE_BIT | OperationTypes::INSERT | OperationTypes::GET | OperationTypes::DELETE | OperationTypes::CREATE;

    if (static_cast<uint32_t>(AccessTypes::FALSE_BIT) & errorBitMask)//일반 접근
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