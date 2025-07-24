#ifndef UGLY_JSON_PARSER_RESULT_UTILS_HEADER
#define UGLY_JSON_PARSER_RESULT_UTILS_HEADER

#include <format>
#include <string>
#include <utility>
#include <stdint.h>
#include "../EnumerationInclude.hpp"
#include "../Utils/TypeUtils.hpp"
#include "../Constants/ResultEnumConstants.hpp"

namespace UglyJSONParser
{
    namespace ResultUtils
    {
        constexpr inline ErrorBitmask MakeErrorBitmask(NodeType nodeType, DataTypes dataType, AccessTypes accessType, OperationTypes operationType, ErrorDescriptions errorDescriptions)
        {
            return      static_cast<ErrorBitmask>(nodeType)         |
                        static_cast<ErrorBitmask>(dataType)         |
                        static_cast<ErrorBitmask>(accessType)       |
                        static_cast<ErrorBitmask>(operationType)    |
                        static_cast<ErrorBitmask>(errorDescriptions);
        }

        std::string DecodeErrorBitMask(ErrorBitmask errorBitMask);
    }
}

#endif // !UGLY_JSON_PARSER_RESULT_UTILS_HEADER
