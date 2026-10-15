#include "OgreResourceFile.h"

COgreResourceFile::COgreResourceFile()
{
}

#include <map>
#include <string>
#include "OgreReader.h"

int COgreResourceFile::Get32BitData(COgreReader* reader)
{
    int value[1] = {0};
    reader->read(value, sizeof(value));
    return value[0];
}

long long COgreResourceFile::Get64BitData(COgreReader* reader)
{
    long long value = 0;
    reader->read(&value, sizeof(value));
    return value;
}
