#ifndef COMPLETE_MAIN_FILE_SANDBOX_H
#define COMPLETE_MAIN_FILE_SANDBOX_H
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>
#include <utime.h>
#include <unistd.h>
#include "LinuxUtils.h"
extern std::wstring UTF8ToUTF32(const std::string&);
namespace mainfiles {
inline void put(const std::string& path,const std::string& data) { std::ofstream f(path.c_str(),std::ios::binary);f.write(data.data(),data.size()); }
inline void stamp(const std::string& path,long time) { struct utimbuf t={time,time};utime(path.c_str(),&t); }
inline std::vector<std::string> entries(const std::string& path) {
 std::vector<std::string> names;DIR* d=opendir(path.c_str());if(!d)return names;struct dirent* e;
 while((e=readdir(d)))if(std::string(e->d_name)!="."&&std::string(e->d_name)!="..")names.push_back(e->d_name);closedir(d);std::sort(names.begin(),names.end());return names;
}
inline void clear(const std::string& path) {
 struct stat st;if(lstat(path.c_str(),&st))return;if(!S_ISDIR(st.st_mode)){unlink(path.c_str());return;}
 std::vector<std::string> names=entries(path);for(unsigned i=0;i<names.size();++i)clear(path+"/"+names[i]);rmdir(path.c_str());
}
inline void capture(autotest::Capture& out,const std::string& base,const std::string& rel) {
 struct stat st;if(lstat((base+rel).c_str(),&st))return;out.addText(rel);unsigned type=S_ISDIR(st.st_mode)?1:2;out.add(&type,sizeof(type));
 if(type==1){std::vector<std::string> names=entries(base+rel);for(unsigned i=0;i<names.size();++i)capture(out,base,rel+"/"+names[i]);}
 else{std::ifstream f((base+rel).c_str(),std::ios::binary);std::string data((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());if(data.size()<=65536)out.addText(data);else{size_t size=data.size();uint64_t hash=14695981039346656037ULL;for(unsigned i=0;i<data.size();++i)hash=(hash^static_cast<unsigned char>(data[i]))*1099511628211ULL;out.add(&size,sizeof(size));out.add(&hash,sizeof(hash));}}
}
struct Sandbox {
 std::string base,app,save;std::wstring oldHome,oldData;
 Sandbox():oldHome(LinuxUtils::gameHomePath),oldData(LinuxUtils::gameDataPath) {
  char p[]="/tmp/otl-main-archive-XXXXXX";if(!mkdtemp(p))_exit(65);base=std::string(p)+"/";app=base+".runicgames/Torchlight/";save=app+"Save/";
  LinuxUtils::gameHomePath=UTF8ToUTF32(base);LinuxUtils::gameDataPath=UTF8ToUTF32(base);mkdir((base+".runicgames").c_str(),0700);mkdir(app.c_str(),0700);mkdir(save.c_str(),0700);
 }
 ~Sandbox(){LinuxUtils::gameHomePath=oldHome;LinuxUtils::gameDataPath=oldData;clear(base);}
};
}
#endif
