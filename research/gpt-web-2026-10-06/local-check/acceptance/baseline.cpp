#include <cstdio>
int helper(int) __attribute__((noinline));
int caller(int) __attribute__((noinline));
int (* volatile dispatch)(int)=helper;
int helper(int x){return x+10;}
int caller(int x){if(x==0)return 7;return dispatch(x);}
int main(){printf("%d %d\n",caller(1),helper(1));}
