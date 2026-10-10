float FILESYSTEM::ReadFloat(FILE* file)
{
    float value;
    if(fread(&value,sizeof(value),1,file)==1)return value;
    return 0.0f;
}
