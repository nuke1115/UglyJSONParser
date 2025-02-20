#include "../../Include/UglyJSONParser/JSONParser/JSONParser.hpp"


bool UglyJSONParser::JSONParser::BuildJSONTreeFromString(const string& sourceString, RootNode& rootNode)
{
    if (sourceString.empty())
    {
        return false;
    }

    std::list<string> tokens;

    if (_tokenizer.Tokenize(sourceString, tokens) == false)
    {
        return false;
    }

    if (_jsonTreeBuilder.BuildJSONTree(rootNode, tokens) == false)
    {
        if (rootNode.GetNodeType() == NodeType::Array || rootNode.GetNodeType() == NodeType::Object)
        {
            rootNode.Clear();
        }
        return false;
    }

    return true;
}

bool UglyJSONParser::JSONParser::BuildJSONTreeFromFile(const string& FilePath, RootNode& rootNode)
{
    if (_fileIOMgr.IsFileExist(FilePath) == false)
    {
        return false;
    }

    string sourceString;
    std::list<string> tokens;

    if (_fileIOMgr.LoadTextFromFile(sourceString, FilePath) == false)
    {
        return false;
    }

    return BuildJSONTreeFromString(sourceString, rootNode);
}

bool UglyJSONParser::JSONParser::SaveJSONTreeToFile(const string& FilePath, RootNode& rootNode)
{
    if (_fileIOMgr.IsFileExist(FilePath) == false)
    {
        return false;
    }

    return _fileIOMgr.WriteTextToFile(rootNode.GetJsonTreeByString(), FilePath);
}