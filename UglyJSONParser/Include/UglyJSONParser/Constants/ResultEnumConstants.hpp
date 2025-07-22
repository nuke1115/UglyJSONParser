#ifndef UGLY_JSON_PARSER_RESULT_ENUM_CONSTANTS_HEADER
#define UGLY_JSON_PARSER_RESULT_ENUM_CONSTANTS_HEADER

#include "../EnumerationInclude.hpp"

namespace UglyJSONParser
{
    constexpr NodeType nodeTypeFilter = NodeType::FALSE_BIT | NodeType::Null | NodeType::Object | NodeType::Array | NodeType::String | NodeType::Number | NodeType::Bool | NodeType::Root | NodeType::Error;
    constexpr DataTypes dataTypeFilter = DataTypes::FALSE_BIT | DataTypes::BOOL | DataTypes::INT | DataTypes::DOUBLE | DataTypes::STRING | DataTypes::NODE | DataTypes::NODE_VECTOR | DataTypes::NODE_EXISTENCE | DataTypes::NODE_COUNT;
    constexpr AccessTypes accessTypeFilter = AccessTypes::FALSE_BIT | AccessTypes::BY_INT | AccessTypes::BY_STRING;
    constexpr OperationTypes operationTypeFilter = OperationTypes::FALSE_BIT | OperationTypes::INSERT | OperationTypes::GET | OperationTypes::DELETE | OperationTypes::CREATE;
    constexpr uint32_t noErrorFilter = static_cast<uint32_t>(NodeType::FALSE_BIT) | static_cast<uint32_t>(DataTypes::FALSE_BIT) | static_cast<uint32_t>(AccessTypes::FALSE_BIT) | static_cast<uint32_t>(OperationTypes::FALSE_BIT);
}


#endif // !UGLY_JSON_PARSER_RESULT_ENUM_CONSTANTS_HEADER
