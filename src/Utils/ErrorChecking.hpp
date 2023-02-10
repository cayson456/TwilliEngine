#pragma once

namespace err
{
    bool HRCheck(HRESULT hr);
    void PrintLastWindowsError();
    void Assert(bool condition, const std::string_view message = {""},
                                const std::source_location = std::source_location::current());

    void LogError(const std::string_view message = { "" }, const std::source_location = std::source_location::current());
} // namespace err