#include <stdio.h>
int normalize(int x) { return x != false; }
int main(){ printf("%d %d %d\n", normalize(-3), normalize(0), normalize(2)); }
