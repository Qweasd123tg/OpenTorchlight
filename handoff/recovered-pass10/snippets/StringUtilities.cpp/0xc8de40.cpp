float STRINGS::GetFloat(const std::wstring& text)
{
    wchar_t* end=NULL;
    return static_cast<float>(wcstod(text.c_str(),&end));
}
