#ifndef SHELLUTILS_H
#define SHELLUTILS_H

#include <string>
#include <vector>

namespace ShellUtils
{
    void LaunchProgram(const std::string& program, const std::vector<std::string>& arguments);
    void LaunchBrowser(const std::string& url);
}

#endif
