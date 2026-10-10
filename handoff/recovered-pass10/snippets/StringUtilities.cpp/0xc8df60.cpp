std::wstring STRINGS::replaceWString(std::wstring text, const std::wstring& find, const std::wstring& replacement)
{
    std::wstring::size_type length=find.size();
    std::wstring::size_type pos;
    while((pos=text.find(find))!=std::wstring::npos)text.replace(pos,length,replacement);
    return text;
}
