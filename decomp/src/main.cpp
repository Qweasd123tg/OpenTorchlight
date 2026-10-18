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
