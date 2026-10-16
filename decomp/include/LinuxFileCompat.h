#ifndef LINUXFILECOMPAT_H
#define LINUXFILECOMPAT_H

// LP64 compatibility structure filled by the game's FindFirst/FindNextFile.
// Timestamp components and final bytes stay opaque until their users need them.
struct _WIN32_FIND_DATA
{
    unsigned long attributes;
    unsigned char creationTime[16];
    unsigned char accessTime[16];
    unsigned char writeTime[16];
    unsigned long fileSizeHigh;
    unsigned long fileSizeLow;
    unsigned long reserved0;
    unsigned long reserved1;
    char fileName[1024];
    unsigned char unusedTail[16];
};

void* FindFirstFile(const char* pattern, _WIN32_FIND_DATA* data);
bool FindNextFile(void* handle, _WIN32_FIND_DATA* data);
void FindClose(void* handle);

#endif
