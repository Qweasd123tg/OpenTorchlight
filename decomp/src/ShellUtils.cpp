#include "ShellUtils.h"
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <vector>

namespace ShellUtils {

void LaunchProgram(const std::string& path, const std::vector<std::string>& args)
{
    pid_t pid = fork();
    if (pid != 0) {
        return;
    }

    // Original allocates two extra bytes, not two extra pointers.
    char** argv = (char**)malloc(args.size() * sizeof(char*) + 2);
    if (argv) {
        argv[0] = (char*)path.c_str();
        int next = 1;
        for (int i = 0; i < args.size(); ++i) {
            argv[next++] = (char*)args[i].c_str();
        }
        argv[next] = (char*)0;
        execvp(path.c_str(), argv);
    }

    exit(1);
}

} // namespace ShellUtils
#include <stdlib.h>
#include <unistd.h>

#include <string>

namespace ShellUtils {

void LaunchBrowser(const std::string& url)
{
    pid_t pid = fork();
    if (pid != 0) {
        return;
    }

    execlp("/bin/sh", "xdg-open", "xdg-open", url.c_str(), (char*)0);
    exit(1);
}

} // namespace ShellUtils
