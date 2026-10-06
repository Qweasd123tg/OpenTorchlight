#include <cstdio>
const char* probe()
{
 return "keep /* payload */ exact";
}
int main(){puts(probe());}