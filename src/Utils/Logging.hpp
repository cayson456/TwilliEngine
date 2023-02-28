#pragma once
#include <string>
#include <fstream>

namespace TwilliEngine
{
class Logger
{
public:

    Logger(const std::string &filename) : mFile(filename) {}
    ~Logger() {}

    template <typename T>
    inline Logger& operator<<(const T &output);
    
private:
    std::ofstream mFile;
    
    static Logger mDebug;
};

template<typename T>
inline Logger& Logger::operator<<(const T& output)
{
    
}
}