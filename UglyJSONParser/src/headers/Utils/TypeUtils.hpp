#ifndef UGLY_JSON_PARSER_TYPE_UTILS_HEADER

#include <string>
#include "..\JsonTree\NodeTypes.hpp"
#include ".\StringUtils.hpp"


namespace UglyJSONParser
{
    namespace TypeUtils
    {
        bool StrToBool(const std::string& data);

        std::string BoolToString(bool data);

        bool IsItJsonString(const std::string& key);

        /// <summary>
        /// only checks boolean,number,null. not array, object
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        bool IsItJsonValue(const std::string& key);
        
        bool IsItJsonBool(const std::string& key);

        NodeType GetNodeTypeOfToken(const std::string& token);
    }
}

#endif // !UGLY_JSON_PARSER_TYPE_UTILS_HEADER
