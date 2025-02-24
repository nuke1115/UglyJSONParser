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

    /// <summary>
    /// Checks whether file is exist
    /// </summary>
    /// <param name="filePath"></param>
    /// <returns></returns>
    inline bool IsFileExist(const string& filePath)
    {
        return (!filePath.empty()) && std::filesystem::exists(filePath);
    }

    /// <summary>
    /// loads contents from file, and copies it to destination string
    /// </summary>
    /// <param name="destination"></param>
    /// <param name="filePath"></param>
    /// <returns></returns>
    bool LoadTextFromFile(string& destination, const string& filePath);

    /// <summary>
    /// Clear file's contents
    /// </summary>
    /// <param name="filePath"></param>
    /// <returns></returns>
    bool ClearFile(const string& filePath);

    /// <summary>
    /// Write data to file
    /// </summary>
    /// <param name="data"></param>
    /// <param name="filePath"></param>
    /// <param name="openMode"></param>
    /// <returns></returns>
    bool WriteTextToFile(const string& data, const string& filePath, std::ios::openmode openMode = std::ios::out | std::ios::trunc);

    /// <summary>
    /// Create new file with input fullFilePath. FullFilePath must contains file's name and extension
    /// </summary>
    /// <param name="fullFilePath"></param>
    /// <returns></returns>
    bool CreateFile(const string& fullFilePath);

    /// <summary>
    /// Create new file with input filePath, fileName, and fileExtension. FilePath must ends with (\), and fileExtension must starts with (.).
    /// </summary>
    /// <param name="filePath"></param>
    /// <param name="fileName"></param>
    /// <param name="fileExtension"></param>
    /// <returns></returns>
    bool CreateFile(const string& filePath, const string& fileName, const string& fileExtension);

    ~FileIOManager() = default;

};

#endif // !UGLY_JSON_PARSER_FILE_IO_MANAGER_HEADER