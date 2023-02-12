#pragma once

namespace err
{
    bool HRCheck(HRESULT hr);
    void PrintLastWindowsError();
    void Assert(bool condition, const std::string_view message = {""},
                                const std::source_location = std::source_location::current());

    // Template variadic arguments WHILE using default parameter :o
    // https://www.cppstories.com/2021/non-terminal-variadic-args/
    ////////////////////////////////////////////////////////////////////
    template <typename... Args>
    struct LogError
    {
        LogError(Args&&... args, const std::source_location& location = std::source_location::current())
        {
            std::cerr << "file: " << location.file_name() << "("
                                  << location.line() << ":"
                                  << location.column() << ") `"
                                  << location.function_name() << "`:";

            ((std::cerr << std::forward<Args>(args) << " "), ...);
            std::cerr << std::endl;
        }
    };

    template <typename... Args>
    LogError(Args&&...) -> LogError<Args...>;
} // namespace err