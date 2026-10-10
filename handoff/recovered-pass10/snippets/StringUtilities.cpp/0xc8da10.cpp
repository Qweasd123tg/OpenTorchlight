unsigned int STRINGS::StringCopyCharArray(char* out, unsigned int capacity, const char* text)
{
    if(!text || !out)return 0;
    memset(out,0,capacity);
    unsigned int length=0,remaining=10000;
    while(text[length] && remaining){++length;--remaining;}
    ++length;
    if(length>capacity)return 0;
    for(unsigned int i=0;i<length;++i)out[i]=text[i];
    return length;
}
