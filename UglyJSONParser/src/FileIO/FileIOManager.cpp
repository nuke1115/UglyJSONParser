#include "..\..\Include\UglyJSONParser\FileIO\FileIOManager.hpp"


bool FileIOManager::LoadTextFromFile(string& destination, const string& filePath)
{
    std::ostringstream oss;

    if (IsFileExist(filePath) == false)
    {
        return false;
    }

    std::ifstream iStream(filePath,std::ios::in);

    if (!iStream.is_open())
    {
        return false;
    }

    iStream >> std::noskipws;

    oss << iStream.rdbuf();

    destination = oss.str();

    return true;
}

bool FileIOManager::ClearFile(const string& filePath)
{

    if (IsFileExist(filePath) == false)
    {
        return false;
    }

    std::ofstream oStream(filePath,std::ofstream::trunc);

    return oStream.good();
}


bool FileIOManager::WriteTextToFile(const string& data, const string& filePath, std::ios::openmode openMode)
{
    if (IsFileExist(filePath) == false)
    {
        return false;
    }

    std::ofstream oStream(filePath,openMode);

    if (!oStream.is_open())
    {
        return false;
    }

    oStream << data;
    
    return oStream.good();
}


bool FileIOManager::CreateFile(const string& filePath, const string& fileName, const string& fileExtension)
{
    std::string tmp;
    tmp.reserve(filePath.size() + fileName.size() + fileExtension.size());

    tmp.append(filePath);
    tmp.append(fileName);
    tmp.append(fileExtension);

    return CreateFile(tmp);
}

bool FileIOManager::CreateFile(const string& fullFilePath)
{
    if (IsFileExist(fullFilePath))
    {
        return false;
    }

    std::ofstream oStream(fullFilePath);

    return oStream.good();
}