#include "..\FileIOManager.hpp"

bool FileIOManager::IsFileExist(const string& filePath) const
{
    return std::filesystem::exists(filePath);
}

bool FileIOManager::LoadTextFromFile(string& destination, const string& filePath)
{

    std::ostringstream oss;

    std::string str;

    std::ifstream iStream(filePath);

    if (!iStream.is_open())
    {
        return false;
    }


    iStream >> std::noskipws;

    oss << iStream.rdbuf();


    destination.assign(std::move(oss.str()));

    return true;
}

bool FileIOManager::ClearFile(const string& filePath) const
{

    if (!IsFileExist(filePath))
    {
        return false;
    }

    std::ofstream oStream(filePath,std::ofstream::trunc);

    return true;
}


bool FileIOManager::WriteTextToFile(const string& data, const string& filePath) const
{
    std::ofstream oStream(filePath);

    if (!oStream.is_open())
    {
        return false;
    }

    oStream << data;

    return oStream.good();
}