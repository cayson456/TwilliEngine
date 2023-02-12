#include "precompiled.hpp"
#include "ErrorChecking.hpp"

void err::PrintLastWindowsError()
{
    DWORD error = ::GetLastError();
    if (error == 0)
        return; //No error message has been recorded

    LPSTR message_buffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message_buffer, 0, NULL);

    std::string message(message_buffer, size);
    std::cerr << message << std::endl;

    //Free the buffer.
    LocalFree(message_buffer);
}

bool err::HRCheck(HRESULT hr)
{
    if (SUCCEEDED(hr))
        return true;

    _com_error error(hr);
    LPCTSTR msg = error.ErrorMessage();

    std::cerr << "HResult: " << msg << " " << std::endl;

    return false;
}

void err::Assert(bool condition, const std::string_view message,
                                 const std::source_location location)
{
#ifndef NDEBUG
    if (!condition) {
        std::cerr << "file: " << location.file_name() << "("
                              << location.line() << ":"
                              << location.column() << ") `"
                              << location.function_name() << "`:"
                              << message << std::endl;
        std::terminate();
    }
#endif
}
