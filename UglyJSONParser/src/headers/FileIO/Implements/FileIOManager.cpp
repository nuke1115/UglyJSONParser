#include "..\FileIOManager.hpp"


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
    std::ofstream oStream(filePath,openMode);

    if (!oStream.is_open())
    {
        return false;
    }

    oStream << data;
    
    return oStream.good();
}