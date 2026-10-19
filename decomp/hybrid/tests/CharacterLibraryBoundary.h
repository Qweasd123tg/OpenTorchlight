#ifndef OTL_CHARACTER_LIBRARY_BOUNDARY_H
#define OTL_CHARACTER_LIBRARY_BOUNDARY_H
// A near executable trampoline keeps the normal five-byte Detour in range of
// shipped shared libraries. All receivers are actual native C1 objects.
inline char* characterLibraryEntry(const char*library,const char*symbol){void*lib=library?dlopen(library,RTLD_NOW|RTLD_NOLOAD):RTLD_DEFAULT;if(library&&!lib)std::abort();void*entry=dlsym(lib,symbol);if(library)dlclose(lib);if(!entry)std::abort();return static_cast<char*>(entry);}
class CharacterLibraryBoundary {
    detour::Set hooks;
    void* code;
public:
    template<class F> CharacterLibraryBoundary(char* entry,F callback):code(MAP_FAILED){
        code=mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
        if(code==MAP_FAILED)std::abort();
        unsigned char bytes[12]={0x48,0xb8,0,0,0,0,0,0,0,0,0xff,0xe0};
        std::memcpy(bytes+2,&callback,8);std::memcpy(code,bytes,12);
        if(mprotect(code,4096,PROT_READ|PROT_EXEC))std::abort();
        hooks.redirect(entry,entry,reinterpret_cast<F>(code));
    }
    bool failed()const{return hooks.failed();}
    ~CharacterLibraryBoundary(){hooks.restore();if(munmap(code,4096))std::abort();}
private:CharacterLibraryBoundary(const CharacterLibraryBoundary&);CharacterLibraryBoundary&operator=(const CharacterLibraryBoundary&);
};
#endif
