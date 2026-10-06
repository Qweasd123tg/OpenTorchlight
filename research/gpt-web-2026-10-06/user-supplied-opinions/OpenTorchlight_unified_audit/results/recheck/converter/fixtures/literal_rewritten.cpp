#include <stdio.h>
const char *message()
{
    return "bad UTF-8 continuation unsigned char";
}

int main() { puts(message()); }
