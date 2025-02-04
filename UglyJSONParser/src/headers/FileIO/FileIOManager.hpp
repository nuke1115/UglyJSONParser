#ifndef UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER
#define UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER

#include <iosfwd>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>


class FileIOManager
{
private:
    using string = std::string;
public:

    FileIOManager() = default;
    FileIOManager(const FileIOManager&) = delete;
    FileIOManager(FileIOManager&&) = delete;

    inline bool IsFileExist(const string& filePath)
    {
        return (!filePath.empty()) && std::filesystem::exists(filePath);
    }

    bool LoadTextFromFile(string& destination, const string& filePath);

    bool ClearFile(const string& filePath);

    bool WriteTextToFile(const string& data, const string& filePath, std::ios::openmode openMode = std::ios::out | std::ios::trunc);

};

#endif // !UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER