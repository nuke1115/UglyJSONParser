#ifndef UGLY_JSON_PARSER_RESULT_UTILS_HEADER
#define UGLY_JSON_PARSER_RESULT_UTILS_HEADER

#include <format>
#include <string>
#include <utility>
#include <stdint.h>
#include "../EnumerationInclude.hpp"
#include "../Utils/TypeUtils.hpp"

namespace UglyJSONParser
{
    namespace ResultUtils
    {
        constexpr inline uint32_t MakeErrorBitmask(NodeType nodeType, DataTypes dataType, AccessTypes accessType, OperationTypes operationType)
        {
            return  static_cast<uint32_t>(nodeType)         |
                    static_cast<uint32_t>(dataType)         |
                    static_cast<uint32_t>(accessType)       |
                    static_cast<uint32_t>(operationType)    ;
        }

        std::string DecodeErrorBitMask(uint32_t errorBitMask);
    }
}

#endif // !UGLY_JSON_PARSER_RESULT_UTILS_HEADER
