#include <stdio.h>
const char *message(void)
{
 return "bad UTF-8 continuation byte";
}

int main() { puts(message()); }
