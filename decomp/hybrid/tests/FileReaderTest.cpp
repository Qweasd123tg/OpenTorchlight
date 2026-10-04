#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <OgreLogManager.h>
#include <OgreMemoryAllocatorConfig.h>
#include "AutoTest.h"
#include "FileReader.h"

TL_ORIGINAL(std::wstring, originalReadLine, (CFileReader*, wchar_t), "_ZN11CFileReader8ReadLineEw")
TL_ORIGINAL(void, originalTokenize, (CFileReader*, std::queue<std::wstring>*, const wchar_t*, wchar_t),
            "_ZN11CFileReader16ReadLineTokenizeEPSt5queueISbIwSt11char_traitsIwESaIwEESt5dequeIS4_SaIS4_EEEPKww")
TL_ORIGINAL(bool, originalConvert, (CFileReader*, FILE*, const std::wstring&),
            "_ZN11CFileReader20ConvertFileToUnicodeEP8_IO_FILERKSbIwSt11char_traitsIwESaIwEE")

namespace {
struct ReaderView {
    std::wstring filename;
    wchar_t* buffer;
    unsigned int length, position, characterSize;
};
typedef char reader_layout[sizeof(CFileReader)==sizeof(ReaderView) && sizeof(CFileReader)==0x20 ? 1 : -1];
struct Case { int operation; unsigned int seed; };

struct LogCapture : Ogre::LogListener {
    std::vector<std::string> messages;
    std::vector<int> levels;
    std::vector<unsigned char> masks;
    virtual void messageLogged(const Ogre::String& text, Ogre::LogMessageLevel level, bool mask, const Ogre::String&) {
        messages.push_back(text);levels.push_back(level);masks.push_back(mask);
    }
};

void captureReader(CFileReader& reader, autotest::Capture& out) {
    ReaderView& view=*reinterpret_cast<ReaderView*>(&reader);
    out.addText(view.filename);
    out.add(&view.length,sizeof(view.length));
    out.add(&view.position,sizeof(view.position));
    out.add(&view.characterSize,sizeof(view.characterSize));
    if(view.length>256)_exit(4);
    if(view.buffer)out.add(view.buffer,view.length*sizeof(wchar_t));
}

void body(Case& c,bool ours,autotest::Capture& out) {
    CFileReader reader;
    if(c.operation==2) {
        Ogre::LogManager logs;
        Ogre::Log* log=logs.createLog("reader-test",true,false,true);
        LogCapture captured;
        log->addListener(&captured);
        unsigned char bytes[96];std::memset(bytes,0x41,sizeof(bytes));
        static const unsigned char prefixes[][4]={
            {0xff,0xfe,0x41,0}, {0xff,0xfe,0,0}, {0,0,0xfe,0xff},
            {0xef,0xbb,0xbf,0x41}, {0xfe,0xff,0,0x41}, {0x41,0x42,0x43,0x44},
            {0xff,0x41,0,0}, {0,0xff,0xfe,0xff}, {0xef,0xbb,0x41,0},
            {0xfe,0,0,0}, {0xff,0xfe,0,0x41}, {0,0,0xfe,0x41},
            {0xef,0x41,0xbf,0}, {0,0,0x41,0xff}, {1,0,0xfe,0xff}, {0,1,0xfe,0xff}
        };
        std::memcpy(bytes,prefixes[c.seed%(sizeof(prefixes)/sizeof(prefixes[0]))],4);
        FILE* file=tmpfile();if(!file)_exit(2);
        if(fwrite(bytes,1,sizeof(bytes),file)!=sizeof(bytes))_exit(2);
        fseek(file,13,SEEK_SET);
        bool result=ours?reader.ConvertFileToUnicode(file,L"reader.dat"):originalConvert(&reader,file,L"reader.dat");
        out.add(&result,sizeof(result));
        long at=ftell(file);out.add(&at,sizeof(at));fclose(file);
        size_t count=captured.messages.size();out.add(&count,sizeof(count));
        for(size_t i=0;i<count;++i) {
            size_t n=captured.messages[i].size();out.add(&n,sizeof(n));
            out.add(captured.messages[i].data(),n);out.add(&captured.levels[i],sizeof(int));
            out.add(&captured.masks[i],sizeof(unsigned char));
        }
        log->removeListener(&captured);
        captureReader(reader,out);
        return;
    }
    const wchar_t* texts[]={L"",L"abc\nrest",L"one,two;;three#comment\n",L"\t a\r b\n",
                            L"#comment\n",L"no newline",L"\r\n",L" α β x\n",L"a\vb\fc\n"};
    std::wstring text=texts[c.seed%9];
    if(c.seed%10==9)text=std::wstring(L"a\0b\n",4);
    ReaderView& view=*reinterpret_cast<ReaderView*>(&reader);
    view.length=static_cast<unsigned int>(text.size())+1;
    view.buffer=OGRE_ALLOC_T(wchar_t,view.length,Ogre::MEMCATEGORY_GENERAL);
    std::memcpy(view.buffer,text.c_str(),view.length*sizeof(wchar_t));
    if(c.seed%4==0 && text.size()>0)--view.length; // also test a buffer without a terminator
    view.position=c.seed%5==0?view.length:c.seed%5==1?view.length/2:0;
    if(c.operation==0) {
        wchar_t ignore=(c.seed%3==0?0:c.seed%3==1?L' ':L'x');
        std::wstring line=ours?reader.ReadLine(ignore):originalReadLine(&reader,ignore);
        out.addText(line);
    } else {
        std::queue<std::wstring> tokens;tokens.push(L"existing");
        const wchar_t* separators=c.seed%3==0?L",; ":c.seed%3==1?L"":L"x";
        wchar_t comment=c.seed%2?L'#':L';';
        if(ours)reader.ReadLineTokenize(&tokens,separators,comment);
        else originalTokenize(&reader,&tokens,separators,comment);
        size_t count=tokens.size();out.add(&count,sizeof(count));
        if(count>256)_exit(4);
        while(!tokens.empty()) {out.addText(tokens.front());tokens.pop();}
    }
    captureReader(reader,out);
}
void original(void* p,autotest::Capture& out) {body(*static_cast<Case*>(p),false,out);}
void recovered(void* p,autotest::Capture& out) {body(*static_cast<Case*>(p),true,out);}
}

TL_TEST(file_reader_lines_tokens_and_encoding) {
    int failures=0;
    for(int operation=0;operation<3;++operation) {
        unsigned int cases=operation==2?16:90;
        for(unsigned int seed=0;seed<cases;++seed) {
            Case c={operation,seed};autotest::Outcome a,b;
            autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);
            bool same=WIFEXITED(a.status)&&WEXITSTATUS(a.status)==0&&
                      WIFEXITED(b.status)&&WEXITSTATUS(b.status)==0&&
                      a.capture.length==b.capture.length&&a.capture.length<autotest::Capture::kSize&&
                      std::memcmp(a.capture.data,b.capture.data,a.capture.length)==0;
            if(!same)host->log("    reader op %d seed %u status %d/%d bytes %lu/%lu\n",operation,seed,a.status,b.status,
                              (unsigned long)a.capture.length,(unsigned long)b.capture.length);
            TL_CHECK(failures,same);
        }
    }
    return failures;
}
