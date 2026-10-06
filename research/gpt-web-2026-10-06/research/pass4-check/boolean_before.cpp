#include <cstdio>
int probe(int x)
{
 return x != false;
}
int main(){printf("%d %d %d\n",probe(-3),probe(0),probe(2));}