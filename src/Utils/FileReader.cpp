#include "precompiled.hpp"
#include "FileReader.hpp"

FileReader::FileReader(const std::filesystem::path& filepath, 
                       std::ios_base::openmode open_mode)
{
    mFileStream.open(filepath, open_mode);
}

FileReader::~FileReader()
{
    mFileStream.close();
}

std::string FileReader::GetString(std::size_t num_bytes)
{
    std::string buffer(num_bytes, ' ');
    mFileStream.read(buffer.data(), num_bytes);

    return buffer;
}

void FileReader::SkipBytes(std::size_t num_bytes)
{
    mFileStream.ignore(num_bytes);
}


