#pragma once

class FileReader
{
public:
    FileReader(const std::filesystem::path &filepath, 
               std::ios_base::openmode open_mode);
    ~FileReader();

    template <typename T>
    void GetBytes(T* buffer, std::size_t num_bytes = sizeof(T));

    template <typename T>
    T GetValue();

    std::string GetString(std::size_t num_bytes);

    void SkipBytes(std::size_t num_bytes);

    std::ifstream mFileStream;
};

template<typename T>
void FileReader::GetBytes(T* buffer, std::size_t num_bytes)
{
    if (!mFileStream.eof())
        mFileStream.read(reinterpret_cast<char*>(buffer), num_bytes);
    else
        err::LogError("Reached end of file");

}

template<typename T>
inline T FileReader::GetValue()
{
    T value;
    mFileStream.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}
