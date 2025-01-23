#ifndef UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER
#define UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER

#include <utility>
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

    bool LoadTextFromFile(string& destination, const string& filePath);

    bool ClearFile(const string& filePath) const;

    bool WriteTextToFile(const string& data, const string& filePath) const;

    bool IsFileExist(const string& filePath) const;

};



#endif // !UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER
