#include "GameMainRuntime.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include <string>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

extern int g_hRestartingFile;

bool WaitForPreviousProcessFinish()
{
    std::string path=STRINGS::StringConvertToUTF8(FILESYSTEM::GetAppDataPath()+L"restarting.lock");
    g_hRestartingFile=open(path.c_str(),O_RDWR|O_CREAT,0666);
    bool result=flock(g_hRestartingFile,LOCK_EX)==0;
    close(g_hRestartingFile);
    g_hRestartingFile=0;
    return result;
}

bool CheckForRestartProcessStart(int argc,char** argv)
{
    for (int i=1;i<argc;++i) {
        std::string arg(argv[i]);
        if (arg=="--restart") return true;
    }
    return false;
}

#include "LinuxUtils.h"
#include <OgreMemoryAllocatorConfig.h>
#include <OgreUTFString.h>
#include <fstream>
#include <cstdio>
#include <cmath>
typedef unsigned char Bytef;
typedef unsigned long uLongf;
enum { Z_OK=0, Z_MEM_ERROR=-4, Z_BUF_ERROR=-5 };
extern "C" int compress(Bytef*,uLongf*,const Bytef*,unsigned long);
extern "C" int uncompress(Bytef*,uLongf*,const Bytef*,unsigned long);

bool uncompressFileInMemory(std::wstring filename,unsigned int offset,unsigned int compressedSize,unsigned int uncompressedSize,char* data)
{
    char* buffer=static_cast<char*>(Ogre::NedAllocImpl::allocBytes(uncompressedSize,0,0,0));
    uLongf size=uncompressedSize;
    int result=uncompress(reinterpret_cast<Bytef*>(buffer),&size,reinterpret_cast<Bytef*>(data+offset),compressedSize);
    if (result!=Z_OK) {
        std::string message="ERROR IN UNCOMPRESSING DATA.\n\n ERROR IS:";
        if (result==Z_BUF_ERROR) message=message+"ERROR FROM ZIP IS BUFFER ERROR\n";
        else if (result==Z_MEM_ERROR) message=message+"ERROR FROM ZIP IS OUT OF MEMORY\n";
        if (buffer) Ogre::NedAllocImpl::deallocBytes(buffer);
        return false;
    }
    Ogre::UTFString path(filename);
    std::ofstream file(path.asUTF8_c_str(),std::ios::binary|std::ios::out);
    if (file.is_open()) {
        file.write(buffer,size);file.close();
        if (buffer) Ogre::NedAllocImpl::deallocBytes(buffer);
        return true;
    }
    if (buffer) Ogre::NedAllocImpl::deallocBytes(buffer);
    return false;
}

CompressedFileBuffer compressFile(std::wstring filename,unsigned int& uncompressedSize)
{
    CompressedFileBuffer result={NULL,0};FILE* file=NULL;
    _wfopen_s(&file,filename.c_str(),L"rb");
    if (!file) return result;
    fseek(file,0,SEEK_END);unsigned int size=ftell(file);fseek(file,0,SEEK_SET);uncompressedSize=size;
    char* data=static_cast<char*>(Ogre::NedAllocImpl::allocBytes(size,0,0,0));
    fread(data,size,1,file);fclose(file);
    uLongf compressedSize=size+static_cast<unsigned int>(ceilf(static_cast<float>(size)*0.2f))+12;
    result.data=static_cast<char*>(Ogre::NedAllocImpl::allocBytes(compressedSize,0,0,0));
    int error=compress(reinterpret_cast<Bytef*>(result.data),&compressedSize,reinterpret_cast<Bytef*>(data),size);
    if (data) Ogre::NedAllocImpl::deallocBytes(data);
    if (!error) {result.size=compressedSize;return result;}
    std::wstring message=static_cast<std::wstring>(Ogre::UTFString(L"Unable to compress file:\n"+filename)+Ogre::UTFString("\n\nTotal buffer size of file is: ")+Ogre::UTFString(STRINGS::GetValueAsWString(size))+Ogre::UTFString(L"\n"));
    if (error==Z_BUF_ERROR) message=static_cast<std::wstring>(Ogre::UTFString(message)+Ogre::UTFString("ERROR FROM ZIP IS BUFFER ERROR\n"));
    else if (error==Z_MEM_ERROR) message=static_cast<std::wstring>(Ogre::UTFString(message)+Ogre::UTFString("ERROR FROM ZIP IS OUT OF MEMORY\n"));
    if (result.data) Ogre::NedAllocImpl::deallocBytes(result.data);
    result.data=NULL;return result;
}

int DeleteFile(const char*);

void removeTmpFiles()
{
    std::wstring savePath=FILESYSTEM::GetAppDataPath()+L"Save/";
    std::wstring backupPath=savePath+L"tmpBackup/";
    TArrayList<std::wstring> files(10);
    FILESYSTEM::GetFileList(backupPath,files,L"*.*");
    for (unsigned int i=0;i<files.size();++i)
        DeleteFile(Ogre::UTFString(files[i].c_str()).asUTF8_c_str());
}

#include "ShellUtils.h"
bool ActivateRestartProcess(CGame*)
{
    std::string lockPath=STRINGS::StringConvertToUTF8(FILESYSTEM::GetAppDataPath()+L"restarting.lock");
    g_hRestartingFile=open(lockPath.c_str(),O_RDWR|O_CREAT,0666);
    bool locked=flock(g_hRestartingFile,LOCK_EX|LOCK_NB)==0;
    std::string program=STRINGS::StringConvertToUTF8(FILESYSTEM::GetApplicationPath()+L"Torchlight.bin.");
    program+="x86_64";
    std::vector<std::string> arguments(1,"");
    arguments.push_back("--restart");
    ShellUtils::LaunchProgram(program.c_str(),arguments);
    return locked;
}


#include "EmptyStrings.h"

void backupOldSavesToTmp(std::wstring directory)
{
    removeTmpFiles();
    std::wstring sourceDirectory = FILESYSTEM::GetAppDataPath() + L"Save/";
    std::wstring backupDirectory = FILESYSTEM::GetAppDataPath() + directory;
    FILESYSTEM::CreateAppDataDirectory(backupDirectory);
    TArrayList<std::wstring> files(10);
    FILESYSTEM::GetFileList(sourceDirectory, files, L"*.svt");
    FILESYSTEM::GetFileList(sourceDirectory, files, L"*.bin");
    for (unsigned int i = 0; i < files.size(); ++i) {
        std::wstring name = FILESYSTEM::GetFileName(files[i]);
        Ogre::UTFString sourceName(files[i].c_str());
        Ogre::UTFString backupName((backupDirectory + name).c_str());
        std::ifstream input(sourceName.asUTF8_c_str(), std::ios::in | std::ios::binary);
        std::ofstream output(backupName.asUTF8_c_str(), std::ios::out | std::ios::binary);
        output << input.rdbuf();
    }
}

bool uncompressFiles(std::wstring archive, std::wstring directory, bool overwrite)
{
    FILE* file = NULL;
    _wfopen_s(&file, archive.c_str(), L"rb");
    if (!file)
        return false;
    fseek(file, 0, SEEK_END);
    unsigned int size = static_cast<unsigned int>(ftell(file));
    fseek(file, 0, SEEK_SET);
    char* data = static_cast<char*>(Ogre::NedAllocImpl::allocBytes(size, 0, 0, 0));
    fread(data, size, 1, file);
    fclose(file);
    if (*reinterpret_cast<unsigned int*>(data) != 1) {
        Ogre::NedAllocImpl::deallocBytes(data);
        return false;
    }
    unsigned int count = *reinterpret_cast<unsigned int*>(data + 4);
    unsigned int position = 8;
    bool failed = false;
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int offset = *reinterpret_cast<unsigned int*>(data + position);
        unsigned int compressedSize = *reinterpret_cast<unsigned int*>(data + position + 4);
        unsigned int uncompressedSize = *reinterpret_cast<unsigned int*>(data + position + 8);
        long long timestamp = *reinterpret_cast<long long*>(data + position + 12);
        unsigned int nameLength = *reinterpret_cast<unsigned int*>(data + position + 20);
        position += 24;
        std::wstring name = EMPTY_WSTRING;
        for (unsigned int c = 0; c < nameLength; ++c) {
            // Preserve the original decoder's signed-char promotion.
            name += static_cast<wchar_t>(data[position] + (data[position + 1] << 8));
            position += 2;
        }
        std::wstring destination = directory + name;
        long long currentTime = FILESYSTEM::GetFileTime(destination.c_str());
        if (FILESYSTEM::FileExists(destination)) {
            if (overwrite || timestamp >= currentTime) {
                if (timestamp == currentTime)
                    continue;
            } else if (!g_bFileCheckDone) {
                g_bFileCheckDone = true;
                std::wstring message(L"Your local saved files are newer than the ones downloaded from the SteamCloud.\n\nDo you want to use the local files? (this will overwrite the data stored in the SteamCloud)");
                if (MessageBox(NULL, message.c_str(), L"File Check", 0x31) == 1) {
                    g_bUseLocalFile = true;
                    continue;
                }
            } else if (g_bUseLocalFile) {
                continue;
            }
        }
        std::wstring progress = (Ogre::UTFString("Saving file: ") + Ogre::UTFString(destination)).asWStr();
        if (uncompressFileInMemory(destination, offset, compressedSize, uncompressedSize, data))
            FILESYSTEM::setFileTime(destination, timestamp, 0, 0);
        else
            failed = true;
    }
    Ogre::NedAllocImpl::deallocBytes(data);
    return !failed;
}

bool compressFiles(std::wstring directory, std::wstring pattern, std::wstring archive, bool cloud)
{
    TArrayList<std::wstring> files(10);
    FILESYSTEM::GetFileListSorted(directory, files, std::wstring(pattern.c_str()));
    TArrayList<CompressedFileBuffer> buffers(10);
    TArrayList<unsigned int> sizes(10);
    unsigned int headerSize = 8;
    unsigned int totalSize = 8;
    for (unsigned int i = 0; i < files.size(); ++i) {
        unsigned int size = 0;
        buffers.add(compressFile(files[i], size));
        if (totalSize + buffers[buffers.size() - 1].size > 2999999) {
            if (buffers[buffers.size() - 1].data)
                Ogre::NedAllocImpl::deallocBytes(buffers[buffers.size() - 1].data);
            buffers[buffers.size() - 1].data = NULL;
            buffers.removeAt(buffers.size() - 1);
            files.removeAt(i--);
        } else {
            sizes.add(size);
            headerSize += 24 + FILESYSTEM::GetFileName(files[i]).size() * sizeof(wchar_t);
            totalSize += buffers[buffers.size() - 1].size + headerSize;
        }
    }
    char* data = static_cast<char*>(Ogre::NedAllocImpl::allocBytes(totalSize, 0, 0, 0));
    *reinterpret_cast<unsigned int*>(data) = 1;
    *reinterpret_cast<unsigned int*>(data + 4) = files.size();
    unsigned int position = 8;
    unsigned int offset = headerSize;
    for (int i = files.size() - 1; i >= 0; --i) {
        *reinterpret_cast<unsigned int*>(data + position) = offset;
        *reinterpret_cast<unsigned int*>(data + position + 4) = buffers[i].size;
        *reinterpret_cast<unsigned int*>(data + position + 8) = sizes[i];
        *reinterpret_cast<long long*>(data + position + 12) = FILESYSTEM::GetFileTime(files[i].c_str());
        std::wstring name = FILESYSTEM::GetFileName(files[i]);
        *reinterpret_cast<unsigned int*>(data + position + 20) = name.size();
        position += 24;
        for (unsigned int c = 0; c < name.size(); ++c) {
            data[position++] = name[c];
            data[position++] = 0;
        }
        offset += buffers[i].size;
    }
    for (int i = buffers.size() - 1; i >= 0; --i) {
        memcpy(data + position, buffers[i].data, buffers[i].size);
        position += buffers[i].size;
    }
    bool failed = true;
    if (cloud) {
        FILESYSTEM::GetFileName(archive);
    } else {
        Ogre::UTFString path(archive);
        std::ofstream output(path.asUTF8_c_str(), std::ios::out | std::ios::binary);
        if (output.is_open()) {
            output.write(data, totalSize);
            output.close();
            failed = false;
        }
    }
    Ogre::NedAllocImpl::deallocBytes(data);
    for (unsigned int i = 0; i < buffers.size(); ++i)
        if (buffers[i].data) {
            Ogre::NedAllocImpl::deallocBytes(buffers[i].data);
            buffers[i].data = NULL;
        }
    return !failed;
}

