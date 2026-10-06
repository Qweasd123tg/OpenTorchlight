#include <cstdio>
const char* probe()
{
    return "bad UTF-8 continuation unsigned char";
}
int main(){puts(probe());}