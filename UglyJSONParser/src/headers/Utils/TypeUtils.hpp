#ifndef UGLY_JSON_PARSER_TYPE_UTILS_HEADER
#define UGLY_JSON_PARSER_TYPE_UTILS_HEADER

#include <string>
#include "..\JsonTree\NodeTypes.hpp"
#include ".\StringUtils.hpp"
#include "..\Tokenizer\Tokens.hpp"


namespace UglyJSONParser
{
    namespace TypeUtils
    {
        inline bool StrToBool(const std::string& data)
        {
            return !data.compare(Tokens::TokenTrue);
        }

        std::string BoolToString(bool data);

        inline bool IsItJsonBool(const std::string& key)
        {
            return !key.compare(Tokens::TokenTrue) || !key.compare(Tokens::TokenFalse);
        }

        inline bool IsItJsonString(const std::string& key)
        {
            return (key.front() == Tokens::TokenQuotationMark && key.back() == Tokens::TokenQuotationMark);
        }

        /// <summary>
        /// only checks boolean,number,null. not array, object
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        inline bool IsItSingleJsonValue(const std::string& key)
        {
            return (
                IsItJsonString(key) ||
                (StringUtils::IsItDigit(key.front()) || StringUtils::IsItSign(key.front())) ||
                IsItJsonBool(key) ||
                StringUtils::CompareString(key, Tokens::TokenNull, 0)
                );
        }

        NodeType GetNodeTypeOfToken(const std::string& token);
    }
}

#endif // !UGLY_JSON_PARSER_TYPE_UTILS_HEADER