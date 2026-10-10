std::string STRINGS::replaceString(std::string text, const std::string& find, const std::string& replacement)
{
    std::string::size_type length=find.size();
    std::string::size_type pos;
    while((pos=text.find(find))!=std::string::npos)text.replace(pos,length,replacement);
    return text;
}