void confirmbackups()
{
    std::wstring savePath = FILESYSTEM::GetAppDataPath() + L"Save/";
    std::wstring backupPath = FILESYSTEM::GetAppDataPath() + L"saveBackup/backup/";
    std::wstring temporaryPath = FILESYSTEM::GetAppDataPath() + L"saveBackup/tmpBackup/";
    FILESYSTEM::CreateAppDataDirectory(backupPath);
    TArrayList<std::wstring> files(10);
    FILESYSTEM::GetFileList(backupPath, files, L"*.*");
    for (unsigned int i = 0; i < files.size(); ++i)
        DeleteFile(Ogre::UTFString(files[i].c_str()).asUTF8_c_str());
    files.clear();
    FILESYSTEM::GetFileList(temporaryPath, files, L"*.svt");
    for (unsigned int i = 0; i < files.size(); ++i) {
        std::wstring name = FILESYSTEM::GetFileName(files[i]);
        Ogre::UTFString source(files[i]);
        Ogre::UTFString destination(backupPath + name);
        {
            std::ifstream input(source.asUTF8_c_str(), std::ios::in | std::ios::binary);
            std::ofstream output(destination.asUTF8_c_str(), std::ios::out | std::ios::binary);
            output << input.rdbuf();
        }
        DeleteFile(source.asUTF8_c_str());
    }
}

#include "Game.h"
#include "Editor.h"
#include "CmdLineParser.h"
extern unsigned int KSETTINGS_RESTARTING;
extern unsigned int KSETTINGS_IGNORE_STEAM_CLOUD;

int main(int argc, char** argv)
{
    LinuxUtils::Init();
    if (CheckForRestartProcessStart(argc, argv))
        WaitForPreviousProcessFinish();
    std::string commandLine("");
    for (int i = 1; i < argc; ++i) {
        commandLine += argv[i];
        commandLine += ' ';
    }
    CEditor::getSingleton();
    FILESYSTEM::CreateAppDataDirectory(L".runicgames/");
    FILESYSTEM::CreateAppDataDirectory(L".runicgames/Torchlight");
    FILESYSTEM::CreateAppDataDirectory(L".runicgames/Torchlight/Save");
    FILESYSTEM::CreateAppDataDirectory(L".runicgames/Torchlight/Mods");
    bool firstRun = false;
    CSettings* settings = createSettings(commandLine, firstRun);
    if (settings->GetInt(KSETTINGS_RESTARTING) == 1)
        settings->SetInt(KSETTINGS_RESTARTING, 0);
    settings->GetInt(KSETTINGS_IGNORE_STEAM_CLOUD);
    CGame* game = new CGame(commandLine, settings, firstRun);
    if (game->getSettings() &&
        game->getSettings()->m_pCmdLineParser->GetStringParam(L"QUIT", EMPTY_WSTRING) != EMPTY_WSTRING) {
        game->begin(reinterpret_cast<void*>(0xdeadbeef));
        delete game;
        return 0;
    }
    if (game->begin(reinterpret_cast<void*>(0xdeadbeef)) < 0) {
        delete game;
        MessageBox(NULL, L"FAILED GAME CREATION", L"Load Error", 0x10);
        return 1;
    }
    bool restarting = false;
    if (game->requestingRestart()) {
        restarting = true;
        if (!ActivateRestartProcess(game)) {
            delete game;
            MessageBox(NULL, L"Restart Failed", L"Restart Game", 0x30);
            return 1;
        }
    }
    delete game;
    DoRestartProcessFinish(restarting);
    return 0;
}
