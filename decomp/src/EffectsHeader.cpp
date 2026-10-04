#include "EmptyStrings.h"
#include "GameVariables.h"

bool CheckProcessWasRestarted()
{
    return g_bWasRestarted;
}

void compressAllFiles()
{
}

extern "C" int flock(int fd, int operation);

bool DoRestartProcessFinish(bool finished)
{
    if (finished && *reinterpret_cast<int *>(g_hRestartingFile) != 0) {
        flock(*reinterpret_cast<int *>(g_hRestartingFile), 8);
        close(*reinterpret_cast<int *>(g_hRestartingFile));
        *reinterpret_cast<int *>(g_hRestartingFile) = 0;
    }

    return true;
}
