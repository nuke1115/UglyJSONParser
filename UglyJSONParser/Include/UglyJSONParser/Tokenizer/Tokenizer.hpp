#ifndef UGLY_JSON_PARSER_TOKENIZER_HEADER
#define UGLY_JSON_PARSER_TOKENIZER_HEADER

#include <string>
#include <list>
#include <utility>
#include <iterator>
#include <stack>
#include <sstream>
#include "../Utils/StringUtils.hpp"
#include "../Utils/TypeUtils.hpp"
#include "./Tokens.hpp"

namespace UglyJSONParser
{

    class Tokenizer
    {
    private:
        using string = std::string;

        bool TokenizeString(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index);
        bool TokenizeNumber(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index);
        bool CheckTokenizedNumber(const string& numString, size_t exponentCnt, size_t signCnt, size_t pointCnt);
        bool TokenizeBool(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index);
        bool TokenizeNull(const string& sourceString, std::list<string>& outTokenizedStrings, size_t& index);
        bool CheckTokenizedTokens(const std::list<string>& tokenizedStrings);
    public:
        /// <summary>
        /// Tokenizes input source string
        /// </summary>
        /// <param name="sourceString"></param>
        /// <param name="outTokenizedStrings"></param>
        /// <returns></returns>
        bool Tokenize(const string& sourceString, std::list<string>& outTokenizedStrings);
    };
}

#endif // !UGLY_JSON_PARSER_TOKENIZER_HEADER