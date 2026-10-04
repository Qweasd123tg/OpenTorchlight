#include "ShellUtils.h"
#include <stdlib.h>
#include <unistd.h>
#include "EmptyStrings.h"
#include "GameNamespaces.h"

void ShellUtils::LaunchProgram(const std::string& program, const std::vector<std::string>& arguments)
{
    if (fork() != 0)
        return;

    char** argv = (char**)malloc(arguments.size() * sizeof(char*) + 2);
    if (argv)
    {
        argv[0] = (char*)program.c_str();
        int count = 1;
        for (int i = 0; (size_t)i < arguments.size(); ++i)
            argv[count++] = (char*)arguments[i].c_str();
        argv[count] = NULL;
        execvp(program.c_str(), argv);
    }
    exit(1);
}

void ShellUtils::LaunchBrowser(const std::string& url)
{
    if (fork() != 0)
        return;

    execlp("/bin/sh", "xdg-open", "xdg-open", url.c_str(), (char*)NULL);
    exit(1);
}

unsigned int lodepng_read32bitInt(const unsigned char* buffer)
{
    return ((static_cast<unsigned int>(buffer[0]) << 24) |
            (static_cast<unsigned int>(buffer[1]) << 16) |
            (static_cast<unsigned int>(buffer[2]) << 8) |
            static_cast<unsigned int>(buffer[3]));
}
