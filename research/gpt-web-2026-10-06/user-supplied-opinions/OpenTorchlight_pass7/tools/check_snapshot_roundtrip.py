#!/usr/bin/env python3
"""Synthetic native initialized tables -> logical dump -> generated C++ -> same logical dump."""
import argparse,json,subprocess
from pathlib import Path
from snapshot_to_cpp import emit

ORIGINAL=r'''
#include <string>
std::wstring sampleNames[8];
std::wstring sampleTags[2][3];
int sampleLimits[4];
struct Populate {
  Populate() {
    sampleNames[0]=L"";
    sampleNames[1]=L"SAVE";
    sampleNames[2]=std::wstring(L"A\000B",3);
    sampleNames[3]=L"\n\r\t";
    sampleNames[4]=L"quote\"slash\\";
    sampleNames[5]=L"\u0421\u043b\u043e\u0432\u043e";
    sampleNames[6]=L"\U0001f680";
    sampleNames[7]=L"\00177";
    sampleTags[0][0]=L"VALUE";sampleTags[0][1]=L"VALUE2";sampleTags[0][2]=L"VALUE3";
    sampleTags[1][0]=L"";sampleTags[1][1]=L"VALUE2";sampleTags[1][2]=L"";
    sampleLimits[0]=-2147483647-1;sampleLimits[1]=-1;sampleLimits[2]=0;sampleLimits[3]=2147483647;
  }
} populate;
'''
DUMP=r'''
#include <iostream>
#include <stdint.h>
void dumpString(const std::wstring& s){std::cout<<"[";for(size_t i=0;i<s.size();++i){if(i)std::cout<<",";std::cout<<static_cast<uint32_t>(s[i]);}std::cout<<"]";}
int main(){
 if(sizeof(wchar_t)!=4||sizeof(int)!=4)return 2;
 std::cout<<"{\"format\":\"typed-logical-tables-v1\",\"tables\":[";
 std::cout<<"{\"name\":\"sampleNames\",\"type\":\"wstring\",\"shape\":[8],\"values\":[";
 for(int i=0;i<8;++i){if(i)std::cout<<",";dumpString(sampleNames[i]);}std::cout<<"]},";
 std::cout<<"{\"name\":\"sampleTags\",\"type\":\"wstring\",\"shape\":[2,3],\"values\":[";
 for(int r=0;r<2;++r)for(int c=0;c<3;++c){if(r||c)std::cout<<",";dumpString(sampleTags[r][c]);}std::cout<<"]},";
 std::cout<<"{\"name\":\"sampleLimits\",\"type\":\"int32\",\"shape\":[4],\"values\":[";
 for(int i=0;i<4;++i){if(i)std::cout<<",";std::cout<<sampleLimits[i];}std::cout<<"]}]}\n";
 std::cerr<<"wstring_bytes="<<sizeof(std::wstring)<<" wchar_bytes="<<sizeof(wchar_t)<<"\n";
}
'''

def execute(source,out,stem):
    p=out/(stem+'.cpp');p.write_text(source);exe=out/stem
    cmd=['g++','-std=gnu++98','-O2','-D_GLIBCXX_USE_CXX11_ABI=0',str(p),'-o',str(exe)]
    r=subprocess.run(cmd,capture_output=True,text=True,timeout=30)
    if r.returncode:raise RuntimeError(r.stderr)
    r=subprocess.run([str(exe)],capture_output=True,text=True,timeout=10)
    if r.returncode:raise RuntimeError(r.stderr)
    d=json.loads(r.stdout);(out/(stem+'.json')).write_text(json.dumps(d,indent=2)+'\n')
    return d,r.stderr

def run(out):
    out.mkdir(parents=True,exist_ok=True)
    original,abi=execute(ORIGINAL+DUMP,out,'synthetic-original-tables')
    generated=emit(original);(out/'generated-table-definitions.cpp').write_text(generated)
    actual,abi2=execute(generated+DUMP,out,'synthetic-regenerated-tables')
    result={'logical_tables_equal':original==actual,'tables':3,'cells':18,'strings':14,
            'scope':'synthetic tables only; not original Torchlight initialization semantics',
            'abi_original':abi.strip(),'abi_regenerated':abi2.strip(),
            'checks':['empty strings','embedded NUL with explicit length','quotes and backslash',
                      'Cyrillic','non-BMP character','control followed by digits',
                      '2D shape','signed int32 endpoints'],
            'compiler':subprocess.check_output(['g++','--version'],text=True).splitlines()[0]}
    (out/'snapshot-roundtrip.json').write_text(json.dumps(result,indent=2,ensure_ascii=False)+'\n');print(json.dumps(result,indent=2,ensure_ascii=False))
    if original!=actual:raise RuntimeError('logical mismatch')
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('out',type=Path);a=p.parse_args();run(a.out)
