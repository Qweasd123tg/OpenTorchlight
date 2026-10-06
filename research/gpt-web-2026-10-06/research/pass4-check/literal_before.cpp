#include <cstdio>
const char* probe()
{
 return "bad UTF-8 continuation byte";
}
int main(){puts(probe());}