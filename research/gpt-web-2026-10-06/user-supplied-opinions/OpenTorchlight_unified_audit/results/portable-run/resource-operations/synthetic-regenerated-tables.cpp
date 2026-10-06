// Generated logical values only. Initializer order and behavior require a separate check.

#include <string>

std::wstring sampleNames[8] = {
    std::wstring(L"", 0),
    std::wstring(L"SAVE", 4),
    std::wstring(L"A\000B", 3),
    std::wstring(L"\012\015\011", 3),
    std::wstring(L"quote\"slash\\", 12),
    std::wstring(L"\u0421\u043b\u043e\u0432\u043e", 5),
    std::wstring(L"\U0001f680", 1),
    std::wstring(L"\00177", 3)
};

std::wstring sampleTags[2][3] = {
{
    std::wstring(L"VALUE", 5),
    std::wstring(L"VALUE2", 6),
    std::wstring(L"VALUE3", 6)
},
{
    std::wstring(L"", 0),
    std::wstring(L"VALUE2", 6),
    std::wstring(L"", 0)
}
};

int sampleLimits[4] = {
    (-2147483647 - 1),
    -1,
    0,
    2147483647
};

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
