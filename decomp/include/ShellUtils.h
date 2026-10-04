#ifndef SHELLUTILS_H
#define SHELLUTILS_H
#include <string>
#include <vector>

namespace ShellUtils
{
    void LaunchProgram(const std::string& path, const std::vector<std::string>& args);
    void LaunchBrowser(const std::string& url);
}
#endif
