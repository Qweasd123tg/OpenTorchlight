#ifndef GAME_MAIN_RUNTIME_H
#define GAME_MAIN_RUNTIME_H
#include <string>
class CGame; class CSettings;
bool WaitForPreviousProcessFinish();
bool CheckForRestartProcessStart(int, char**);
bool uncompressFileInMemory(std::wstring, unsigned int, unsigned int, unsigned int, char*);
void removeTmpFiles();
// The original unnamed 16-byte return aggregate uses rax=data and edx=compressed length.
struct CompressedFileBuffer { char* data; unsigned int size; };
CompressedFileBuffer compressFile(std::wstring, unsigned int&);
bool ActivateRestartProcess(CGame*);
void DoRestartProcessFinish(bool);
CSettings* createSettings(const std::string&, bool&);
extern bool g_bFileCheckDone;
extern bool g_bUseLocalFile;
namespace FILESYSTEM {
void setFileTime(const std::wstring&, long long, long long, long long);
}
#endif
