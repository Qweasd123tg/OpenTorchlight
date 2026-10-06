#include <string>
#include <cstdio>
// WARNING: slots [1] not found in sample.cpp
static const std::wstring sample[] =
{
    L"FIRST",
    /* slot 1 not recovered */
    L"THIRD",
};
int main(){std::printf("count=%lu slot1_is_THIRD=%d\n",(unsigned long)(sizeof(sample)/sizeof(sample[0])),sample[1]==L"THIRD");}
