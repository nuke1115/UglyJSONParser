#ifndef UGLY_JSON_PARSER_STRING_UTILS_HEADER
#define UGLY_JSON_PARSER_STRING_UTILS_HEADER

#include <string>
#include "../Tokenizer/Tokens.hpp"

namespace UglyJSONParser
{
    namespace StringUtils
    {
        /// <summary>
        /// Compare target with key string. targetStringStartIndex is the start index that you want to start comparing in target string
        /// </summary>
        /// <param name="target"></param>
        /// <param name="key"></param>
        /// <param name="targetStringStartIndex"></param>
        /// <returns></returns>
        bool CompareString(const std::string& target, const std::string& key, size_t targetStringStartIndex);

        /// <summary>
        /// Checking input token is in range of digits (0~9)
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        inline bool IsItDigit(const char token)
        {
            return Tokens::NumRangeStart <= token && Tokens::NumRangeEnd >= token;
        }

        /// <summary>
        /// Checking whether input token is { or [
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        inline bool IsItOpeningToken(const char token)
        {
            return token == Tokens::TokenObjectStart || token == Tokens::TokenArrayStart;
        }

        /// <summary>
        /// Checking whether input token is } or ]
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        inline bool IsItClosingToken(const char token)
        {
            return token == Tokens::TokenObjectEnd || token == Tokens::TokenArrayEnd;
        }

        /// <summary>
        /// Checking whether input token is + or -
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        inline bool IsItSign(const char token)
        {
            return token == Tokens::TokenPlus || token == Tokens::TokenMinus;
        }

        /// <summary>
        /// Checking whether input source contains char key
        /// </summary>
        /// <param name="token"></param>
        /// <returns></returns>
        inline bool Contains(const std::string& source, const char key)
        {
            return source.find(key) != std::string::npos;
        }
    }
}

#endif // !UGLY_JSON_PARSER_STRING_UTILS_HEADER