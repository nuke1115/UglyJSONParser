#include<stdio.h>
#include<iostream>
#include <fstream>

#include ".\src\headers\JsonTree\Node.hpp"
#include ".\src\headers\FileIO\FileIOManager.hpp"
#include ".\src\headers\Tokenizer\Tokenizer.hpp"
#include ".\src\headers\JsonTree\JSONTreeBuilder.hpp"

using namespace UglyJSONParser;


void run()
{
    std::string str, jsonFilePath = "E:\\»õ Æú´õ (2)\\json.json";
    std::list<std::string> tokens;
    FileIOManager mgr;
    RootNode root;
    Tokenizer tokenizer;
    JSONTreeBuilder builder;

    mgr.LoadTextFromFile(str, jsonFilePath);
    std::cout << tokenizer.Tokenize(str, tokens) << '\n';
    std::cout << builder.BuildJSONTree(root,tokens) << '\n';
    
    std::cout << root.GetJsonTreeByString();

    mgr.WriteTextToFile(root.GetJsonTreeByString(), jsonFilePath);

}

int main()
{
    run();

    using namespace std;
    
    
    
    ios::in;
    ios::out;
    ios::ate;
    ios::app;
    ios::trunc;
    ios::binary;

}
/*
utils => ok 
fileio => ok
tokenizer => ok
jsonTree => (Nodetypes,nodeBase,node,>jsonTreeBuilder )todo=

*/