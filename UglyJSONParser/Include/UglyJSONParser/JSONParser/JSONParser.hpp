#ifndef UGLY_JSON_PARSER_JSON_PARSER_HEADER
#define UGLY_JSON_PARSER_JSON_PARSER_HEADER

#include <string>
#include <list>
#include "../FileIO/FileIOManager.hpp"
#include "../Tokenizer/Tokenizer.hpp"
#include "../JsonTree/Node.hpp"
#include "../JsonTree/JSONTreeBuilder.hpp"


namespace UglyJSONParser
{
    class JSONParser
    {
    private:
        JSONTreeBuilder _jsonTreeBuilder;
        FileIOManager _fileIOMgr;
        Tokenizer _tokenizer;

        using string = std::string;

    public:

        /// <summary>
        /// Builds json tree to root node from string
        /// </summary>
        /// <param name="FilePath"></param>
        /// <param name="rootNode"></param>
        /// <returns></returns>
        bool BuildJSONTreeFromString(const string& sourceString, RootNode& rootNode);

        /// <summary>
        /// Builds json tree to root node from file
        /// </summary>
        /// <param name="FilePath"></param>
        /// <param name="rootNode"></param>
        /// <returns></returns>
        bool BuildJSONTreeFromFile(const string& FilePath, RootNode& rootNode);

        /// <summary>
        /// Serializes json tree, and saves it to file
        /// </summary>
        /// <param name="FilePath"></param>
        /// <param name="rootNode"></param>
        /// <returns></returns>
        bool SaveJSONTreeToFile(const string& FilePath, RootNode& rootNode);
    };
}


#endif // !UGLY_JSON_PARSER_JSON_PARSER_HEADER