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
        /// <summary>
        /// Converts input string to bool data
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        inline bool StrToBool(const std::string& data)
        {
            return !data.compare(Tokens::TokenTrue);
        }

        /// <summary>
        /// Converts input bool data to string
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        std::string BoolToString(bool data);

        /// <summary>
        /// Checking input is json type bool
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        inline bool IsItJsonBool(const std::string& key)
        {
            return !key.compare(Tokens::TokenTrue) || !key.compare(Tokens::TokenFalse);
        }

        /// <summary>
        /// Checking input is json type string
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        inline bool IsItJsonString(const std::string& key)
        {
            return (key.front() == Tokens::TokenQuotationMark && key.back() == Tokens::TokenQuotationMark);
        }

        /// <summary>
        /// Checking input is single json value(bool,null,string,number)
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        inline bool IsItSingleJsonValue(const std::string& key)
        {
            return (
                IsItJsonString(key) ||
                ((StringUtils::IsItDigit(key.front()) || StringUtils::IsItSign(key.front())) && StringUtils::IsItDigit(key.back())) ||
                IsItJsonBool(key) ||
                StringUtils::CompareString(key, Tokens::TokenNull, 0)
                );
        }

        /// <summary>
        /// Returns node type of token
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        NodeType GetNodeTypeOfToken(const std::string& token);
    }
}

#endif // !UGLY_JSON_PARSER_TYPE_UTILS_HEADER