#include "..\FileIOManager.hpp"

bool FileIOManager::IsFileExist(const string& filePath) const
{
    return (!filePath.empty()) && std::filesystem::exists(filePath);
}

bool FileIOManager::LoadTextFromFile(string& destination, const string& filePath)
{
    std::ostringstream oss;


    if (!IsFileExist(filePath))
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

bool FileIOManager::ClearFile(const string& filePath) const
{

    if (!IsFileExist(filePath))
    {
        return false;
    }

    std::ofstream oStream(filePath,std::ofstream::trunc);

    return oStream.good();
}


bool FileIOManager::WriteTextToFile(const string& data, const string& filePath) const
{
    std::ofstream oStream(filePath,std::ios::out);

    if (!oStream.is_open())
    {
        return false;
    }

    oStream << data;

    return oStream.good();
}